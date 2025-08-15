# EndToEndWasap

Este proyecto es una aplicación en C++ que implementa mensajería y comunicación de extremo a extremo, haciendo uso de OpenSSL para los servicios criptográficos. El proyecto está configurado con Visual Studio y utiliza un archivo de solución (.sln) para su compilación.

## Estructura del Proyecto

- **EndToEndWasap.sln**  
  Archivo de solución de Visual Studio para compilar el proyecto.

- **EndToEndWasap/**  
  - `*.vcxproj`, `*.vcxproj.filters`, `*.vcxproj.user`: Archivos de proyecto y configuración para Visual C++.
  - **bin/**: Directorio de salida con ejecutables.
  - **inc/**: Archivos de cabecera que incluyen:
    - `Client.h`, `CryptoHelper.h`, `NetworkHelper.h`, `Server.h`, `Prerequisites.h`
    - La carpeta `openssl/` contiene las implementaciones y definiciones de OpenSSL utilizadas en el proyecto.
  - **src/**: Código fuente en C++.
    - `Client.cpp`: Implementación del cliente.
    - `CrtyptoHelper.cpp`: (Nota: Verifique la ortografía, podría ser "CryptoHelper.cpp")  
      Encapsula funciones criptográficas (por ejemplo, generación de claves RSA, obtención de la clave pública en formato PEM).
    - `E2E.cpp`: Código principal y de inicio, probablemente se encarga de la coordinación de la comunicación.
    - `NetworkHelper.cpp`: Funciones auxiliares para la comunicación de red.
    - `Server.cpp`: Implementación del servidor.
  
- **intermediate/**  
  Archivos generados por Visual Studio para la compilación y depuración.
  
- **lib/**  
  Contiene bibliotecas necesarias (archivos de DLL o estáticos) que se utilizan en el proyecto.  
  - Las carpetas VC/x64 y x64/ incluyen bibliotecas y otros recursos compilados para la arquitectura x64.

- **bin/**  
  Además de la salida de compilación, se incluyen dependencias de OpenSSL:
  - `libcrypto-3-x64.dll` y `libssl-3-x64.dll`

## Requisitos

- **Compilador:** Visual Studio con soporte para C++.
- **Dependencias:**  
  OpenSSL se utiliza para operaciones criptográficas. Los archivos de cabecera y bibliotecas están incluidos en la carpeta `inc/openssl/` y en `bin/`.

## Compilación

Abre el archivo `EndToEndWasap.sln` en Visual Studio. Una vez abierto, puedes compilar el proyecto utilizando la opción de Build:
  
```sh
Ctrl + Shift + B
