# QMK Compiler Development Guide

Esta pagina intenta introducir los desarrolladores al compilador de QMK. No se revisaran nada en detalle, para ello deberas de leer el codigo. En vez se pretende dar un marco de referencia para ayudar tu entendimiento mientras lees el codigo. 

# Overview

La API de compilacion de QMK consiste de algunas partes:

![Architecture Diagram](https://raw.githubusercontent.com/qmk/qmk_api/master/docs/architecture.svg)

Los Clientes de la API interactuan exclusivamente con el servicio de la API. Esto es donde se envian trabajos, se checa el estatus y se descargan los resultados. La API de servicio inserta procesos de compilacion en una [Redis Queue](https://python-rq.org) y checa tanto RQ como S3 por los resultados de esos trabajos.

Workers buscan nuevos trabajos de compilacion desde el RQ, los compilan y despues los suben la fuente y el binario a un motor de almacenaje compatible S3.

# Workers

Los Workers son responsables de la compilacion, cuando un worker toma un trabajo de la RQ, hace muchas cosas para complerar dicho trabajo: 

* Hace una checkout del qmk_firmware
* Usa las capas y la metada del teclado suministrada para compilar un `keymap.c`
* Use the supplied layers and keyboard metadata to build a `keymap.c`
* Construye el firmware
* Hace un zip del fuente
* Sube el firmware, la fuente en zip y el archivo de metadata al S3
* Reporta el estatus del trabajo a la RQ

# API Service

La API de servicio es relativamente una simple aplicacion Flask, solo hay algunas vistas que deberias de entender.

## @app.route('/v1/compile', methods=['POST'])

Este es el endpoint principal para la API. La interaccion del cliente inicia aqui, con una peticion del tipo Post con un documento JSON que describe el teclado y la api hace un trabajo basico de validacion de dicho JSON antes de enviar el trabajo de compilacion.

## @app.route('/v1/compile/&lt;string:job_id&gt;', methods=['GET'])

Este es el endpoint mas utilizado. obtiene los detalles de los trabajos del redis, para  checar su disponibilidad o los detalles del trabajo cacheado en el S3 si es que no esta disponible.

## @app.route('/v1/compile/&lt;string:job_id&gt;/download', methods=['GET'])

Este metodo permite al usuario descargar el archivo del firmware.

## @app.route('/v1/compile/&lt;string:job_id&gt;/source', methods=['GET'])

Este metodo permite al usuario descargar la fuente de su firmware.
