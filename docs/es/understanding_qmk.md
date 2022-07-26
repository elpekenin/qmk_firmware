# Entendiendo el código de QMK 

Este documento intenta explicar como el firmware de QMK funciona a un alto nivel. Se asume que el lector tiene conocimientos básicos de programación, pero no familiaridad con C. Se asume que tienes un conocimiento básico de la siguiente documentación

* [Introducción](es/getting_started_introduction.md)
* [Como funcionan un teclado](es/how_keyboards_work.md)
* [FAQ](es/faq_general.md)

## Inicio

Puedes pensar en QMK como cualquier otro programa de ordenador. Ejecuta tareas cuando se arranca, sin embargo este programa nunca acaba. Como otros programas en C, su punto de entrada es la funcion `main()`. En QMK, el `main()` se encuentra en [`quantum/main.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/main.c#L55).

Si miras el código de `main()`, verás que empieza inicializando cualquier hardware que se haya configurado (incluido el puerto USB hacia el host). La plataforma más común para QMK es `lufa`, que se ejecuta en procesadores AVR como el atmega32u4. Cuando se compila para dicha plataforma, se ejecutan (entre otros) `platform_setup()` en [`platforms/avr/platform.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/platforms/avr/platform.c#L19) y `protocol_setup()` en [`tmk_core/protocol/lufa/lufa.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/tmk_core/protocol/lufa/lufa.c#L1066). Se usan implementaciones diferentes cuando se compila para otras plataformas como `chibios` o `vusb`. Puede parecer mucho código de primeras, pero la mayoría está desactivado con `#define`s.

La función `main()` empezará despues la parte central del programa con un [`while (true)`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/main.c#L63). Este es [El Bucle Principal](#the-main-loop).

## El Bucle Principal

Esta parte del código se llama "El Bucle Principal" porque es responsable de repetir las mismas instrucciones indefinidamente. Aqui es donde QMK ejecuta todas las funciones responsables de que el teclado se comporte como lo que hayamos configurado.

El bucle principal llamará a [`protocol_task()`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/main.c#L38), que a su vez llama a `keyboard_task()` in [`quantum/keyboard.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/keyboard.c#L377). Aquí es donde toda la funcionalidad del teclado se ejecuta, es responsable de detectar cambios en las teclas y encender o apagar los LEDs de estado.

En `keyboard_task()` se puede encontrar código para:

* [Escanear la Matriz](#matrix-scanning)
* Manejar el ratón
* LEDs de estado del teclado (Caps Lock, Num Lock, Scroll Lock)

#### Escanear la Matriz

El escaneo de la matriz es la función básica del firmware de un teclado. Es el proceso de detectar qué teclas están pulsadas y se ejecuta una gran cantidad de veces por segundo. De hecho, no es exagerado decir que el 99% del tiempo de CPU se gasta en esta funcionalidad.

Aunque hay diferentes maneras de hacerlo, se escapan del objetivo de este documento. Es suficiente con tratar el escaneo como una caja negra a la que le pedimos el estado actual de la matriz y nos devuelve una estructura con el siguiente formato:

```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

Essta es la representación de una matriz de 4 filas y 5 columnas. Cuando una tecla está pulsada, su posición en la matriz será `1` en vez de `0`.

El escaneo se ejecuta muchas veces por segundo. El valor exacto varía pero generalmente se hace un mínimo de 10 veces por segundo para evitar un retardo perceptible.

##### Relación Entre Matriz y Distribución de Teclas

Una vez sabemos el estado de cada switch en nuestro teclado, tenemos que asignarle un keycode. En QMK esto se hace con macros de C que nos permiten abstraer la definición de posición física de las teclas y su funcionalidad.

A nivel de teclado definimos una macro (generalmente llamada `LAYOUT()`) qwue relaciona nuestra matriz con la posición física de las teclas. A veces las matrices no tienen switches en cada posición y podems usar esta macro para rellenar esos huecos con KC_NO, haciendo más fácil nuestro trabajo. Aquí hay un `LAYOUT()` de ejemplo para un teclado numérico.

```c
#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k33, \
    k40,      k42 \
) { \
    { k00, k01,   k02, k03   }, \
    { k10, k11,   k12, k13   }, \
    { k20, k21,   k22, KC_NO }, \
    { k30, k31,   k32, k33   }, \
    { k40, KC_NO, k42, KC_NO } \
}
```

¿Ves cómo el segundo bloque de nuestro `LAYOUT()` se relaciona con la matriz que vimos antes? Esta macro mapea el array del escaneo con keycodes. Si te fijas, el teclado tiene 17 teclas por lo que hay 3 posiciones donde la matriz podría tener una tecla y no la hay, debido a teclas más grande. Estas posiciones se han llenado con `KC_NO` para no tener que ponerlos cada vez que añadamos código a nuestro keymap.

También se puede usar esta macro para distribuciones inusuales, por ejemplo el [Clueboard rev 2](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/66/rev2/rev2.h). La explicación de dicho código está fuera del objetivo del presente documento.

##### Asignar Keycodes

A nivel de keymap hacemos uso de nuestro `LAYOUT()` para relacionar keycodes y teclas. El código queda:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,            KC_PDOT
    )
}
```

Fíjate como los argumentos coinciden con la primera mitad de la macro `LAYOUT()` de la sección anterior. Así es como cogemos los keycodes y los asignamos a nuestro Escaneo de Matriz de antes.

##### Detectar Cambio de Estado

El escaneo descrito antes nos dice el estado de la matrix en un instante dado, pero nuestro ordenador solo quiere saber los cambios, no importa el estado. QMK almacena el resultado del escaneo anterior y lo compara con el actual para determinar cuándo una tecla ha sido pulsada o soltada.

Veámoslo con un ejemplo. En mitad del bucle de escaneos, el resultado anterior era:

```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

Y el escaneo actual es:

```
{
    {1,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

Comparando con el keymap, podemos ver que se ha pulsado la tecla `KC_NUM`. Esto se comunica a las funciones `process_record`.

<!-- FIXME: Magic happens between here and process_record -->

##### Process Record

La función `process_record()` en sí misma es bastante simple, pero es la puerta para sobre-escribir funcionalidad a varios niveles en QMK. La cadena de eventos está listada abajo. Dependiendo de las opciones en `rules.mk` u otras partes, solo una parte de estas funciones se incluirán en el firmware final.

* [`void action_exec(keyevent_t event)`](https://github.com/qmk/qmk_firmware/blob/88fe5c16a5cdca5e3cf13ef3cd91f5f1e4898c37/quantum/action.c#L70-L131)
    * [`void pre_process_record_quantum(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/ed49dbeac4c0deba1c6b511ac1ce8f4c542e1b3e/quantum/quantum.c#L176-L185)
      * [`bool process_combo(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_combo.c#L115)
  * [`void process_record(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/tmk_core/common/action.c#L172)
    * [`bool process_record_quantum(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L206)
      * [Relacionar este evento a un keycode](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L226)
      * [`void velocikey_accelerate(void)`](https://github.com/qmk/qmk_firmware/blob/c1c5922aae7b60b7c7d13d3769350eed9dda17ab/quantum/velocikey.c#L27)
      * [`void preprocess_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_tap_dance.c#L119)
      * [`bool process_key_lock(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_key_lock.c#L62)
      * [`bool process_clicky(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_clicky.c#L79)
      * [`bool process_haptic(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/2cee371bf125a6ec541dd7c5a809573facc7c456/drivers/haptic/haptic.c#L216)
      * [`bool process_record_kb(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/card/card.c#L20)
        * [`bool process_record_user(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/clueboard/card/keymaps/default/keymap.c#L58)
      * [`bool process_midi(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_midi.c#L81)
      * [`bool process_audio(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_audio.c#L19)
      * [`bool process_steno(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_steno.c#L160)
      * [`bool process_music(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_music.c#L114)
      * [`bool process_key_override(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/5a1b857dea45a17698f6baa7dd1b7a7ea907fb0a/quantum/process_keycode/process_key_override.c#L397)
      * [`bool process_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_tap_dance.c#L141)
      * [`bool process_unicode_common(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicode_common.c#L169)
        llama a una de:
          * [`bool process_unicode(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicode.c#L20)
          * [`bool process_unicodemap(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_unicodemap.c#L46)
          * [`bool process_ucis(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_ucis.c#L95)
      * [`bool process_leader(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_leader.c#L51)
      * [`bool process_printer(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_printer.c#L77)
      * [`bool process_auto_shift(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_auto_shift.c#L94)
      * `bool process_dynamic_tapping_term(uint16_t keycode, keyrecord_t *record)`
      * [`bool process_terminal(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/process_keycode/process_terminal.c#L264)
      * [Identificar y processar keycodes especiales de QMK](https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/quantum/quantum.c#L291)

Cualquier paso de esta cadena (por ejemplo `process_record_kb()`) puede usar `return false` para interrumpir el procesado de la cadena.

Tras esto, se llama a `post_process_record()`, que puede ser usado para hacer limpieza adicionar después del manejo normal del keycode.

* [`void post_process_record(keyrecord_t *record)`]()
  * [`void post_process_record_quantum(keyrecord_t *record)`]()
    * [Relacionar este evento a un keycode]()
    * [`void post_process_clicky(uint16_t keycode, keyrecord_t *record)`]()
    * [`void post_process_record_kb(uint16_t keycode, keyrecord_t *record)`]()
      * [`void post_process_record_user(uint16_t keycode, keyrecord_t *record)`]()
      
<!--
#### Mouse Handling

FIXME: This needs to be written

#### Serial Link(s)

FIXME: This needs to be written

#### Keyboard state LEDs (Caps Lock, Num Lock, Scroll Lock)

FIXME: This needs to be written

-->
