# Driver UART

Los drives de UART utilizados en QMK tienen un conjunto de funciones comunes para permitir portabilidad entre distintos MCU.

Actualmente, este driver no soporta control de flujo con hardware (pines `RTS` y `CTS`) aunque estén disponibles, pero podría hacerlo en un futuro.

##  en AVR

No es necesaria configuración especial - simplemente conecta `RX` y `TX` en tu dispositivo a los pines opuestos en la MCU

|MCU          |`TX`|`RX`|`CTS`|`RTS`|
|-------------|----|----|-----|-----|
|ATmega16/32U2|`D3`|`D2`|`D7` |`D6` |
|ATmega16/32U4|`D3`|`D2`|`D5` |`B7` |
|AT90USB64/128|`D3`|`D2`|*n/a*|*n/a*|
|ATmega32A    |`D1`|`D0`|*n/a*|*n/a*|
|ATmega328/P  |`D1`|`D0`|*n/a*|*n/a*|

## Configuración en ChibiOS/ARM

Necesitarás determinar qué pines pueden usarse para UART -- como ejemplo, los STM32 normalmente tienen varios periféricos UART, llamados USART1, USART2, USART3, etc.

Para habilitar UART, modifica el `halconf.h` de tu dispositivo, para habilitar el driver serie.

```c
#define HAL_USE_SERIAL TRUE
```

Después modifica el 's `mcuconf.h` para activar el periférico que hayas elegido, por ejemplo.

```c
#undef STM32_SERIAL_USE_USART2
#define STM32_SERIAL_USE_USART2 TRUE
```

Para la configuración, debes conectar el periférico acorde a la hoja de datos de tu MCU -- los valores por defecto de estas configuraciones son los del Proton-C (STM32F303).

|`config.h`        |Descripción                                                    |Valor por defecto|
|--------------------------|---------------------------------------------------------------|-------------|
|`#define SERIAL_DRIVER`   |Periférico USART a usar - USART1 -> `SD1`, USART2 -> `SD2` etc.|`SD1`        |
|`#define SD1_TX_PIN`      |Pin a usar para TX                                          |`A9`         |
|`#define SD1_TX_PAL_MODE` |Modo de función alternativa para TX                             |`7`          |
|`#define SD1_RX_PIN`      |Pin a usar para RX                                          |`A10`        |
|`#define SD1_RX_PAL_MODE` |Modo de función alternativa para RX                             |`7`          |
|`#define SD1_CTS_PIN`     |Pin a usar para CTS                                         |`A11`        |
|`#define SD1_CTS_PAL_MODE`|Modo de función alternativa paraCTS                            |`7`          |
|`#define SD1_RTS_PIN`     |Pin a usar para RTS                                         |`A12`        |
|`#define SD1_RTS_PAL_MODE`|Modo de función alternativa para RTS                            |`7`          |

## Funciones

### `void uart_init(uint32_t baud)`

Inicializa el driver UART. Esta función solo se debe llamar una vez, antes de las funciones más abajo.

#### Argumentos

 - `uint32_t baud`  
   La velocidad a la que transmitir y recibir. Puede depender del dispositivo con el que te comuniques. Valores usuales son 1200, 2400, 4800, 9600, 19200, 38400, 57600, and 115200.

---

### `void uart_write(uint8_t data)`

Envía un byte.

#### Argumentos

 - `uint8_t data`  
   El byte a escribir.

---

### `uint8_t uart_read(void)`

Recibe un byte.

#### Valor Devuelto

El byte leído del buffer de recepción. Esta función bloqueará si el buffer está vacío (es decir, no hay datos para leer).

---

### `void uart_transmit(const uint8_t *data, uint16_t length)`

Transmite varios bytes.

#### Argumentos

 - `const uint8_t *data`  
   Un puntero hacia los datos a enviar.
 - `uint16_t length`  
   El número de bytes a escribir. Ten cuidado de no superar la longitud de `data`.

---

### `void uart_receive(char *data, uint16_t length)`

Recibe varios bytes.

#### Argumentos

 - `uint8_t *data`  
   Un punto al buffer donde se escribirá lo recibido.
 - `uint16_t length`  
   El número de bytes a leer. Ten cuidado de no superar la longitud de `data`.

---

### `bool uart_available(void)`

Devuelve si el buffer de recepción contiene datos. LLama a esta función para determinar si `uart_read()` devolverá datos inmediatamente.

#### Valor Devuelto

`true` si la longitud del buffer de recepción es distinta de 0.
