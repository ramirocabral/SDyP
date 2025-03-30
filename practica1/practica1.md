# Respuestas

## Ejercicio 1

### Inciso A

#### Analizar el algoritmo matrices.c que resuelve la multiplicación de matrices C=AB donde A, B y C son matrices cuadradas de N\*N.

#### i. Comparar el tiempo de ejecución original con el tiempo de eliminar las funciones getValor y setValor. ¿Son necesarias estas funciones?¿Qué puede decirse del overhead introducido por los llamados a estas funciones?

| N    | Tiempo Original | Tiempo Sin Funciones |
| ---- | --------------- | -------------------- |
| 32   | 0.001098        | 0.000308             |
| 64   | 0.007711        | 0.001546             |
| 128  | 0.035615        | 0.018147             |
| 256  | 0.273985        | 0.077327             |
| 512  | 2.277871        | 0.650832             |
| 1024 | 20.927238       | 6.592458             |
| 2048 | 481.8086285     | 192.774337           |

Estas funciones son al recontra pedo.

#### ii. Partiendo del código sin las funciones getValor y setValor, comparar la solución que almacena A, B y C por filas con las solución que almacena B por columnas. ¿Qué conclusión puede obtenerse de la diferencia en los tiempos de ejecución? ¿Cómo se relaciona con el principio de localidad?

| N    | Tiempo por Filas | Tiempo por Columnas |
| ---- | ---------------- | ------------------- |
| 32   | 0.000308         | 0.000308            |
| 64   | 0.001546         | 0.003078            |
| 128  | 0.018147         | 0.009498            |
| 256  | 0.077327         | 0.087142            |
| 512  | 0.650832         | 0.629017            |
| 1024 | 6.592458         | 5.219488            |
| 2048 | 192.774337       | 42.868388           |

Por columnas es más rápido porque se aprovecha mejor el principio de localidad.

### Inciso B

#### Analizar los algoritmos que resuelven distintas operaciones sobre matrices de N\*N:

#### Ejecutar con distintos valores de N. Comparar los tiempos de ejecución de las dos versiones en cada caso. ¿Qué versión es más rápida? ¿Por qué?

#### expMatrices1.c: dos versiones que resuelven la operación AB + AC + AD

| N    | Tiempo 1 Loop | Tiempo 4 Loops |
| ---- | ------------- | -------------- |
| 32   | 0.000891      | 0.000938       |
| 64   | 0.007405      | 0.007584       |
| 128  | 0.032876      | 0.025604       |
| 256  | 0.198224      | 0.209902       |
| 512  | 1.567249      | 1.740132       |
| 1024 | 12.475206     | 14.281776      |

Esto sucede porque en la versión con 4 loops se aprovecha mejor el principio de localidad.

#### expMatrices2.c: dos versiones que resuelven la operación AB + CD

| N    | Tiempo 1 Loop | Tiempo 3 Loops |
| ---- | ------------- | -------------- |
| 32   | 0.000614      | 0.000665       |
| 64   | 0.005505      | 0.002540       |
| 128  | 0.026141      | 0.019169       |
| 256  | 0.150362      | 0.164662       |
| 512  | 1.184163      | 1.221098       |
| 1024 | 9.173862      | 10.043702      |
| 2048 | 74.649652     | 42.868388      |

#### expMatrices3.c: dos versiones que resuelven la operación BA + CAD

| N    | Tiempo 1 Loop | Tiempo 3 Loops |
| ---- | ------------- | -------------- |
| 32   | 0.000614      | 0.000665       |
| 64   | 0.005505      | 0.002540       |
| 128  | 0.026141      | 0.019169       |
| 256  | 0.150362      | 0.164662       |
| 512  | 1.184163      | 1.221098       |
| 1024 | 9.173862      | 10.043702      |
| 2048 | 74.649652     | 79.509380      |

Sin lugar a dudas esto esta relacionado al susodicho principio de localidad...

### Inciso C

#### Implementar una solución a la multiplicación de matrices AA donde la matriz A es de N\*N. Plantear dos estrategias

Planteamos primero ambas ordenadas por filas, y luego A por filas y B por columnas.

| N    | Matrices por fila | Matrices por Columnas |
| ---- | ----------------- | --------------------- |
| 32   | 0.000173          | 0.000180              |
| 64   | 0.002721          | 0.002925              |
| 128  | 0.018309          | 0.008622              |
| 256  | 0.080996          | 0.067294              |
| 512  | 0.680934          | 0.554413              |
| 1024 | 6.195168          | 4.736084              |
| 2048 | 200.088278        | 38.761456             |

La segunda alcanza mejor rendimiento. Uno podria discernir que es por el principio de localidad.

### Inciso D

| N    | BS  | Multiplicacion |
| ---- | --- | -------------- |
| 64   | 16  | 0.003059       |
| 64   | 32  | 0.002585       |
| 128  | 32  | 0.017520       |
| 128  | 64  | 0.012353       |
| 256  | 32  | 0.074063       |
| 256  | 64  | 0.084029       |
| 512  | 32  | 0.554413       |
| 512  | 64  | 0.670766       |
| 1024 | 32  | 5.161499       |
| 1024 | 64  | 4.736084       |
| 2048 | 64  | 38.761456      |
| 2048 | 128 | 40.385857      |

Se toman mini-matrices de menor tamaño que la original, optimizando el uso de la cache.

### Inciso E

| N    | Almacenando ceros | Sin almacenar ceros |
| ---- | ----------------- | ------------------- |
| 32   | 0.000783          | 0.000729            |
| 64   | 0.006311          | 0.006484            |
| 128  | 0.032647          | 0.020023            |
| 256  | 0.176397          | 0.191416            |
| 512  | 0.390198          | 0.493101            |
| 1024 | 17.536228         | 14.566245           |
| 2048 | 384.922440        | 272.829422          |

### Ejercicio 2

| N   | Fibonacci Iterativo | Fibonacci Recursivo |
| --- | ------------------- | ------------------- |
| 5   | 0.00000000000       | 0.00000001192       |
| 8   | 0.00000000954       | 0.00000003099       |
| 13  | 0.00000001907       | 0.00000029087       |
| 21  | 0.00000000954       | 0.0001267910        |
| 34  | 0.00000003099       | 0.0287601948        |
| 55  | 0.00000005007       | infinite lol        |

### Ejercicio 3

| N        | Sin Registro | Con Registro |
| -------- | ------------ | ------------ |
| 10000    | 0.0004460812 | 0.0005650520 |
| 100000   | 0.0054278374 | 0.0046420097 |
| 1000000  | 0.0168690681 | 0.0115449429 |
| 10000000 | 0.1493060589 | 0.1042599678 |

Tarda menos con registro ya que se aprovecha mejor el principio de localidad al tener las variables en un struct.

### Ejercicio 5

#### Inciso A

Es claramente mas rapido usando el puntero. Sin embargo, esto puede variar dependiendo de la arquitectura y de la implementacion del compilador.

#### Inciso B

Es por que la variable i es un int, y debe ser unsigned long.

### Ejercicio 6

IF MALARDO

### Ejercicio 7

Para la misma cantidad de elementos, el programa con doble precision tarda mucho mas tiempo, aunque no tiene ningun tipo de error comparado al de simple precision.
