# Respuestas

## Ejercicio 1

#### El programa ejercicio1.c inicializa una matriz de NxN de la siguiente manera: A[i,j]=i\*j, para todo i,j=0..N-1. Compilar y ejecutar. ¿Qué problemas tiene el programa? Corregirlo.

la variable i era private, y al entrar al bloque su valor era basura.

## Ejercicio 2

#### Analizar y compilar el programa ejercicio2.c. Ejecutar varias veces y comparar los resultados de salida para diferente número de threads ¿Cuál es el problema? ¿Es posible corregirlo?.

Necesitamos usar reduction!!! Al hacer esto, se crea una variable privada a cada thread y al finalizar la ejecucion del codigo, se aplica reduce a los resultados en la variable compartida.

## Ejercicio 3

#### El programa matrices.c realiza la multiplicación de 2 matrices cuadradas de N\*N (C=AxB). Utilizando pragma parallel omp for Paralelizarlo de dos formas:

#### 1. Repartiendo entre los threads el cálculo de las filas de C. Es decir, repartiendo el trabajo del primer for.

#### 2. Repartiendo el cálculo de las columnas de cada fila de C. Es decir, repartiendo el trabajo del segundo for.

#### Comparar los tiempos de ambas soluciones variando el número de threads.

Es un poco mas rapido por filas jijo.

## Ejercicio 4

#### El programa traspuesta.c calcula la transpuesta de una matriz triangular de NxN. Compilar y ejecutar para 4 threads comparándolo con el algoritmo secuencial.

#### El programa tiene un problema, describir de que problema se trata. ¿Qué cláusula usaría para corregir el problema? Describir brevemente la cláusula OpenMP que resuelve el problema y las opciones que tiene. Corregir y ejecutar de nuevo comparando con los resultados anteriores.

El tiempo de procesamiento de cada thread es muy distinto.
Le ponemos shedule(dynamic, n) y anda perfecto.

## Ejercicio 5

#### El programa mxm.c realiza 2 multiplicaciones de matrices de NxN (D=AB y E=CB). Paralelizar utilizando secciones de forma que cada una de las multiplicaciones se realice en una sección y almacenar el código paralelo como mxmSections.c.

#### Compilar y ejecutar sobre diferente número de threads. Probar con 2 threads. Luego con 4 threads ¿Se Consigue mayor speedup al incrementar la cantidad de threads? ¿Por qué?

Tarda lo casi lo mismo con T=2 y T=4, ya que solo hay 2 secciones.
