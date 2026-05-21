# README: ASSIGNMENT III — Disk Scheduling

**Integrantes:** *[Nombres del equipo]*

---

# 1.1 Descripción General

La presente actividad tiene como propósito estudiar y comprender el funcionamiento de los algoritmos de planificación de disco en sistemas operativos, mediante su implementación en C++ y la visualización de su comportamiento a través de gráficas interactivas.

Se implementaron tres algoritmos clásicos de scheduling de disco: **FCFS**, **SCAN** y **C-SCAN**, cada uno encapsulado en su propia clase. El programa genera 1,000 solicitudes de cilindros de forma aleatoria, aplica cada algoritmo y exporta los resultados en un archivo `data.js` que es consumido por una interfaz web para graficar el recorrido del cabezal.

---

# 1.2 Descripción de la Actividad

La actividad fue desarrollada en C++ utilizando programación orientada a objetos, separando cada algoritmo en su propio par de archivos `.h` y `.cpp`.

La implementación incluye:

* Generación aleatoria de 1,000 solicitudes de cilindros entre 0 y 4,999
* Recepción de la posición inicial del cabezal por parámetro en línea de comandos
* Implementación de los algoritmos FCFS, SCAN y C-SCAN
* Cálculo del movimiento total del cabezal para cada algoritmo
* Exportación de los resultados en formato `data.js`
* Visualización interactiva mediante una página HTML con gráficas SVG

---

# 1.3 Estructura General de la Actividad

```
proyecto/
├── main.cpp          ← Programa principal
├── FCFS.h            ← Declaración de la clase FCFS
├── fcfs.cpp          ← Implementación de FCFS
├── SCAN.h            ← Declaración de la clase SCAN
├── scan.cpp          ← Implementación de SCAN
├── CSCAN.h           ← Declaración de la clase C-SCAN
├── cscan.cpp         ← Implementación de C-SCAN
├── index.html        ← Visualización web
├── script.js         ← Lógica de graficación
├── style.css         ← Estilos de la interfaz
├── Dockerfile        ← Configuración del contenedor Docker
└── data.js           ← Generado al ejecutar el programa (no incluido)
```

## Descripción de archivos

`main.cpp`
Archivo principal. Lee la posición inicial del cabezal desde la línea de comandos, genera 1,000 solicitudes aleatorias, instancia los tres algoritmos, calcula los recorridos y exporta el archivo `data.js`.

`FCFS.h / fcfs.cpp`
Implementación del algoritmo First-Come, First-Served. Atiende las solicitudes en el orden exacto en que llegaron, sin reordenamiento.

`SCAN.h / scan.cpp`
Implementación del algoritmo SCAN (elevador). El cabezal se mueve hacia arriba atendiendo solicitudes, llega hasta el cilindro 4,999 y luego regresa hacia abajo atendiendo las solicitudes restantes.

`CSCAN.h / cscan.cpp`
Implementación del algoritmo C-SCAN (SCAN circular). El cabezal se mueve hacia arriba atendiendo solicitudes, llega hasta el cilindro 4,999, salta directamente al cilindro 0 y continúa atendiendo hacia arriba.

`index.html / script.js / style.css`
Interfaz web que lee el archivo `data.js` generado y muestra cuatro gráficas: una combinada con los tres algoritmos, una individual por cada algoritmo y una gráfica de barras de comparación de rendimiento.

`data.js`
Archivo generado automáticamente al ejecutar el programa. Contiene los requests originales, los paths de cada algoritmo y los totales de movimiento. Este archivo es leído por la visualización web.

---

# 1.4 Algoritmos Implementados

## FCFS — First Come, First Served

Atiende las solicitudes en el orden en que llegaron, sin importar la posición del cabezal. Es el más simple pero también el menos eficiente, ya que el cabezal puede moverse de un extremo al otro repetidamente.

```
Ejemplo: cabezal en 2500, requests: [3000, 500, 4000]
Recorrido: 2500 → 3000 → 500 → 4000
```

## SCAN — Algoritmo del Elevador

El cabezal se mueve siempre hacia arriba primero, atendiendo todas las solicitudes en esa dirección. Cuando llega al extremo del disco (cilindro 4,999), invierte su dirección y atiende las solicitudes restantes de regreso.

```
Ejemplo: cabezal en 2500, requests: [3000, 500, 4000]
Recorrido: 2500 → 3000 → 4000 → 4999 → 500
```

## C-SCAN — Circular SCAN

Similar a SCAN, pero al llegar al extremo superior (cilindro 4,999) el cabezal salta directamente al cilindro 0 sin atender solicitudes durante ese trayecto, y continúa moviéndose hacia arriba. Esto garantiza tiempos de espera más uniformes.

```
Ejemplo: cabezal en 2500, requests: [3000, 500, 4000]
Recorrido: 2500 → 3000 → 4000 → 4999 → 0 → 500
```

---

# 1.5 Formato del archivo data.js generado

Al ejecutar el programa se crea un archivo `data.js` con el siguiente formato:

```js
const MAX_CYLINDER = 4999;
const INITIAL_HEAD = 2500;
const NUM_REQUESTS = 1000;

const MOVEMENT_FCFS  = 1654651;
const MOVEMENT_SCAN  = 7491;
const MOVEMENT_CSCAN = 9990;

const REQUESTS   = [433, 2107, 1807, ...];  // 1000 elementos
const PATH_FCFS  = [2500, 433, 2107, ...];  // 1001 elementos
const PATH_SCAN  = [2500, 512, 890, ..., 4999, 201, ...];
const PATH_CSCAN = [2500, 512, 890, ..., 4999, 0, 201, ...];
```

---

## 1.6 Desarrollo Teórico Complementario

Además de la implementación práctica y la visualización de los algoritmos de scheduling, el proyecto incluye un documento adicional llamado `Assignment_III_Parte2.pdf`.

En este archivo se desarrolla la parte teórica de la actividad propuesta en el enunciado del Assignment III, incluyendo el análisis conceptual de la gestión de entrada/salida (I/O), el estudio de los algoritmos de planificación de disco y la resolución de los ejercicios planteados sobre cálculo de movimientos del cabezal y comparación de estrategias de scheduling.

El documento complementa la implementación realizada en C++ y sirve como soporte teórico para comprender el comportamiento y rendimiento de los algoritmos FCFS, SCAN y C-SCAN.

---

## Contenido del documento `Assignment_III_Parte2.pdf`

El archivo incluye:

* Resolución de ejercicios teóricos sobre scheduling de disco
* Análisis paso a paso de recorridos del cabezal
* Comparación entre algoritmos FCFS, SCAN y C-SCAN
* Explicaciones conceptuales sobre eficiencia y latencia
* Discusión sobre variantes del algoritmo Elevator/SCAN
* Interpretación de resultados y comportamiento de los algoritmos


---

# 2. Visualización Gráfica

La visualización se realiza abriendo el archivo `index.html` directamente en el navegador **después de haber ejecutado el programa** y generado el `data.js`.

## Demo Online

La visualización también puede verse directamente desde GitHub Pages:

https://anadan10102006.github.io/Assignment-III-Parte-2/

## Gráficas disponibles

## Gráficas disponibles

**Combined Graph** — Muestra el recorrido de los tres algoritmos superpuestos en una misma gráfica para facilitar la comparación visual. Cada algoritmo tiene su propio color:
* Azul → FCFS
* Naranja → SCAN
* Verde → C-SCAN

**FCFS / SCAN / C-SCAN (individuales)** — Una gráfica por cada algoritmo mostrando el recorrido del cabezal paso a paso. El eje X representa cada solicitud atendida y el eje Y el número de cilindro visitado.

**Performance Comparison** — Gráfica de barras que compara el movimiento total del cabezal entre los tres algoritmos, permitiendo ver de forma inmediata cuál fue más eficiente.

## Cómo ver la visualización

1. Ejecutar el programa (ver sección 3) para generar el `data.js`
2. Asegurarse de que `data.js`, `index.html`, `script.js` y `style.css` estén en la misma carpeta
3. Abrir `index.html` directamente en el navegador (doble clic o arrastrar al navegador)

> **Importante:** el `data.js` debe estar en la misma carpeta que el `index.html`. Si no existe, la página no mostrará ninguna gráfica.

---

# 3. Compilación y Ejecución fuera de Docker

Si se desea compilar directamente con `g++`:

## Compilación

```bash
g++ main.cpp fcfs.cpp scan.cpp cscan.cpp -o diskScheduler
```

## Ejecución

```bash
# Linux / macOS
./diskScheduler 2500

# Windows
diskScheduler.exe 2500
```

El número `2500` es la posición inicial del cabezal. Puede ser cualquier valor entre `0` y `4999`.

Al ejecutar, el programa:
1. Genera 1,000 solicitudes aleatorias
2. Aplica FCFS, SCAN y C-SCAN
3. Imprime en consola el movimiento total de cada algoritmo
4. Crea el archivo `data.js` en la misma carpeta

---

# 4. Compilación y Ejecución con Docker

La actividad está preparada para compilarse y ejecutarse dentro de un contenedor Docker. Al correrlo, el programa genera el `data.js` y levanta automáticamente un servidor web en el puerto 8080 para visualizar las gráficas desde el navegador.

## Paso 1 — Clonar el repositorio

```bash
git clone <URL del repositorio>
cd <nombre-de-la-carpeta>
```

## Paso 2 — Construir la imagen Docker

```bash
docker build -t disk-scheduler .
```

Este comando lee el `Dockerfile`, compila todos los archivos fuente y genera una imagen lista para ejecutar.

## Paso 3 — Ejecutar el contenedor

```bash
docker run --rm -p 8080:8080 disk-scheduler 2500
```

| Parte del comando | Qué hace |
|---|---|
| `--rm` | Elimina el contenedor al terminar |
| `-p 8080:8080` | Expone el puerto 8080 del contenedor en tu máquina |
| `disk-scheduler` | Nombre de la imagen |
| `2500` | Posición inicial del cabezal (puede cambiarse por cualquier valor entre 0 y 4,999) |

## Paso 4 — Ver la visualización

Con el contenedor corriendo, abrir el navegador y entrar a:

```
http://localhost:8080
```

Ahí se verán todas las gráficas generadas automáticamente con los resultados del scheduling.

> **Importante:** no cerrar la terminal mientras se quiera ver la visualización, ya que el servidor web corre dentro del contenedor. Para detenerlo usar `Ctrl + C`.

---

# 4.1 Archivos de configuración Docker

`Dockerfile`
```dockerfile
FROM japeto/so-tools:v64

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -o diskScheduler \
    main.cpp fcfs.cpp scan.cpp cscan.cpp

EXPOSE 8080

ENTRYPOINT ["sh", "entrypoint.sh"]
```

`entrypoint.sh`
```bash
#!/bin/sh
./diskScheduler $1
python3 -m http.server 8080
```

El `entrypoint.sh` primero corre el scheduler para generar el `data.js`, y luego levanta un servidor web simple con Python para servir el `index.html` junto con ese archivo.

---

# 5. Cumplimiento de Requerimientos

## Implementación de algoritmos de scheduling
* FCFS
* SCAN (con llegada al extremo del disco)
* C-SCAN (con salto circular al cilindro 0)

## Generación aleatoria de solicitudes
* 1,000 cilindros aleatorios entre 0 y 4,999
* Semilla basada en el tiempo del sistema (resultados distintos en cada ejecución)

## Parámetro por línea de comandos
* Posición inicial del cabezal recibida como `argv[1]`
* Validación de rango (0 a 4,999)

## Uso de programación orientada a objetos
* Clases separadas por algoritmo
* Archivos `.h` y `.cpp` por clase

## Visualización de datos
* Gráficas de recorrido individuales por algoritmo
* Gráfica combinada
* Comparación de rendimiento mediante gráfica de barras
* Implementada en HTML/CSS/JavaScript puro, sin dependencias externas
