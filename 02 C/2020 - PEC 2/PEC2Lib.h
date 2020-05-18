//
// Created by Jorge Pulido on 09/05/2020.
//

#ifndef INC_2020___PEC_2_PEC2LIB_H
#define INC_2020___PEC_2_PEC2LIB_H

#endif

#include <stdio.h>


/**
 * Genera un número comprendido aleatorio comprendido entre 0 y 1
 * 
 * En este caso debería ser suficiente con utilizar la función propia de C `rand()` con un seed generado cada vez que se ejecuta cada uno de los ejercicios para evitar que los resultados sean iguales en varias ejecuciones, pero podría ser interesante utilizar algún algorimo como el método de Montecarlo para cumplir esta función.
 * 
 * Return
 * ------
 * float
 *      Número aleatorio comprendido entre 0 y 1.*/
float randomProbability();

/**
 * Calcula los límites de una lista de datos (float) para x max, Y min e Y max. X min se considerará 0 dado que los procesos de desintegración siempre empezarán en `t = 0`.
 * 
 * Parameters
 * -----------
 * 
 * array: (float \*)
 *      Puntero del tipo float que indica la memoria inicial del array a evaluar.
 * 
 * columnas: int
 *      Longitud del array a evaluar.
 * 
 * rangeX: (float \*)
 *      Puntero del tipo float que indica la memoria inicial del array que alberga los datos del rango del eje X. Permite utilizar los datos resultantes de esta función fuera de la misma.
 * 
 * rangeY: (float \*)
 *      Puntero del tipo float que indica la memoria inicial del array que alberga los datos del rango del eje Y. Permite utilizar los datos resultantes de esta función fuera de la misma.
 * 
 * accumulated: int
 *      Define el modo de calcular los resultados a la hora de considerar los rangos X e Y, de forma que, en caso de tener varias gráficas conjuntas, nos permitirá calcular los máximos absolutos de todas las funciones:
 * 
 *      >>> accumulated = 0 -> Xmin_0 = 0, Ymin_0 = 0, Xmax_0 = 0, Ymax_0 = 0
 *      >>> accumulated = 1 -> Xmin_0 = rangeXmin, Ymin_0 = rangeYmin, Xmax_0 = rangeXmax, Ymax_0 = rangeYmax
 * 
 * step: float
 *      Duración de cada etapa de la desintegración (en años) que permite obtener el valor máximo de `t` aun trabajando con datos de etapa. */
void rangosArrayUnidimensional_float(float *array, int columnas, float *rangeX, float *rangeY, int accumulated, float step);

/**
 * Calcula los límites de una lista de datos (int) para x max, Y min e Y max. X min se considerará 0 dado que los procesos de desintegración siempre empezarán en `t = 0`.
 * 
 * Parameters
 * -----------
 * 
 * array: (int \*)
 *      Puntero del tipo int que indica la memoria inicial del array a evaluar.
 * 
 * columnas: int
 *      Longitud del array a evaluar.
 * 
 * rangeX: (float \*)
 *      Puntero del tipo float que indica la memoria inicial del array que alberga los datos del rango del eje X. Permite utilizar los datos resultantes de esta función fuera de la misma.
 * 
 * rangeY: (float \*)
 *      Puntero del tipo float que indica la memoria inicial del array que alberga los datos del rango del eje Y. Permite utilizar los datos resultantes de esta función fuera de la misma.
 * 
 * accumulated: int
 *      Define el modo de calcular los resultados a la hora de considerar los rangos X e Y, de forma que, en caso de tener varias gráficas conjuntas, nos permitirá calcular los máximos absolutos de todas las funciones:
 * 
 *      >>> accumulated = 0 -> Xmin_0 = 0, Ymin_0 = 0, Xmax_0 = 0, Ymax_0 = 0
 *      >>> accumulated = 1 -> Xmin_0 = rangeXmin, Ymin_0 = rangeYmin, Xmax_0 = rangeXmax, Ymax_0 = rangeYmax
 * 
 * step: float
 *      Duración de cada etapa de la desintegración (en años) que permite obtener el valor máximo de `t` aun trabajando con datos de etapa. */
void rangosArrayUnidimensional_int(int *array, int columnas, float *rangeX, float *rangeY, int accumulated, float step);

/** 
 * Toma un array de entrada de longitud `length` y evalúa cada una de sus posiciones, de forma que, si es cero, genera un número aleatorio y lo compara con la probabilidad umbral `p`, si el valor generado es menor que el umbral, se producirá una desintegración, es decir la posición analizada pasará de estado 0 a estado 1.
 * Evalua de esta forma todas las posiciones del array y actualiza el estado de cada una de las posiciones del array de salida `arrayOut`, de forma que para todo `arrayIn[i]`, genera un estado de salida y lo guarda en `arrayOut[i]`.
 * 
 * Parameters
 * ----------
 * 
 * ArrayIn: (int \*)
 *      Puntero a la dirección de memoria inicial del array a evaluar.
 * 
 * ArrayOut: (int \*)
 *      Puntero a la dirección de memoria inicial del array de salida.
 * 
 * length: int
 *      Número de posiciones a evaluar del array de entrada y, por lo tanto, número de posiciones a actualizar del array de salida.
 * 
 * p: float
 *      Valor umbral de desintegración. Si el valor aleatorio está por debajo de dicho umbral, el núcleo evaluado se desintegra.
 * 
 * t: (float \*)
 *      Puntero a la dirección de memoria que contiene el valor de tiempo al inicio de la simulación. Su valor se actualiza al final de la misma en función de `step`.
 * 
 * step: float
 *      Tiempo (en años) que dura la etapa de simulación. Se utiliza para actualizar el valor de `t` cuando esta concluya.*/
int simularDesintegracion(int *arrayIn, int *arrayOut, int length, float p, float *t, float dt);

/** 
 * Ejecuta `simularDesintegracion()` `M` veces y devuelve el histograma de desintegraciones.
 * 
 * Parameters
 * ----------
 * 
 * ArrayIn: (int \*)
 *      Puntero a la dirección de memoria inicial del array a evaluar.
 * 
 * ArrayOut: (int \*)
 *      Puntero a la dirección de memoria inicial del array de salida.
 * 
 * length: int
 *      Número de posiciones a evaluar del array de entrada y, por lo tanto, número de posiciones a actualizar del array de salida.
 * 
 * p: float
 *      Valor umbral de desintegración. Si el valor aleatorio está por debajo de dicho umbral, el núcleo evaluado se desintegra.
 * 
 * histogram: (int \*)
 *      Puntero a la dirección de memoria inicial del array de salida del histograma, que contendrá el número de veces que el resultado de la simulación ha coincidido con la posición del array en la que se encuentre dicho valor. Es decir, el valor de `histograma[0]` recogerá el número de veces que e resultado de la simulación ha sido de cero desintegraciones.
 * 
 * M: int
 *      Número de ciclos de simulación a ejecutar. Deberá coincidir con el resultado de la suma de todos los valores contenidos en el array `histogram`. */
void simulateFirstStepDisintegrationsMTimes(int *arrayIn, int *arrayOut, int length, float p, int *histogram, int M);

/**
 * Simula el proceso de desintegración completo de un conjunto de núcleos hasta que todos ellos figuran como desintegrados, almacenando los datos para generar un array de núcleos activos `disintegrations[]` que contendrá el número de nucleos activos al comienzo de cada etapa, así como los datos de tiempo de cada una de ellas en el array `t[]`.
 * 
 * Parameters
 * ----------
 * 
 * ArrayIn: (int \*)
 *      Puntero a la dirección de memoria inicial del array a evaluar.
 * 
 * ArrayOut: (int \*)
 *      Puntero a la dirección de memoria inicial del array de salida.
 * 
 * length: int
 *      Número de posiciones a evaluar del array de entrada y, por lo tanto, número de posiciones a actualizar del array de salida.
 * 
 * p: float
 *      Valor umbral de desintegración. Si el valor aleatorio está por debajo de dicho umbral, el núcleo evaluado se desintegra.
 * 
 * disintegrations: (int \*)
 *      Puntero a la dirección inicial del array que se irá recorriendo y actualizando con los datos de los núcleos activos al comienzo de cada etapa de la desintegración.
 * 
 * 
 * t: (float \*)
 *      Puntero a la dirección de memoria que contiene el valor de tiempo al inicio de la simulación. Su valor se actualiza al final de la misma en función de `step`.
 * 
 * dt: float
 *      Tiempo (en años) que dura la etapa de simulación. Se utiliza para actualizar el valor de `t` cuando esta concluya.
 * 
 * steps: int
 *      Número máximo de estados que se almacenarán para su posterior exportación o manipulación (Dimensión de los arrays `disintegrations` y `t`).
 * 
 * disintegrationTime: (float \*)
 *      Puntero a la dirección de memoria inicial del array de dos posiciones en el que se actualizarán los datos de tiempo de semidesintegración y tiempo de desintegración del conjunto (respectivamente).
 * 
 * accumulated: (float \*)
 *      Puntero a la dirección de memoria inicial del array que contendrá los datos acumulados de los valores del array disintegrations en caso de que `accumulate` lo indicara. Permite así calcular ponderaciones sin necesidad de aumentar en gran medida el número de ciclos de procesamiento.
 * 
 * accumulate: int
 *      Indica si los valores deseados son instanciales(0) o acumulativos(1).*/
void simulateFullDisintegration(int *arrayIn, int *arrayOut, int length, float p, int *disintegrations, float *t, float dt, int steps, float *disintegrationTime, float *accumulated, int accumulate);

/**
 * Mediante un proceso iterativo, divide todas las posiciones de un array de entrada entre una constante, para generar un array de salida. Se utilizará para la ponderación de resultados.
 * 
 * Parameters
 * ----------
 * 
 * ArrayIn: (int \*)
 *      Puntero a la dirección de memoria inicial del array a evaluar.
 * 
 * ArrayOut: (float \*)
 *      Puntero a la dirección de memoria inicial del array de salida.
 * 
 * divider: int
 *      Divisor de la operación.
 * 
 * length: int
 *      Número de posiciones a evaluar del array de entrada y, por lo tanto, número de posiciones a actualizar del array de salida.*/
void arrayIterationalDivider(int *arrayIn, float *arrayOut, int divider, int length);

/** 
 * Verifica la existencia de un directorio y, en caso de no existir, trata de crearlo (hasta un máximo de 1 nivel).
 * En caso de no poder crearlo, entra en un bucle de comprobaciones de la existencia de este (para su creación manual), evitando así continuar la ejecución del programa y posibilitar la pérdida de datos.
 * 
 * Parameters
 * ----------
 * 
 * directory (char \*)
 *      Puntero a la dirección de memoria inicial de la cadena de caracteres que contiene la ruta a analizar*/
int checkAndCreateDirectory(const char *directory);

/** 
 * Exporta los datos de dos arrays unidimensionales de tipos `float` y `int` a un archivo.
 * 
 * Parameters
 * ----------
 * 
 * nombre: (char \*)
 *      Puntero a la dirección de memoria inicial de la cadena de caracteres que contiene la ruta completa al archivo de salida de datos.
 * 
 * col1: (float \*)
 *      Puntero a la dirección de memoria inicial del array de datos que formará la columna 1 del array bidimensional de salida.
 * 
 * col1: (int \*)
 *      Puntero a la dirección de memoria inicial del array de datos que formará la columna 2 del array bidimensional de salida.
 * 
 * columnas: int
 *      Número de posiciones a exportar de cada uno de los arrays.*/
void print_array_2d_to_file_float_int(char *nombre, float *col1, int *col2, int columnas);

/** 
 * Exporta los datos de dos arrays unidimensionales de tipos `float` a un archivo.
 * 
 * Parameters
 * ----------
 * 
 * nombre: (char \*)
 *      Puntero a la dirección de memoria inicial de la cadena de caracteres que contiene la ruta completa al archivo de salida de datos.
 * 
 * col1: (float \*)
 *      Puntero a la dirección de memoria inicial del array de datos que formará la columna 1 del array bidimensional de salida.
 * 
 * col1: (float \*)
 *      Puntero a la dirección de memoria inicial del array de datos que formará la columna 2 del array bidimensional de salida.
 * 
 * columnas: int
 *      Número de posiciones a exportar de cada uno de los arrays.
 * 
 * skippingStep: int
 *      Paso de exportado. Solo se exportarán aquellos datos cuya posición en el array sea múltiplo de skippingStep. Por defecto un skippingStep de 1 exportará todos los datos del array*/
void print_array_2d_to_file_float_float(char *nombre, float *col1, float *col2, int columnas, int skippingStep);

/** 
 * Exporta los datos de un array unidimensional de tipo `float` a un archivo.
 * 
 * Parameters
 * ----------
 * 
 * nombre: (char \*)
 *      Puntero a la dirección de memoria inicial de la cadena de caracteres que contiene la ruta completa al archivo de salida de datos.
 * 
 * col1: (float \*)
 *      Puntero a la dirección de memoria inicial del array de datos a exportar.
 * 
 * columnas: int
 *      Número de posiciones a exportar de cada uno de los arrays.*/
void print_array_1d_to_file_float(char *nombre, float *array, int columnas);

/** 
 * Solicita un parámetro configurable por consola y, le asigna el valor proporcionado por el usuario o, en caso de no proporcionarse nignuno, el valor establecido por defecto.
 * 
 * Parameters
 * ----------
 * 
 * name: char[]
 *      Nombre del parámetro solicitado para ser mostrado por pantalla.
 * 
 * iterator: int
 *      Si el valor será asignado mediante un bucle, utiliza el valor del iterador introducido para especificar a que campo del array se introducirá dicho valor.
 * 
 * defaultValue: float
 *      Valor por defecto que se asignará si el usuario no introduce ningún valor y pulsa `enter`.*/
float inputParameter(char name[], int iterator, float defaultValue);

/**
 * Ejecuta el bucle de simulación y calcula los valores que serán asignados a F_t:
 * 
 * .. literalinclude:: ../../../PEC2Lib.c
 *      :language: C
 *      :caption: F(t) calculation loop
 *      :linenos:
 *      :lines: 326-332
 *      :emphasize-lines: 6
 * 
 * Así como la ponderación de los valores obtenidos de los tiempos de desintegración y semidesintegración.*/
void simulateF_t(float *F_t, float *t, int length, float p, float dt, int steps, int M, float *disintegrationTimes);

/**
 * Ejecuta el bucle de simulación y calcula las probabilidades de desintegración que serán asignadas al array unidimensional `markov`:
 * 
 * .. literalinclude:: ../../../PEC2Lib.c
 *      :language: C
 *      :caption: F(t) calculation loop
 *      :linenos:
 *      :lines: 382-385
 *      :emphasize-lines: 3
 * 
 * Así como la ponderación de los valores obtenidos de los tiempos de desintegración y semidesintegración.*/
void checkMarkov(float *markov, float *t, int length, float p, float dt, int steps, int M, int l, float *disintegrationTimes);