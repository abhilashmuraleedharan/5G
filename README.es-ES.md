

# Repositorio de Utilidades 5G

Bienvenido al repositorio de Utilidades 5G, tu conjunto de herramientas integral para el análisis, diseño y simulación de sistemas de comunicación 5G. Este repositorio está diseñado como un centro central donde desarrolladores, investigadores, ingenieros y estudiantes pueden acceder y contribuir a una colección en crecimiento de herramientas y scripts diseñados para mejorar la interacción con la tecnología 5G.

## Origen

Este repositorio está inspirado en los extensos experimentos prácticos con RAN 5G en el simulador NetSim, realizados como parte del Programa de Certificación Avanzada de Posgrado en Tecnologías 5G ofrecido por IISc Bangalore en asociación con Talent Sprint. Esta experiencia puso de manifiesto la clara necesidad de herramientas simplificadas y accesibles para manejar los cálculos frecuentes y complejos implicados en la tecnología 5G.

## Propósito

El repositorio de Utilidades 5G proporciona:

- **Herramientas prácticas**: Cálculos y modelos esenciales para el diseño y operación de redes 5G.
- **Recursos educativos**: Documentación detallada y ejemplos para facilitar el aprendizaje sobre la tecnología 5G.
- **Contribuciones comunitarias**: Un entorno colaborativo para compartir conocimientos y soluciones.

## Características

- **Calculadoras de Pérdida por Trayecto**: Para escenarios de vista libre (LOS) y sin vista libre (NLOS) utilizando modelos de propagación específicos de 5G.
- **Convertidores de Potencia**: Convierte entre dBm y vatios, esencial para el análisis a nivel de señal y sistema.
- **Estimadores de Eficiencia Espectral**: Basados en diversos esquemas de modulación y codificación.
- **Métricas de Utilización de PRB**: Evalúa la eficiencia bajo diferentes condiciones de red.
- **Calculadoras de Throughput (Rendimiento)**: Evalúa la capacidad de la red y el rendimiento.

## Público Objetivo

- **Ingenieros de Telecomunicaciones** y **Diseñadores de Redes**
- **Académicos** y **Estudiantes** en comunicación inalámbrica y tecnología 5G

## Estructura del Repositorio

El proyecto está organizado en los siguientes directorios:

- **/utilities/**: Contiene directorios individuales para cada utilidad.
- **/shared/**: Contiene código fuente y encabezados compartidos utilizados en múltiples utilidades.
- **/tests/**: Contiene casos de prueba para las utilidades, utilizando Google Test para pruebas automatizadas.

Cada utilidad dentro del directorio `/utilities/` está estructurada de la siguiente manera:

```
/utilities/DLThroughputCalculator/
    ├── src/
    │   └── main.cpp
    └── include/
        └── ... (any additional headers)
```

## Cómo Empezar

Para clonar y ejecutar las utilidades en este repositorio, sigue estos pasos:

### Requisitos Previos

- Un compilador moderno de C++ que soporte C++11
- CMake versión 3.14 o superior
- Google Test instalado en tu sistema

### Clonar el Repositorio

Clona este repositorio en tu máquina local:

```bash
git clone https://github.com/abhilashmuraleedharan/5G.git
cd 5G
```

### Configuración de Google Test

El marco de pruebas automatizadas utiliza Google Test, incluido como un submódulo. Para configurarlo, ejecuta:

```bash
git submodule update --init --recursive
```

### Configurar y Compilar

Desde el directorio raíz del proyecto:

```bash
mkdir build
cd build
cmake ..
make
```

Esto generará los archivos ejecutables para todas las utilidades y los colocará dentro del directorio `build`.

### Ejecutar las Utilidades

Después de compilar, puedes ejecutar las utilidades desde dentro del directorio `build`. Por ejemplo:

```bash
./DLThroughputCalculator
```

Reemplaza `DLThroughputCalculator` con el nombre de la utilidad que deseas ejecutar.

### Ejecutar Pruebas Automatizadas

Para ejecutar las pruebas automatizadas compiladas junto con las utilidades, utiliza el siguiente comando:

```bash
./utilities_test
```

Esto ejecutará todas las pruebas enlazadas con el marco de Google Test.

## Cómo Contribuir

Si estás interesado en contribuir a este proyecto, agradezco tus aportes y apoyo. Aquí hay algunas formas en las que puedes contribuir:

- **Reportar errores**: Si encuentras algún problema, házmelo saber presentando un informe de error.
- **Sugerir mejoras**: ¿Tienes ideas sobre cómo mejorar estas utilidades? ¡Compártelas!
- **Agregar nuevas utilidades**: Contribuye con tu propia utilidad siguiendo los pasos mencionados en la siguiente sección.
- **Escribir casos de prueba automatizados**: Mejora la confiabilidad de las utilidades escribiendo casos de prueba automatizados en el directorio `/tests/`.

Por favor, sigue el estilo de código existente y proporciona documentación clara para tus contribuciones. Para cambios significativos, abre un issue para discutir lo que te gustaría modificar.
Si has desarrollado una nueva utilidad que deseas compartir, por favor sigue estas directrices para garantizar que se integre adecuadamente con la estructura existente.

### Agregar Nuevas Utilidades

Al contribuir nuevas utilidades, asegúrate de agregar la configuración de compilación CMake correspondiente para tu utilidad y pruebas en el archivo `CMakeLists.txt`.

```
/utilities/
├── YourNewUtility/
│   ├── src/
│   │   └── main.cpp
│   └── include/
│       └── ... (any additional header files)
```

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - consulta el archivo [LICENSE.md](LICENSE.md) para más detalles.

## Contacto

Si tienes alguna pregunta o comentario, por favor abre un issue en este repositorio o contáctame directamente en `abhilashmuraleedharan@outlook.com`.

¡Disfruta de las utilidades y feliz cálculo!
