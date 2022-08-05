# QMK API

Esta pagina describe el uso de la QMK API. Si eres un desarrollador de aplicaciones puedes usar esta API para compilar el firmware de cualquier [QMK](https://qmk.fm) teclado.

## Overview

Este servicio es una API asincrona para la compilacion de keymaps personalizados. Al hacer un POST con el JSON, a la API, podras checar periodicamente su estado y cuando tu firmware se termine de compilar, podras descargar tanto el firmware final, como su codigo fuente para el firmware, si asi lo deseas.

#### Example JSON Payload:

```json
{
  "keyboard": "clueboard/66/rev2",
  "keymap": "my_awesome_keymap",
  "layout": "LAYOUT_all",
  "layers": [
    ["KC_GRV","KC_1","KC_2","KC_3","KC_4","KC_5","KC_6","KC_7","KC_8","KC_9","KC_0","KC_MINS","KC_EQL","KC_GRV","KC_BSPC","KC_PGUP","KC_TAB","KC_Q","KC_W","KC_E","KC_R","KC_T","KC_Y","KC_U","KC_I","KC_O","KC_P","KC_LBRC","KC_RBRC","KC_BSLS","KC_PGDN","KC_CAPS","KC_A","KC_S","KC_D","KC_F","KC_G","KC_H","KC_J","KC_K","KC_L","KC_SCLN","KC_QUOT","KC_NUHS","KC_ENT","KC_LSFT","KC_NUBS","KC_Z","KC_X","KC_C","KC_V","KC_B","KC_N","KC_M","KC_COMM","KC_DOT","KC_SLSH","KC_RO","KC_RSFT","KC_UP","KC_LCTL","KC_LGUI","KC_LALT","KC_MHEN","KC_SPC","KC_SPC","KC_HENK","KC_RALT","KC_RCTL","MO(1)","KC_LEFT","KC_DOWN","KC_RIGHT"],
    ["KC_ESC","KC_F1","KC_F2","KC_F3","KC_F4","KC_F5","KC_F6","KC_F7","KC_F8","KC_F9","KC_F10","KC_F11","KC_F12","KC_TRNS","KC_DEL","BL_STEP","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","_______","KC_TRNS","KC_PSCR","KC_SLCK","KC_PAUS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(2)","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_PGUP","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(1)","KC_LEFT","KC_PGDN","KC_RGHT"],
    ["KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","RESET","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(2)","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","KC_TRNS","MO(1)","KC_TRNS","KC_TRNS","KC_TRNS"]
  ]
}
```

Como puedes ver el payload describe todos los aspectos necesarios del teclado para crear y generar el firmware. Cada capa is una simple lista de QMK keycodes de la misma longitud como el  `LAYOUT` macro del teclado. Si un teclado soporta multiple `LAYOUT` macros puedes especificar que macro usar.

## Submitting a Compile Job

Para compilar tu keymap a un firmware simplemente manda un POST con tu JSON al endpoint  `/v1/compile`. En el siguiente ejemplo, hemos colocad el JSON payload en un archivo nombrado `json_data`.

```
$ curl -H "Content-Type: application/json" -X POST -d "$(< json_data)" https://api.qmk.fm/v1/compile
{
  "enqueued": true,
  "job_id": "ea1514b3-bdfc-4a7b-9b5c-08752684f7f6"
}
```

## Checking The Status

Despues de enviar tu keymap, podras checar el status usando un simple llamado HTTP GET:

```
$ curl https://api.qmk.fm/v1/compile/ea1514b3-bdfc-4a7b-9b5c-08752684f7f6
{
  "created_at": "Sat, 19 Aug 2017 21:39:12 GMT",
  "enqueued_at": "Sat, 19 Aug 2017 21:39:12 GMT",
  "id": "f5f9b992-73b4-479b-8236-df1deb37c163",
  "status": "running",
  "result": null
}
```

Esto nos muestra que el trabajo ah pasado por el queue y que se esta realizando. Existen 5 status posibles:

* **failed**: Algo dentro del sistema de compilado se rompio.
* **finished**: La compilacion esta completa y deberias checar el `result` para ver los resultados.
* **queued**: El keymap esta espera de que el servidor de compilacion este disponible.
* **running**: La compilacion esta en progreso y deberia completarse pronto.
* **unknown**: Ocurrio un error serio y deberias [file a bug](https://github.com/qmk/qmk_compiler/issues).

## Examining Finished Results

Una vez el proceso de compilacion termine deberias checar el indice `result`. El valor de este indice es un hash que contienen varios bits de informacion:

* `firmware_binary_url`: Una lista de URLs para el firmware
* `firmware_keymap_url`: Una lista de URLs para el `keymap.c`
* `firmware_source_url`: Una lista de URLs para el codigo fuente del firmware
* `output`: El stdout y el stderr para el trabajo de compilaciones. Errores pueden ser encontrados en este indice.
