# Configuración de Tap-Hold (Pulsar-Mantener)

Aunque las opciones de Tap-Hold son fantasticas, también tienen sus problemas. Hemos intentado configurarlos con valores por defecto razonables, pero todavía podría causar problemas a alguna gente.

Estas opciones te permiten modificar el comportamiento de las teclas Tap-Hold.

## Tapping Term

Lo esencial de las siguientes características, es la configuración del tapping term. El tiempo exacto para que se sienta natural puede cambiar entre teclados, switches o incluso teclas.

?> `DYNAMIC_TAPPING_TERM_ENABLE` activa tres teclas especiales que te ayudarán a encontrar rápidamente un tapping term que te resulte cómodo. Consulta [Tapping Term Dinámico](#dynamic-tapping-term) para más detalles.

Puedes configurar el tiempo de forma global, añadiendo a tu `config.h`:

```c
#define TAPPING_TERM 200
```

Esta configuración se define en milisegundos, y su valor por defecto es 200ms. Es una buena media para la mayoría de la gente.

Para un mayor control de esta opción, puedes añadir a tu `config.h`:

```c
#define TAPPING_TERM_PER_KEY
```

Entonces, añade esta función en tu keymap:

```c
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            return TAPPING_TERM + 1250;
        case LT(1, KC_GRV):
            return 130;
        default:
            return TAPPING_TERM;
    }
}
```

### Tapping Term Dinámico :id=dynamic-tapping-term

`DYNAMIC_TAPPING_TERM_ENABLE` es una opción que puedes activar en `rules.mk` y que permite usar tres teclas especiales en tu keymap para editar el tapping term en caliente (sin editar tu código y actualizar el firmware en tu teclado).

| Tecla         | Descripción                                                                                                            |
|-------------|------------------------------------------------------------------------------------------------------------------------|
| `DT_PRNT`   | Escribe el valor actual del tapping term, en milisegundos                                          |
| `DT_UP`     | Aumenta el valor actual del tapping term en `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms por defecto)   |
| `DT_DOWN`   | Disminuye el valor actual del tapping term en `DYNAMIC_TAPPING_TERM_INCREMENT`ms (5ms por defecto) |

Configura el tapping term de la manera usual con `#define TAPPING_TERM <valor>` en `config.h` y añade `DYNAMIC_TAPPING_TERM_ENABLE = yes` a `rules.mk`. Entonces, coloca las teclas recién explicadas en cualquier lugar de tu keymap y flashea el nuevo firmware en el teclado.

Ahora puedes intentar usar teclas con doble rol, como layer-taps o mod-taps, y usar `DT_DOWN` y `DT_UP` para ajustar el tapping term al momento. Si activas frecuentemente el modificador de tu(s) mod-tap por accidente, es un signo de que tu tapping term es muy bajo, así que pulsa `DT_UP` unas cuantas veces para aumentarlo hasta que no suceda. En cambio, si obtienes letras cuando querías cambiar de capa temporalmente, usa `DT_DOWN` para reducir el tapping term. Estas teclas afectal al tapping term *global*, no puedes cambiar el tapping term de una tecla específica sin re-flashear.

Una vez satisfecho con el valor del tapping term, abre tu `config.h` y sustituye el valor existente con la salida de la tecla `DT_PRNT`.

Es importante actualizar `TAPPING_TERM` con el nuevo valor porque los cambios hechos con `DT_UP` y `DT_DOWN` no sos persistentes.

El valor en el que aumenta o decrementa el tapping term cuando pulsas `DT_UP` y `DT_DOWN` se puede configurar en `config.h` con `#define DYNAMIC_TAPPING_TERM_INCREMENT <nuevo valor>`. El the tapping term *no* se modifica manteniendo las teclas pulsadas, si quieres, por ejemplo, disminuirlo en 50ms, no puedes mantener `DT_DOWN` pulsado; tienes que pulsarlo 10 veces seguidas (con el valor por defecto de 5ms).

Si necesitas más flexibilidad, nada te impide definir tus propios keycodes personalizados, para cambiar el tapping term de forma dinámica.
```c
enum custom_dynamic_tapping_term_keys = {
    DT_UP_50 = SAFE_RANGE,
    DT_DOWN_50,
    DT_UP_X2,
    DT_DOWN_X2,
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DT_UP_50:
        if (record->event.pressed) {
            g_tapping_term += 50;
        }
        break;
    case DT_DOWN_50:
        if (record->event.pressed) {
            g_tapping_term -= 50;
        }
        break;
    case DT_UP_X2:
        if (record->event.pressed) {
            g_tapping_term *= 2;
        }
        break;
    case DT_DOWN_X2:
        if (record->event.pressed) {
            g_tapping_term /= 2;
        }
        break;
    }
    return true;
};
```

Para que esta característica sea efectiva cuando usas tapping terms diferentes en cada tecla, necesitas hacer unos cuantos cambios a la funcion `get_tapping_term`. Lo que necesitas es reemplazar cada aparición de `TAPPING_TERM` con `g_tapping_term`. Si no lo haces, verás que el valor escrito por `DT_PRNT` sube y baja, pero no notarás cambios puesto que no se están aplicando. Si puedes bajar hasta 10ms y aún activar la función de pulsación en tu tecla dual, es un signo de que se te ha olvidado hacer los cambioos necesarios a `get_tapping_term`.

Por ejemplo, así quedaría el `get_tapping_term` visto antes tras aplicar los cambios:

```c
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
           return g_tapping_term + 1250;
        case LT(1, KC_GRV):
            return 130;
        default:
            return g_tapping_term;
    }
}
```

La razón es que `TAPPING_TERM` es una macro que se expande a un entero constante y por tanto no se puede cambiar en ejecución, mientras que `g_tapping_term` es una variable cuyo valor podemos editar. Si quieres, puedes activar temporalmente `DYNAMIC_TAPPING_TERM_ENABLE` para encontrar un valor de tapping term que te resulte cómodo y entonces desactivar la carácteristica y revertir los cambios. En caso de que necesites acceder al tapping term en algún otro lugar de tu código, puedes usar la macro `GET_TAPPING_TERM(keycode, record)`. Esta macro expandirá a cualquiera que sea la forma apropiada de obtener la configuración actual.

## Modos de Decision

El código que decide entre las acciones de pulsar y mantener e una tecla permite 3 modos diferentes, en orden ascendente de preferencia hacia matener:

1. El modo por defecto selecciona la acción de mantener solo si la tecla se ha pulsado durante más tiempo que el tapping term. En este modo, pulsar otras teclas mientras esta se mantiene no afecta a la decisión.

2. El modo “permissive hold”, además del comportamiento por defecto, selecciona inmediatamente la acción de mantener cuando otra tecla es pulsada(presionada y levantada) mientras la tecla con doble acción está pulsada, incluso si esto sucede antes del tapping term. Si otra tecla es pulsada(sin levantar), pero la tecla dual se levanta antes que esta otra (y antes del tapping term), se selecciona la acción de pulsación.

3. El modo “hold on other key press” , añade al comportamiento por defecto, que se seleccione automáticamente la acción de mantener cuando otra tecla es pulsada mientras la tecla dual está mantenida, incluso si esto sucede antes del tapping term.

Fíjate que hasta que la decisión se completa (cosa que sucede cuando la tecla es liberada, el tapping term expira, u otras condiciones extra se cumplen), los eventos de teclas son atrasados y no se transmiten al anfitrión inmediatamente. El modo por defecto añade el mayor retardo (si la tecla se mantiene pulsada se espera tapping term), y los otros modos puedes reducir este retardo si la decisión se toma antes.

### Modo por defecto
Secuencia de ejemplo 1 (la tecla `L` es `KC_RGHT` en la capa 2):

```
             TAPPING_TERM
  +---------------|--------------------+
  | +-------------|-------+            |
  | | LT(2, KC_A) |       |            |
  | +-------------|-------+            |
  |               | +--------------+   |
  |               | | KC_L         |   |
  |               | +--------------+   |
  +---------------|--------------------+
```
La secuencia enviaría `KC_RGHT`, dado que `LT(2, KC_A)` se pulsa durante más tiempo que `TAPPING_TERM`.

---

Secuencia de ejemplo 2 (la tecla `L` es `KC_RGHT` en la capa 2):

```
                           TAPPING_TERM
  +-----------------------------|------+
  | +---------------+           |      |
  | | LT(2, KC_A)   |           |      |
  | +---------------+           |      |
  |            +--------------+ |      |
  |            | KC_L         | |      |
  |            +--------------+ |      |
  +-----------------------------|------+
```
La secuencia enviaría `KC_A` `KC_L` en vez de `KC_RIGHT`, porque `LT(2, KC_A)` no se ha pulsado durante el tiempo necesario, `TAPPING_TERM`.

---

Secuencia de ejemplo 3 (Mod Tap):

```
                         TAPPING_TERM
  +---------------------------|--------+
  | +-------------+           |        |
  | | SFT_T(KC_A) |           |        |
  | +-------------+           |        |
  |       +--------------+    |        |
  |       | KC_X         |    |        |
  |       +--------------+    |        |
  +---------------------------|--------+
```
Basado en los ejemplos anteriores, podrías esperar que la salida fuera `KC_A` `KC_X` ya que `SFT_T(KC_A)` NO se ha pulsado más tiempo que el `TAPPING_TERM`.
Sin embargo, la salida será `X` mayúscula (`SHIFT` + `x`) debido a las razones explicadas en [Ignore Mod Tap Interrupt](#ignore-mod-tap-interrupt).


### Permissive Hold

El modo “permissive hold” se puede activar para todas las teclas duales añadiendo a `config.h`:

```c
#define PERMISSIVE_HOLD
```

Esto hace que las teclas funcionen mejor para gente que escribe rápido o para configuraciones con un `TAPPING_TERM` alto.

Si pulsas una tecla dual, pulsas otra tecla(presionar y liberar) y luego liberar la tecla dual, todo en una ventana de tiempo dentro del tapping term, por defecto la tecla dual realizará su función de pulsacion. Sin embargo, cuando `PERMISSIVE_HOLD` está activado, la tecla hará su acción de mantener.

Ejemplo de una secuencia afectada por el modo “permissive hold”:

- `LT(2, KC_A)` Pulsado
- `KC_L` Pulsado (la tecla `L` es `KC_RGHT` en la capa 2)
- `KC_L` Liberado
- `LT(2, KC_A)` Liberado

```
                         TAPPING_TERM   
  +---------------------------|--------+
  | +----------------------+  |        |
  | | LT(2, KC_A)          |  |        |
  | +----------------------+  |        |
  |    +--------------+       |        |
  |    | KC_L         |       |        |
  |    +--------------+       |        |
  +---------------------------|--------+
```

Normalmente, si haces todo esto durante `TAPPING_TERM` (por defecto: 200ms), se registrará como `al` por el firmware y el sistema anfitrión.  Con `PERMISSIVE_HOLD`, la tecla Layer Tap se considera un interruptor de capa si otra tecla se pulsa, y la secuencia se registraría como `KC_RGHT` (el mapeo de `L` en la capa 2). Podemos describir esta secuencia como una “pulsación anidada” (los eventos de la tecla modificada están “anidados” entre los eventos de la tecla dual).

Sin embargo, esta secuencia ligeramente diferente no sería afectada por el modo “permissive hold”:

- `LT(2, KC_A)` Pulsado
- `KC_L` Pulsado (la tecla `L` es `KC_RGHT` en la capa 2)
- `LT(2, KC_A)` Liberado
- `KC_L` Liberado

```
                         TAPPING_TERM   
  +---------------------------|--------+
  | +-------------+           |        |
  | | LT(2, KC_A) |           |        |
  | +-------------+           |        |
  |       +--------------+    |        |
  |       | KC_L         |    |        |
  |       +--------------+    |        |
  +---------------------------|--------+
```

En esta secuencia, la tecla dual se libera antes que la otra tecla, si esto sucede durante el tapping term, el modo “permissive hold” todavia elegirá la acción de pulsación para la tecla dual, y se registrará `al` en el anfitrión. Podemos describir esto como una “pulsación giratoria” (los eventos de pulsar y levantar ambas teclas se comportan como si girásemos una bola entre las 2 teclas, primero pulando cada tecla y liberándolas en el mismo orden).

?> La opción `PERMISSIVE_HOLD` también afecta a las teclas Mod Tap, pero puede no ser percibido si no se activa  también `IGNORE_MOD_TAP_INTERRUPT` para esas teclas, porque por defecto Mod Tap keys considera tanto las “pulsaciones anidadas” como las “pulsaciones giratorias“ como el modificador mantenido, en vez de como una pulsación. Si no activas `IGNORE_MOD_TAP_INTERRUPT`, el efecto de `PERMISSIVE_HOLD` en las teclas Mod Tap estará limitado a reducir el retardo hasta que los eventos son enviados al anfitrión.

Para un mayor control de esta opción, puedes añadir a tu `config.h`:

```c
#define PERMISSIVE_HOLD_PER_KEY
```

Entonces, añade esta función en tu keymap:

```c
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            // Selecciona inmediatamente la acción de mantener cuando otra tecla se pulsa y libera.
            return true;
        default:
            // No selecciona la acción de mantener cuando otra tecla se pulsa y libera.
            return false;
    }
}
```

### Hold On Other Key Press

El modo “hold on other key press” se activa para todas las teclas duales añadiendo dicha opción al `config.h`:

```c
#define HOLD_ON_OTHER_KEY_PRESS
```

Esto hace que las teclas funcionen mejor para gente que escribe rápido o para configuraciones con un `TAPPING_TERM` alto. Comparado con el modo “permissive hold”, este modo selecciona la acción de mantener en más escenario.

Si pulsas una tecla dual, pulsas otra tecla y luego liberas la tecla dual, todo durante el tapping term, por defecto la tecla dual hara su acción de pulsar. Sin embargo, si la opción `HOLD_ON_OTHER_KEY_PRESS` está activada, la tecla dual hara su action de mantener.

Ejemplo de una secuencia que es afectada por el modo “hold on other key press”, pro no por el “permissive hold”:

- `LT(2, KC_A)` Pulsado
- `KC_L` Pulsado (la tecla `L` es `KC_RGHT` en la capa 2)
- `LT(2, KC_A)` Liberado
- `KC_L` Liberado

```
                         TAPPING_TERM
  +---------------------------|--------+
  | +-------------+           |        |
  | | LT(2, KC_A) |           |        |
  | +-------------+           |        |
  |       +--------------+    |        |
  |       | KC_L         |    |        |
  |       +--------------+    |        |
  +---------------------------|--------+
```

Normalmente, si haces todo esto durante `TAPPING_TERM` (por defecto: 200ms), se registrará como `al` por el firmware y el sistema anfitrión.  Con `HOLD_ON_OTHER_KEY_PRESSES`, la tecla Layer Tap se considera un interruptor de capa si otra tecla se pulsa, y la secuencia se registraría como `KC_RGHT` (el mapeo de `L` en la capa 2).

?> La opción `HOLD_ON_OTHER_KEY_PRESS` también afecta a las teclas Mod Tap, pero puede no ser percibido si no se activa  también `IGNORE_MOD_TAP_INTERRUPT` para esas teclas, porque por defecto Mod Tap keys considera las “pulsaciones giratorias“ como el modificador mantenido, en vez de como una pulsación. Si no activas `IGNORE_MOD_TAP_INTERRUPT`, el efecto de `HOLD_ON_OTHER_KEY_PRESS` en las teclas Mod Tap estará limitado a reducir el retardo hasta que los eventos son enviados al anfitrión.

Para un mayor control de esta opción, puedes añadir a tu `config.h`:

```c
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
```

Entonces, añade esta función en tu keymap:

```c
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            // Selecciona inmediatamente la acción de mantener cuando otra tecla se pulsa.
            return true;
        default:
            // No selecciona la acción de mantener cuando otra tecla se pulsa.
            return false;
    }
}
```


## Ignore Mod Tap Interrupt

Para activar esta opción, añade a tu `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT
```

?> Esta opcion solo afecta a teclas Mod Tap; no afecta a otras teclas duales como Layer Tap.

Por defecto, la decisión entre pulsar y mantener en Mod Tap prefiere la acción de mantener. Si pulsas un Mod Tap y pulsas otra tecla mientras Mod Tap sigue pulsado, el Mod Tap se entenderá como un modificador incluso si se ha levantado dentro del tapping term, e independientemente del orden en que las teclas se liberen. Usar opciones como `PERMISSIVE_HOLD` o `HOLD_ON_OTHER_KEY_PRESS` no afecta a la funcionalidad de Mod Tap de una forma significativa (estas opciones aún afectan al retardo hasta que el código de teclas duales termina su decisión entre pulsar y mantener, pero entonces el código de Mod Tap sobre-escribirá el resultado de la decisión y elegirá la acción de mantener si otra tecla fue pulsada). De hecho, por defecto, la decision para Mod Tap se hace de la misma manera que si `HOLD_ON_OTHER_KEY_PRESS` estuviera activo, pero sin la disminución de retardo el retardo que consigue `HOLD_ON_OTHER_KEY_PRESS`.

Si la opción `IGNORE_MOD_TAP_INTERRUPT` está activa, las teclas Mod Tap no serán tratadas de forma especial y su funcionamiento será el mismo que cualquier otra tecla dual, como por ejemplo Layer Tap. Entonces, el comportamiento de Mod Tap se puede ajustar con opciones como `PERMISSIVE_HOLD` o `HOLD_ON_OTHER_KEY_PRESS`.

Ejemplo de una secuencia afectada por la opción `IGNORE_MOD_TAP_INTERRUPT` (asumiento que las opciones `PERMISSIVE_HOLD` y `HOLD_ON_OTHER_KEY_PRESS` no están activadas):

- `SFT_T(KC_A)` Pulsado
- `KC_X` Pulsado
- `SFT_T(KC_A)` Liberado
- `KC_X` Liberado

```
                         TAPPING_TERM
  +---------------------------|--------+
  | +-------------+           |        |
  | | SFT_T(KC_A) |           |        |
  | +-------------+           |        |
  |       +--------------+    |        |
  |       | KC_X         |    |        |
  |       +--------------+    |        |
  +---------------------------|--------+
```

Normalmente, esto enviaría una `X` mayúscula (`SHIFT`+`x`), incluso is la secuencia se hace más rápido que el `TAPPING_TERM`. Sin embargo, cuando `IGNORE_MOD_TAP_INTERRUPT` está activo, la tecla `SFT_T(KC_A)` debe haber sido mantenida por más tiempo que `TAPPING_TERM` para registrarse la acción de estar mantenida. Una pulsación rapida enviará `ax` en este caso, mientras que mantener la tecla mandaría `X` mayúscula (`SHIFT`+`x`).

Sin embargo, si la opción `HOLD_ON_OTHER_KEY_PRESS` se activa a la vez que `IGNORE_MOD_TAP_INTERRUPT`, la secuencia anterior volvería a enviar una `X` mayúscula (`SHIFT`+`x`) incluso is se hace más rápido que el `TAPPING_TERM`.  La diferencia respecto a la configuración por defecto es que, por defecto el anfitrión recibe los eventos después de que `SFT_T(KC_A)` se libere, pero con la opción `HOLD_ON_OTHER_KEY_PRESS`, empezará a recibir eventos tan pronto se pulse `KC_X`.

Para un mayor control de esta opción, puedes añadir a tu `config.h`:

```c
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
```

Entonces, añade esta función en tu keymap:

```c
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_SPC):
            // No se fuerza a pulsaciones de Mod-Tap a ser tratadas como modificador
            // si cualquier otra tecla se pulsa mientras el Mod-Tap está mantenido.
            return true;
        default:
            // Fuerza a pulsaciones de Mod-Tap a ser tratadas como modificador
            // si cualquier otra tecla se pulsa mientras el Mod-Tap está mantenido.
            return false;
    }
}
```

## Tapping Force Hold

Para activar `tapping force hold`, añade a tu `config.h`:

```c
#define TAPPING_FORCE_HOLD
```

Cuando el usuario mantiene la tecla tras pulsarla, la función de pulsación se repite por defecto, en vez de activar la función de mantener. Esto permite mantener la habilidad de auto repetir la función de pulsación en una tecla dual. `TAPPING_FORCE_HOLD` elimina esta habilidad para permitir al usuario activar la función de mantener, en caso de mantener tras haber pulsado.

Ejemplo:

- `SFT_T(KC_A)` Pulsado
- `SFT_T(KC_A)` Liberado
- `SFT_T(KC_A)` Pulsado
- espera a que se agote el tapping term...
- `SFT_T(KC_A)` Liberado

Con la configuración por defecto, se enviaría `a` tras la primera liberación y otra `a` en la segunda pulsación, permitiendo al ordenador activar funcionalidades de auto repetición.

Con `TAPPING_FORCE_HOLD`, la segunda pulsación se interpreta como Shift, permitiendo usarlo como un modificador poco después de la primera pulsación. 

!> `TAPPING_FORCE_HOLD` romperá cualquier cosa que use interruptores por pulsación (Como el keycode `TT` para capas, o el One Shot Tap Toggle). <!-- TODO improve this -->

Para un mayor control de esta opción, puedes añadir a tu `config.h`:

```c
#define TAPPING_FORCE_HOLD_PER_KEY
```

Entonces, añade esta función en tu keymap:

```c
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            return true;
        default:
            return false;
    }
}
```

## Retro Tapping

Para activar `retro tapping`, activa a tu `config.h`:

```c
#define RETRO_TAPPING
```

Pulsar y liberar una tecla dual sin pulsar otra tecla, resultará en que no suceda nada. Con retro tapping activo, liberar la tecla sin pulsar otra enviará el keycode inicial incluso si se hace después del tapping term.

Por ejemplo, mantener y liberar `LT(2, KC_SPC)` sin pulsar otra teclado resultará en que no suceda nada. COn esta opción activa, enviará `KC_SPC`.

```
               TAPPING_TERM
  +-----------------|------------------+
  | +---------------|-------+          |
  | | LT(2, KC_SPC) |       |          |
  | +---------------|-------+          |
  |                 |                  |
  |                 |                  |
  |                 |                  |
  +-----------------|------------------+
```

Para un mayor control de esta opción, puedes añadir a tu `config.h`:

```c
#define RETRO_TAPPING_PER_KEY
```

Entonces, añade esta función en tu keymap:

```c
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(2, KC_SPC):
            return true;
        default:
            return false;
    }
}
```

### Retro Shift

[Auto Shift,](feature_auto_shift.md) tiene su propia versión del `retro tapping` llamada `retro shift`. Es extremadamente parecida a `retro tapping`, pero mantener la tecla pasado `AUTO_SHIFT_TIMEOUT` resulta en el valor enviado incluyendo el shift. Otras configuraciones también le afectan diferente, mira [aquí](feature_auto_shift.md#retro-shift) para más imformación.

## ¿Por qué incluir el registro de teclas en las funciones *per-key*?

Quizás te hayas percatado que incluimos el registro en todas las funciones "per key", y te podrías por qué se hace esto.

Es realmente simple: personalización. Pero específicamente, depende en cómo esté cableado tu teclado. Por ejemplo, si cada fila realmente usa una fila en la matriz, sería más facil usar `if (record->event.row == 3)` en vez de comprobar un montón de keycodes. Lo que es especialmente bueno para aquellos usando teclas Tap Hold type en su home row. Por lo que podrías ajustarlas para que no interfieran tu escritura habitual.

## ¡¿Por qué no hay función `*_kb` ó `*_user`?!

A diferencia de otras funciones, no hay una necesidad (o razón) para tener una función a nivel interno o de teclado. Solo las funciones a nivel de usuario resultan útiles, así que no hay necesidad de marcarlas como tal.