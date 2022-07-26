# Unit Testing

Si eres nuevo al unit testing, puedes encontrar buenos recursos en internet. Sin embargo, la mayoría está dividido en pequeñas partes y hay muchas opiniones distintas, por lo que no se da ninguna reomedación.

En cambio, se recomiendan estos 2 libros, que explican dos estilos diferentes de testing en detalle.

* "Test Driven Development: By Example: Kent Beck"
* "Growing Object-Oriented Software, Guided By Tests: Steve Freeman, Nat Pryce"

Si prefieres videos, están los _Uncle Bob's [Clean Coders Videos](https://cleancoders.com/)_, que desgraciadamente cuestan un poco, especialmente si quieres ver muchos de ellos. Pero James Shore tiene una serie de videos gratis _[Let's Play](https://www.jamesshore.com/Blog/Lets-Play)_.

## Google Test y Google Mock

Es posible probar tu código usando [Google Test](https://github.com/google/googletest). Este framework tambien incluye otro componente para escribir pruebas, llamado "Google Mock". Para información sobre cómo escribir las pruebas, lee la documentación de dicho sitio.

## Uso of C++

Nótese que Google Test está escrito en C++, por lo que las pruebas también estarlo incluso si el resto de QMK es C. Esto no debería ser un problema si no conoces C++, dado que hay documentación bastante clara sobre las características de C++ requeridas, y puedes escribir el resto del código como lo harías en C. Algunos errores de compilación puede dar miedo, pero si los lees con cuidado todo debe estar ok.

Una cosa a tener en cuenta es que debes usar `extern "C"` alrededor de cualquier trozo de código en C.

## Añadir Tests para Características Nuevas o Existentes

Si quieres hacer pruebas de una característica, echa un vistazo a los tests existentes, por ejemplo en la carpeta `quantum/sequencer/tests`. Y sigue estos pasos para crear una estructura similar.

1. Si no existe ya, añade una subcarpeta a la carpeta que contiene la característica.
2. Crea un `testlist.mk` y un `rules.mk` en esa carpeta.
3. Incluye esos archivos al `testlist.mk` y `build_test.mk` del directorio raíz, respectivamente.
4. Añade un nuevo nombre para tu grupo de pruebas en el archivo `testlist.mk`. Cada grupo definido será un ejecutable distinto. Así es como puedes reemplazar diferentes partes. Recuerda que es útil añadir un prefijo común, como en los tests existentes. El motivo es que el comando `make` permite hacer filtrado de substring, de esta forma se puede correr fácilmente un subconjunto de pruebas.
5. Define los archivos de código fuente, así como sus configuraciones en el archivo `rules.mk`.
   * `_SRC` para código fuente
   * `_DEFS` para definiciones adicionales
   * `_INC` para incluir carpetas adicionales
6. Escribe los tests en un nuevo archivo cpp dentro de la carpeta de tests que has creado. Este archivo tiene que ser uno de los incluidos en `rules.mk`.

Fíjate como hay muchos tests distintos, cada uno probando una parte diferente. Cada uno compila solo lo mínimo necesario para los test. Se recomienda que intentes hacer lo mismo. Puedes consultar [Matt Hargett "Advanced Unit Testing in C & C++](https://www.youtube.com/watch?v=Wmy6g-aVgZI) para más información..

## Ejecutar los Tests

Para ejecutar todos los tests, escribe `make test:all`. También pueden ejecutarse tests filtrando `make test:substring`. Los tests siempre se compilan con el compilador nativo de tu plataforma, por lo que se corren como cualquier otro programa en tu ordenador.

## Depurar los Tests

Si hay problemas con tus tests, puedes encontrar el ejecutable en la carpeta `./build/test`. Deberías poder ejecutarlos con GDB o un depurador similar.

Para reenviar cualquier [mensaje de debug](unit_testing.md#debug-api) a `stderr`, puedes ejecutar los tests con la opción `DEBUG=1`. Por ejemplo

```
make test:all DEBUG=1
```

Alternativamente, añade `CONSOLE_ENABLE=yes` al archivo `rules.mk` de los tests.

## Tests de Integración

Aún no es posible hacer un test de integración completa, donde se compilaría todo el firmware y definiría un keymap a testear. Sin embargo, hay planes para hacerlo porque hacer tests de esa manera sería más fácil, al menos para gente sin experiencia en unit testing.

En ese modelo, podrías simular la entrada, y esperar determinadas salidas del teclado simulado.

# Seguimiento de Variables :id=tracing-variables

A veces podrías querer saber cuándo o dónde ha cambiado una variable, y esto puede ser un desafio sin un depurador. Por supuesto que es posible añadir `print`s para ello, pero también puedes activar la opción de seguimiento de variables. Funciona tanto para cambios realizados por el código como corrupción de memoria.

Para activarla, añade `VARIABLE_TRACE=x` al final de tu comando `make`. `x` representa el número de variables que quieres seguir, normalmente 1.

Entonces, en la parte del código que corresponda, llama a `ADD_TRACED_VARIABLE`, para iniciar el seguimiento. Por ejemplo, para seguir los cambios de capa, puedes hacer:
```c
void matrix_init_user(void) {
  ADD_TRACED_VARIABLE("layer", &layer_state, sizeof(layer_state));
}
```

Esto añade una variable de seguimiento llamada "layer" (el nombre es solo para tí), que supervisa la posición de memoria de `layer_state`. Hace el seguimiento de 4 bytes (el tamaño de `layer_state`), de forma que se reportará cualquier modificación. Por defecto no se puede usar un tamaño mayor a 4, pero puedes cambiarlo añadiendo `MAX_VARIABLE_TRACE_SIZE=x` al final de tu comando `make`.

Para detectar cambios en las variables, deberias llamar a `VERIFY_TRACED_VARIABLES` en las partes que creas que modifican la variable. Si la raible se modifica, te dirá entre que par de llamadas a `VERIFY_TRACED_VARIABLES` ha ocurrido el cambio. Entonces puedes añadir más llamadas para aislar aún más el cambio. No se recomienda llenar el código con estas llamadas, es mejor empezar con pocas e ir añadiendo como si se hiciera una búsqueda binaria. También puedes borrar las que no uses, ya que cada una almacena el nombre del archivo y el número de línea en ROM, por lo que podrías quedarte sin memoria.

Recuerda borrar todo el código de tracing una vez encontrado el bug, ya que no quieres querar una pull request con código de depuración.