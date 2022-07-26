# Traduciendo la documentación de QMK

Todos los archivos del directorio raíz (`docs/`) deben estar en Inglés - todos los demás idiomas deben estar en subcarpetas con el código de idioma ISO 639-1, seguido por `-` y el país cuando sea relevante. [Lista de códigos de idioma comunes](https://www.andiamo.co.uk/resources/iso-language-codes/). Si la carpeta no existe, debes crearla. Cada archivo traducido debe tener el mismo nombre que la versión en Inglés, para que las cosas funcionen correctamente.

Un archivo `_summary.md` debe existir en esta carpeta con una lista de enlaces a cada archivo, con el nombre traducido y el enlace precedido de la carpeta de idioma:

```markdown
 * [QMK简介](zh-cn/getting_started_introduction.md)
```

Todos los enlaces a otras páginas de documentación también deben ser precedidos por la carpeta de idioma. Si el enlace es a una parte específica de la página (por ejemplo, una cabecera), debes usar el ID Inglés:

```markdown
[建立你的环境](zh-cn/newbs-getting-started.md#set-up-your-environment)

## 建立你的环境 :id=set-up-your-environment
```

Una vez hayas terminado de traducir un nuevo idioma, también tendrás que modificar los siguientes archivos:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)  
  Cada línea debe contener una bandera con un [código emoji GitHub](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md#country-flag) seguida del idioma, escrito en el propio idioma:

  ```markdown
   - [:cn: 中文](/zh-cn/)
  ```

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)  
  Tanto `placeholder` como `noData` deben tener una entrada para la carpeta del idioma en una cadena de texto:

  ```js
  '/zh-cn/': '没有结果!',
  ```

  El objeto `nameLink`, para configurar el enlace "QMK Firmware" en el lateral, también debe añadirse:

  ```js
  '/zh-cn/': '/#/zh-cn/',
  ```

  Y asegúrate de añadir la carpeta del idioma a la lista `fallbackLanguages`, para que pueda redirigir a la documentación en Inglés en vez de dar un error 404:

  ```js
  fallbackLanguages: [
    // ...
    'zh-cn',
    // ...
  ],
  ```

## Vista Previa de la Traducción

Consulta [Vista previa de la Documentación](contributing.md#previewing-the-documentation) para configurar la documentación en logal - deberías poder seleccionar tu nuevo idioma en el menú "Translations" arriba a la derecha.

Una vez estés content@ con tu trabajo, abre un pull request!
