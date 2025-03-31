# Respuestas

## Ejercicio 1

#### Paralelizar la multiplicación de matrices cuadradas de NxN. Obtener el tiempo de ejecución para N=512, 1024 y 2048. Ejecutar con 2 y 4 threads.

| T   | N    | Secuencial | Paralelo  |
| --- | ---- | ---------- | --------- |
| 2   | 512  | 0.424661   | 0.222298  |
| 2   | 1024 | 3.393746   | 1.708461  |
| 2   | 2048 | 27.364525  | 14.012190 |
| 4   | 512  | 0.426431   | 0.116166  |
| 4   | 1024 | 3.401225   | 0.957521  |
| 4   | 2048 | 27.587718  | 7.384228  |

## Ejercicio 2

#### Paralelizar un algoritmo que cuente la cantidad de veces que un elemento X aparece dentro de un vector de N elementos enteros. Al finalizar, la cantidad de ocurrencias del elemento X debe quedar en una variable llamada ocurrencias. Ejecutar con 2 y 4 threads.

| T   | N         | Secuencial | Paralelo |
| --- | --------- | ---------- | -------- |
| 2   | 100000    | 0.000363   | 0.000533 |
| 2   | 1000000   | 0.003114   | 0.004090 |
| 2   | 10000000  | 0.030985   | 0.026994 |
| 2   | 100000000 | 0.311693   | 0.172299 |
| 4   | 100000    | 0.000306   | 0.000386 |
| 4   | 1000000   | 0.003141   | 0.002513 |
| 4   | 10000000  | 0.031346   | 0.018618 |
| 4   | 100000000 | 0.311657   | 0.092601 |

## Ejercicio 3

#### Paralelizar la búsqueda del mínimo y el máximo valor en un vector de N elementos. Ejecutar con 2 y 4 Threads.

| T   | N         | Secuencial | Paralelo |
| --- | --------- | ---------- | -------- |
| 2   | 1000000   | 0.002615   | 0.003596 |
| 2   | 10000000  | 0.025173   | 0.023982 |
| 2   | 100000000 | 0.254843   | 0.139453 |
| 4   | 1000000   | 0.002545   | 0.001828 |
| 4   | 10000000  | 0.025146   | 0.017170 |
| 4   | 100000000 | 0.254770   | 0.075081 |

## Ejercicio 5

#### Paralelizar la ordenación por mezcla de un vector de N elementos. Ejecutar con 2 y 4 Threads.

| T   | N        | Secuencial | Paralelo  |
| --- | -------- | ---------- | --------- |
| 2   | 100000   | 0.015232   | 0.018064  |
| 2   | 1000000  | 0.177593   | 0.102305  |
| 2   | 10000000 | #segfault  | #segfault |
| 4   | 100000   | 0.017315   | 0.011640  |
| 4   | 1000000  | 0.177789   | 0.064535  |
| 4   | 10000000 | #segfault  | #segfault |

## Ejercicio 6

#### si.
