# ADC Driver

QMK puede delegar la conversion Analoga-a-Digital (ADC) en MCUs soportados para medir voltages en ciertos pines. Esto puede ser util para implementar ciertas cosas como indicadores de nivel de baterias para teclados Bluetooth, or controles de volumen usando potenciometros, al contrario de [codificador rotatorio](feature_encoders.md). 

Este driver actualmente soporta tanto AVR como una limitada seleccion de dispositivos ARM. Los valores retornados son 10-bit intergers (0-1023) mapeados entre 0v y VCC (usualmente 5V o 3.3V para AVR, 3.3V solo para ARM), sin embargo hay mas flexibilidad en el control de la operacion en ARM atravez de `#define` si es que se necesita mas precision.

## Uso

Para usar este driver, agrega la siguiente regla a `rules.mk`:

```make
SRC += analog.c
```

Despues agrega este include en la parte superior de tu codigo:

```c
#include "analog.h"
```

## Canales

### AVR

|Channel|AT90USB64/128|ATmega16/32U4|ATmega32A|ATmega328/P|
|-------|-------------|-------------|---------|----------|
|0      |`F0`         |`F0`         |`A0`     |`C0`      |
|1      |`F1`         |`F1`         |`A1`     |`C1`      |
|2      |`F2`         |             |`A2`     |`C2`      |
|3      |`F3`         |             |`A3`     |`C3`      |
|4      |`F4`         |`F4`         |`A4`     |`C4`      |
|5      |`F5`         |`F5`         |`A5`     |`C5`      |
|6      |`F6`         |`F6`         |`A6`     |*         |
|7      |`F7`         |`F7`         |`A7`     |*         |
|8      |             |`D4`         |         |          |
|9      |             |`D6`         |         |          |
|10     |             |`D7`         |         |          |
|11     |             |`B4`         |         |          |
|12     |             |`B5`         |         |          |
|13     |             |`B6`         |         |          |

<sup>\* El ATmega328/P posee dos canales ADC extras; sin embargo no estan prensentes en el DIP pinout, and no estan compartidos con los GPIO pins. Puedes usar `adc_read()` directamente para ganar acceso a estos.</sup>

### ARM

Nota que algunos de estos pins estan duplicados en ADCs con el mismo canal. Esto es porque los pines pueden ser usados para cualquier ADC.

Tambien nota que F0 y F3 usan esquemas diferentes de nomenclatura. El F0 tiene un unico ADC y los canales son 0-indexed, mientras que F3 tiene 4 ADC y los canales son 1-indexed. Esto es porque F0 usa la implentacion `ADCv1` de los ADC, mientras que F3 usa la implementacion `ADCv3`.

|ADC|Channel|STM32F0xx|STM32F1xx|STM32F3xx|STM32F4xx|
|---|-------|---------|---------|---------|---------|
|1  |0      |`A0`     |`A0`     |         |`A0`     |
|1  |1      |`A1`     |`A1`     |`A0`     |`A1`     |
|1  |2      |`A2`     |`A2`     |`A1`     |`A2`     |
|1  |3      |`A3`     |`A3`     |`A2`     |`A3`     |
|1  |4      |`A4`     |`A4`     |`A3`     |`A4`     |
|1  |5      |`A5`     |`A5`     |`F4`     |`A5`     |
|1  |6      |`A6`     |`A6`     |`C0`     |`A6`     |
|1  |7      |`A7`     |`A7`     |`C1`     |`A7`     |
|1  |8      |`B0`     |`B0`     |`C2`     |`B0`     |
|1  |9      |`B1`     |`B1`     |`C3`     |`B1`     |
|1  |10     |`C0`     |`C0`     |`F2`     |`C0`     |
|1  |11     |`C1`     |`C1`     |         |`C1`     |
|1  |12     |`C2`     |`C2`     |         |`C2`     |
|1  |13     |`C3`     |`C3`     |         |`C3`     |
|1  |14     |`C4`     |`C4`     |         |`C4`     |
|1  |15     |`C5`     |`C5`     |         |`C5`     |
|1  |16     |         |         |         |         |
|2  |0      |         |`A0`¹    |         |`A0`²    |
|2  |1      |         |`A1`¹    |`A4`     |`A1`²    |
|2  |2      |         |`A2`¹    |`A5`     |`A2`²    |
|2  |3      |         |`A3`¹    |`A6`     |`A3`²    |
|2  |4      |         |`A4`¹    |`A7`     |`A4`²    |
|2  |5      |         |`A5`¹    |`C4`     |`A5`²    |
|2  |6      |         |`A6`¹    |`C0`     |`A6`²    |
|2  |7      |         |`A7`¹    |`C1`     |`A7`²    |
|2  |8      |         |`B0`¹    |`C2`     |`B0`²    |
|2  |9      |         |`B1`¹    |`C3`     |`B1`²    |
|2  |10     |         |`C0`¹    |`F2`     |`C0`²    |
|2  |11     |         |`C1`¹    |`C5`     |`C1`²    |
|2  |12     |         |`C2`¹    |`B2`     |`C2`²    |
|2  |13     |         |`C3`¹    |         |`C3`²    |
|2  |14     |         |`C4`¹    |         |`C4`²    |
|2  |15     |         |`C5`¹    |         |`C5`²    |
|2  |16     |         |         |         |         |
|3  |0      |         |`A0`¹    |         |`A0`²    |
|3  |1      |         |`A1`¹    |`B1`     |`A1`²    |
|3  |2      |         |`A2`¹    |`E9`     |`A2`²    |
|3  |3      |         |`A3`¹    |`E13`    |`A3`²    |
|3  |4      |         |`F6`¹    |         |`F6`²    |
|3  |5      |         |`F7`¹    |`B13`    |`F7`²    |
|3  |6      |         |`F8`¹    |`E8`     |`F8`²    |
|3  |7      |         |`F9`¹    |`D10`    |`F9`²    |
|3  |8      |         |`F10`¹   |`D11`    |`F10`²   |
|3  |9      |         |         |`D12`    |`F3`²    |
|3  |10     |         |`C0`¹    |`D13`    |`C0`²    |
|3  |11     |         |`C1`¹    |`D14`    |`C1`²    |
|3  |12     |         |`C2`¹    |`B0`     |`C2`²    |
|3  |13     |         |`C3`¹    |`E7`     |`C3`²    |
|3  |14     |         |         |`E10`    |`F4`²    |
|3  |15     |         |         |`E11`    |`F5`²    |
|3  |16     |         |         |`E12`    |         |
|4  |1      |         |         |`E14`    |         |
|4  |2      |         |         |`E15`    |         |
|4  |3      |         |         |`B12`    |         |
|4  |4      |         |         |`B14`    |         |
|4  |5      |         |         |`B15`    |         |
|4  |6      |         |         |`E8`     |         |
|4  |7      |         |         |`D10`    |         |
|4  |8      |         |         |`D11`    |         |
|4  |9      |         |         |`D12`    |         |
|4  |10     |         |         |`D13`    |         |
|4  |11     |         |         |`D14`    |         |
|4  |12     |         |         |`D8`     |         |
|4  |13     |         |         |`D9`     |         |
|4  |14     |         |         |         |         |
|4  |15     |         |         |         |         |
|4  |16     |         |         |         |         |

<sup>¹ Apartir de ChibiOS 20.3.4, el driver ADC para dispositivos STM32F1xx solo soporta ADC1, por lo tanto cualquier configuracion involucrando ADC2 o ADC3 actualmente no puede ser usada. En particular, pines `F6`…`F10`, los cuales estan presentes en algunos dispositivos STM32F103x[C-G], no pueden ser usados algunos ADC inputs debido a limitaciones de este driver.</sup>

<sup>² Not todos los dispositivos STM32F4xx tienen ADC2 o ADC3, por lo tanto algunas configutaciones mostradas en esta tabla podria no estar disponibles; en particular, pines `F4`…`F10` no pueden ser usados como entradas ADC en dispositivos que no tienen ADC3. Comprueba en la hoja de informacion del disposituvo que funciones son soportadas.</sup>

## Functions

### AVR

|Function                    |Description                                                                                                        |
|----------------------------|-------------------------------------------------------------------------------------------------------------------|
|`analogReference(mode)`     |Configura la fuente de voltaje de referencia analoga. Debe ser una de `ADC_REF_EXTERNAL`, `ADC_REF_POWER` o `ADC_REF_INTERNAL`.|
|`analogReadPin(pin)`        |Lee el valor del pin especificado, eg. `F6` para ADC6 en el ATmega32U4.                                     |
|`pinToMux(pin)`             |Traduce cierto pin a un valor mux. Si un pin no soportado es seleccionado, regresa un valor de mux de "0V (GND)".       |
|`adc_read(mux)`             |Lee el valor del ADC acorde al mux especificado. Verifica la hoja de datos de tu MCU's para mas informacion.        |

### ARM

|Function                    |Description                                                                                                                                                                                                                                                                                           |
|----------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`analogReadPin(pin)`        |Lee el valor del pin especificado, eg. `A0` para el canal 0 en el STM32F0 y ADC1 canal 1 en el STM32F3. Nota que un pin puede ser utilizado para multiples ADCs, tomara el ADC con la menor numeracion para esta funcion. eg. `C0` sera el canal 6 del ADC 1 cuando pueda ser usado para el ADC 2 tambien.|
|`analogReadPinAdc(pin, adc)`|Lee el valor de un pin especificado y ADC, eg. `C0, 1` obtendra la lectura del canal 6, ADC2 en vez de ADC 1. Nota que los ADCs son 0-indexed para esta funcion.   |
|`pinToMux(pin)`             |Tranlada cierto pin a la combinacion de canal y ADC. Si es un pin no soportado , regresara el valor de mux para "0V (GND)".                                                                                                                                                                        |
|`adc_read(mux)`             |Lee el valor del ADC acorde a la combinacion de pin y ADC especidicada. Mira la hoja de datos de tu MCU's para mas informacion.                                                                                                                                                                       |

## Configuration

## ARM

La implementacion ARM de los ADC tiene unas opciones adicionales que puedes sobre escribir en tu teclado para cambiar su forma de operacion. Consulta el codigo `hal_adc_ldd.h` en ChibiOs para mas documentacion de las opciones disponibles sobre tu MCU en especifico.

|`#define`            |Type  |Default                                       |Description                                                                                                                                                                                                 |
|---------------------|------|----------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`ADC_CIRCULAR_BUFFER`|`bool`|`false`                                       |If `true`, entonces la implementacion usara un buffer circular.                                                                                                                                              |
|`ADC_NUM_CHANNELS`   |`int` |`1`                                           |Configura el numero de canales que seran escaneados como parte de la operacion del ADC. La implementacion actual solo soporta `1`.                                                                                 |
|`ADC_BUFFER_DEPTH`   |`int` |`2`                                           |Configuta la profundidad de cadara resultado. Desde que solo buscamos resultados de 10-bits por default, se configuro a 2 bytes por lo que se puede contener un valor. Esto podria ser configurado a 1 si optas por 8-bit o un resultado menor.|
|`ADC_SAMPLING_RATE`  |`int` |`ADC_SMPR_SMP_1P5`                            |Configta el numero de muestas del ADC. Por default, se configura a la opcion mas rapida.                                                                                                                            |
|`ADC_RESOLUTION`     |`int` |`ADC_CFGR1_RES_10BIT` or `ADC_CFGR_RES_10BITS`|La resolucion de tu resultado. Escoginos 10 bits por default, pero puedes optar por 12,10, 8, o 6 bit. Diferentes MCUs usara diferentes nombres para las constantes de resolucion.                              |
