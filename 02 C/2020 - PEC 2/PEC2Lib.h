//
// Created by Jorge Pulido on 09/05/2020.
//

#ifndef INC_2020___PEC_2_PEC2LIB_H
#define INC_2020___PEC_2_PEC2LIB_H

#endif

#include <stdio.h>

/**
 * Inicializa a cero todas las posiciones de un array del tipo ``int[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * array: int[]
 *      Array a inicializar
 * L_filas: int
 *      Longitud del array unidimensional.
 */
void inicializar_i_ceros_1d(int *array, int L_filas);

/**
 * Inicializa a cero todas las posiciones de un array del tipo ``float[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * array: float[]
 *      Array a inicializar
 * L_filas: int
 *      Longitud del array unidimensional.
 */
void inicializar_f_ceros_1d(float *array, int L_filas);

/**
 * Inicializa a uno todas las posiciones de un array del tipo ``int[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * array: float[]
 *      Array a inicializar
 * L_filas: int
 *      Longitud del array unidimensional.
 */
void inicializar_i_unos_1d(int *array, int L_filas);

/**
 * Inicializa a uno todas las posiciones de un array del tipo ``float[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * array: int[]
 *      Array a inicializar
 * L_filas: int
 *      Longitud del array unidimensional.
 */
void inicializar_f_unos_1d(float *array, int L_filas);

/**
 * Genera un número comprendido aleatorio comprendido entre 0 y 1
 * 
 * Return
 * ------
 * float
 *      Número aleatorio comprendido entre 0 y 1.
 */
float randomProbability();

/**
 * Imprime por consola un array del tipo ``float[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * *array: float[]
 *      Array a imprimir
 * columnas: int
 *      Longitud del array unidimensional.
 * espacio: bool
 *      Modifica el formato de salida de los datos.
 * 
 *      Examples
 *      --------
 *      >>> True: 0 | 2 | 7...
 *      >>> False: 027...
 * 
 * printfloat: bool
 *      Modifica el formato de salida de los datos.
 * 
 *      Examples
 *      --------
 *      >>> True: 0.00 | 2.00 | 7.00
 *      >>> False: 0 | 2 | 7
 */
void print_array_f_1d(float *array, int columnas, int espacio, int printfloat);

/**
 * Imprime por consola un array del tipo ``int[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * *array: int[]
 *      Array a imprimir
 * columnas: int
 *      Longitud del array unidimensional.
 * espacio: bool
 *      Modifica el formato de salida de los datos.
 * 
 *      Examples
 *      --------
 *      >>> True: 0 | 2 | 7...
 *      >>> False: 027...
 */
void print_array_i_1d(int *array, int columnas, int espacio);

/**
 * Imprime por consola un array del tipo ``int[]`` unidimensional.
 * 
 * Parameters
 * ----------
 * *array: int[]
 *      Array a imprimir.
 * columnas: int
 *      Número de campos por fila.
 * filas: int
 *      Número de filas.
 * espacio: bool
 *      Modifica el formato de salida de los datos.
 * 
 *      Examples
 *      --------
 *      >>> True: 0 | 2 | 7
 *      >>>       2 | 4 | 9
 *      >>>       2 | 2 | 4
 *      >>>       2 | 11 | 7
 *      >>>
 *      >>> False: 027
 *      >>>        249
 *      >>>        224
 *      >>>        2117
 */
void print_array_2d(int *array, int columnas, int filas, int espacio);

void crear_histograma(int *array, float *histograma, int filas, int columnas);

void dividir_array(float *array, int columnas, int dividendo);

void rangosArrayUnidimensional_float(float *array, int columnas, float *rangeX, float *rangeY, int accumulated, float step);

void rangosArrayUnidimensional_int(int *array, int columnas, float *rangeX, float *rangeY, int accumulated, float step);

int simularDesintegracion(int *arrayIn, int *arrayOut, int length, float p, float *t, float dt);

void simulateFirstStepDisintegrationsMTimes(int *arrayIn, int *arrayOut, int length, float p, int *histogram, int M);

void simulateFullDisintegration(int *arrayIn, int *arrayOut, int length, float p, int *disintegrations, float *t, float dt, int steps, float *disintegrationTime);

void arrayIterationalDivider(int *arrayIn, float *arrayOut, int divider, int length);

int checkAndCreateDirectory(const char *directory);

void print_array_2d_to_file_float_int(char *nombre, float *col1, int *col2, int columnas);

void print_array_1d_to_file_float(char *nombre, float *array, int columnas);

void print_array_1d_to_file_int(char *nombre, int *array, int columnas);

float inputParameter(char name[], int iterator, float defaultValue);