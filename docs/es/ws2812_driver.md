# Driver para WS2812
Este driver permite las funcionalidades [RGB Lighting](es/feature_rgblight.md) y [RGB Matrix](es/feature_rgb_matrix.md).

Actualmente, QMK soporta los siguientes LEDs direccionables (sin embargo, el LED blanco en las versiones RGBW no está soportado):

    WS2811, WS2812, WS2812B, WS2812C, etc.
    SK6812, SK6812MINI, SK6805

Estos LEDs se llaman "direccionables" porque en vez de usar un cable para cada color, cada LED tiene un pequeño microchop que entiende un protocolo especial enviado en un solo cable. Este chip envía el resto de datos al siguiente LED, permitiendo conectarlos entre sí. De esta forma se puede controlar fácilmente el color de LED de forma individual.

## Tipos de Driver Permitidos

|          | AVR                | ARM                |
|----------|--------------------|--------------------|
| bit bang | :heavy_check_mark: | :heavy_check_mark: |
| I2C      | :heavy_check_mark: |                    |
| SPI      |                    | :heavy_check_mark: |
| PWM      |                    | :heavy_check_mark: |

## Configuración de driver

### Todos los drivers

Diferentes versiones de LED direccionables varían en los requisitos para el periodo T<sub>RST</sub>.
El valor por defecto es 280 µs, lo que debería funcionar en la mayoría de casos, pero se puede editar en tu archivo config.h. por ejemplo:

```c
#define WS2812_TRST_US 80
```

#### Orden de Bytes

Algunas variantes del WS2812 pueden tener los colores en un orden (lógico o físico) diferente. Por ejemplo, el WS2812B-2020 intercambia los LEDs rojo y verde, lo que causa que se muestren colores incorrectos porque el orden por defecto en el que se envían los datos por el cable es GRB.
En estas situaciones, puedes cambiar el orden definiendo `WS2812_BYTE_ORDER` con uno de los siguientes valores:

|Orden de bytes                   |Dispositivos conocidos              |
|---------------------------------|------------------------------------|
|`WS2812_BYTE_ORDER_GRB` (defecto)| Mayoría de WS2812's, SK6812, SK6805|
|`WS2812_BYTE_ORDER_RGB`          |WS2812B-2020                        |
|`WS2812_BYTE_ORDER_BGR`          |TM1812                              |


### Bitbang
Driver por defecto, la ausencia de configuración asume esta opción. Para configurarlo, añade a tu rules.mk:

```make
WS2812_DRIVER = bitbang
```

!> Este driver no es acelerado por hardware accelerated y podría no ser eficiente en sistemas muy cargados.

#### Ajustando la temporización de bits

La topología de comunicación de los LED WS2812 depende de una ventana temporal serializada. Algunas variantes de los LEDs tienen requisitos temporales distintos, por ejemplo el SK6812.
Puedes ajustar estos parámetros con la definición de las siguientes macros:

| Macro               |Por defecto                                 | AVR                | ARM                |
|---------------------|--------------------------------------------|--------------------|--------------------|
|`WS2812_TIMING`      |`1250`                                      | :heavy_check_mark: | :heavy_check_mark: |
|`WS2812_T0H`         |`350`                                       | :heavy_check_mark: | :heavy_check_mark: |
|`WS2812_T0L`         |`WS2812_TIMING - WS2812_T0H`                |                    | :heavy_check_mark: |
|`WS2812_T1H`         |`900`                                       | :heavy_check_mark: | :heavy_check_mark: |
|`WS2812_T1L`         |`WS2812_TIMING - WS2812_T1H`                |                    | :heavy_check_mark: |

### I2C
Destinado a diseños donde el control de los WS2812 está delegado a una segunda MCU. Actualmente el driver está limitado a AVR dado que los consumidores conocidos son ps2avrGB/BMC. Para configurarlo, añade a tu your rules.mk:

```make
WS2812_DRIVER = i2c
```

Configura el hardware en config.h:
```c
#define WS2812_ADDRESS 0xb0 // default: 0xb0
#define WS2812_TIMEOUT 100 // default: 100
```

### SPI
Destinado a teclados con STM32 donde el control de los WS2812 se delega en un dispositivo SPI. La ventaja es que el uso de DMA elimina la carga del protocolo WS2812 del MCU. En este driver `RGB_DI_PIN` es el pin configurado como SPI MOSI. Dada la naturaleza de reutilizar SPI para controlar los LEDs, los otros pins SPI (MISO y SCK)**deben** quedar sin utilizar. Para configurarlo, añade esto a tu rules.mk:

```make
WS2812_DRIVER = spi
```

Configura el hardware en config.h:
```c
#define WS2812_SPI SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // "alternate function" del pin MOSI, consulta la hoja de datos para los valores correctos en tu MCU. default: 5
#define WS2812_SPI_SCK_PIN B3 // requerido para F072, quizás para otros -- pin SCK, consulta la hoja de datos para los valores correctos en tu MCU. default: unspecified
#define WS2812_SPI_SCK_PAL_MODE 5 // "alternate function" del pin SCK, consulta la hoja de datos para los valores correctos en tu MCU. default: 5
```

También debes activar la funcionalidad SPI en tu halconf.h y mcuconf.h

#### Modo Buffer Circular
Algunos teclados puedes parpadear en el modo de buffer normal. Para arreglar este problema, se puede activar el modo de buffer circular.

Por defecto, el modo de buffer circular está desactivado.

Para habilitar este modo alternativo, añade a tu `config.h`:
```c
#define WS2812_SPI_USE_CIRCULAR_BUFFER
```

#### Configurar velocidad de datos con divisor
Para ajustar los baudios a los que el periférico SPI se configura, los usuarios tienen que calcular la velocidad a partir de los relojes dados por el STM32CubeMX.

Solo los divisores de 2, 4, 8, 16, 32, 64, 128 y 256 son soportados por hardware.

|Define              |Por defecto|Description                          |
|--------------------|-----------|-------------------------------------|
|`WS2812_SPI_DIVISOR`|`16`       |Divisor del reloj para periférico SPI|

#### Notas de testeo

Aunque no es una lista completa, la siguiente tabla contiene escenarios que han sido parcialmente validados:

|      | SPI1                                        | SPI2                                    | SPI3                  |
|------|---------------------------------------------|-----------------------------------------|-----------------------|
| f072 | ?                                           | B15 :heavy_check_mark: (needs SCK: B13) | N/A                   |
| f103 | A7 :heavy_check_mark:                       | B15 :heavy_check_mark:                  | N/A                   |
| f303 | A7 :heavy_check_mark: B5 :heavy_check_mark: | B15 :heavy_check_mark:                  | B5 :heavy_check_mark: |

*Otros dispositivos soportados por ChibiOS o pines podrían funcionar, es muy dependiente del chip y la configuración.*

### PWM

Destinado a tablas STM32 donde el soporte WS2812 se realiza con un timer PWM y un stream DMA. La ventaja es que el uso de DMA reduce la carga del MCU. Para configurarlo, añade a tu rules.mk:

```make
WS2812_DRIVER = pwm
```

Configura el hardware en tu config.h:
```c
#define WS2812_PWM_DRIVER PWMD2  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // "alternate function" del pin, consulta la hoja de datos para los valores correctos en tu MCU. default: 2
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define para un timer complementario (TIMx_CHyN); omite para un timer normal (TIMx_CHy).
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, consulta la hoja de datos para los valores correctos en tu MCU.
#define WS2812_DMA_CHANNEL 2  // Canal DMA para TIMx_UP, consulta la hoja de datos para los valores correctos en tu MCU.
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM2_UP // Configuración DMAMUX para TIMx_UP -- solo es necesario si tu MCU tiene un periférico DMAMUX, consulta la hoja de datos para los valores correctos en tu MCU.
```

Ten en cuenta que usar un timer complementario (TIMx_CHyN) solo es posible para relojes de control avanzado (TIM1, TIM8, TIM20 on STM32), y la opción `STM32_PWM_USE_ADVANCED` en mcuconf.h debe estar configurada a `TRUE`. Salidas complementarias para timer de propósito general no está soportado debido a limitaciones de ChibiOS.

También debes activar PWN en tu halconf.h y mcuconf.h

#### Notas de testeo

Aunque no es una lista completa, la siguiente tabla contiene escenarios que han sido parcialmente validados:

| | Estado |
|-|-|
| f072 | ? |
| f103 | :heavy_check_mark: |
| f303 | :heavy_check_mark: |
| f401/f411 | :heavy_check_mark: |

*Otros dispositivos soportados por ChibiOS o pines podrían funcionar, es muy dependiente del chip y la configuración.*
 
### Configuración Push Pull y Drenaje Abierto
La configuración por defecto es push-pull en el pin definido.
Esto se puede configurar para bitbang, PWM y SPI.

Nota: Esto solo aplica a STM32.

 Para configurar `RGB_DI_PIN` a drenaje abierto, añade a tu config.h: 
```c
#define WS2812_EXTERNAL_PULLUP
```
