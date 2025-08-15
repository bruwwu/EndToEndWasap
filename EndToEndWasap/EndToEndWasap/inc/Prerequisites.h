#pragma once

// Evita conflictos con macros min/max de Windows
#define NOMINMAX

// Librerías estándar C++ usadas comúnmente en el proyecto

#include <string>      ///< Manejo de cadenas de texto
#include <vector>      ///< Uso de contenedores dinámicos tipo array
#include <iostream>    ///< Entrada y salida estándar (cout, cin, etc.)
#include <cstring>     ///< Funciones de manejo de memoria tipo C (e.g., memcpy, strcmp)
#include <limits>      ///< Constantes de límites numéricos (e.g., INT_MAX)
#include <thread>      ///< Soporte para ejecución concurrente mediante hilos
