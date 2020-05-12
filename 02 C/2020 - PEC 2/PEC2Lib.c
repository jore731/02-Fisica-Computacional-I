//
// Created by Jorge Pulido on 09/05/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "PEC2Lib.h"

void inicializar_i_ceros_1d(int *array, int L_filas)
{
    int i = 0;
    while (i < L_filas)
    {
        array[i] = 0;
        i++;
    }
}

void inicializar_f_ceros_1d(float *array, int L_filas)
{
    int i = 0;
    while (i < L_filas)
    {
        array[i] = 0;
        i++;
    }
}

void inicializar_i_unos_1d(int *array, int L_filas)
{
    int i = 0;
    while (i < L_filas)
    {
        array[i] = 1;
        i++;
    }
}

void inicializar_f_unos_1d(float *array, int L_filas)
{
    int i = 0;
    while (i < L_filas)
    {
        array[i] = 1;
        i++;
    }
}

float randomProbability()
{
    return rand() / (double)RAND_MAX;
}

void print_array_f_1d(float *array, int columnas, int espacio, int printfloat)
{
    int i = 0;
    while (i < columnas)
    {
        if (espacio == 0)
        {
            if (printfloat == 0)
            {
                printf("%.0f", array[i]);
            }
            else
            {
                printf("%.4f", array[i]);
            }
        }
        else
        {
            if (printfloat == 0)
            {
                printf("%.0f |", array[i]);
            }
            else
            {
                printf("%.4f |", array[i]);
            }
        }
        i++;
    }
}

void print_array_i_1d(int *array, int columnas, int espacio)
{
    int i = 0;
    int * ptr = array;
    while (i < columnas)
    {
        if (espacio == 0)
        {
//            printf("%i", array[i]);
        printf("%i ", *ptr);
        ptr++;
        }
        else
        {
            printf("%i |", array[i]);
        }
        i++;
    }
}

void print_array_2d(int *array, int columnas, int filas, int espacio)
{
    int i = 0, j = 0;
    while (i < filas)
    {
        while (j < columnas)
        {
            if (espacio == 1)
            {
                printf("%i |", array[i * columnas + j]);
            }
            else
            {
                printf("%i", array[i * columnas + j]);
            }
            j++;
        }
        printf("\n");
        i++;
        j = 0;
    }
}

void calcular_huecos(int *array, int *huecos, int L_filas)
{
    int i = 0, h_act = 0;
    while (i < L_filas)
    {
        if (array[i] == 0)
        {
            h_act++;
        }
        else
        {
            if (h_act != 0)
            {
                huecos[h_act]++;
                // printf("%i, %i\n",i, &array[i] );
            }
            h_act = 0;
        }
        // printf("%i, %i, %i\n",i,h_act,array[i]);
        i++;
    }
    if (h_act != 0)
    {
        huecos[h_act]++;
    }
}

void crear_matriz_huecos(int *array, int *huecos, int filas, int columnas)
{
    int i = 0;
    while (i < filas)
    {
        inicializar_i_ceros_1d(&huecos[i * columnas / 2], columnas / 2);
        calcular_huecos(&array[i * columnas], &huecos[i * columnas / 2], columnas);
        i++;
    }
}

void crear_histograma(int *array, float *histograma, int filas, int columnas)
{
    int i = 0, j = 0;
    inicializar_f_ceros_1d(histograma, columnas);
    while (i < filas)
    {
        while (j < columnas)
        {
            histograma[j] = histograma[j] + array[i * columnas + j];
            j++;
        }
        j = 0;
        i++;
    }
}

void dividir_array(float *array, int columnas, int dividendo)
{
    int j = 0;
    while (j < columnas)
    {
        array[j] = array[j] / dividendo;
        j++;
    }
}

void escala_histograma(float *array, int columnas, float *max_x, float *max_y)
{
    int i = 0;
    *max_x = 0;
    *max_y = 0;
    while (i < columnas / 2)
    {
        if (array[i] > *max_y)
        {
            *max_y = array[i];
        }
        if (array[i] > 0)
        {
            *max_x = i;
        }
        i++;
    }
}

void print_array_f_1d_to_file(char *nombre, float *array, int columnas, FILE *output_txt)
{
    int i = 0;
    while (i < columnas)
    {
        if (i == 0)
        {
            fprintf(output_txt, "%f ", array[i]);
        }
        else
        {
            fprintf(output_txt, "| %f ", array[i]);
        }
        i++;
    }
}

void print_array_f_2d_to_file(char *nombre, float *array, int columnas, int filas)
{
    int j = 0;
    FILE *output_txt = fopen(nombre, "w");
    while (j < filas)
    {
        print_array_f_1d_to_file(nombre, &array[j * columnas], columnas, output_txt);
        if (j != filas - 1)
        {
            fprintf(output_txt, "\n");
        }
        j++;
    }
    fclose(output_txt);
}

void print_array_i_1d_to_file(char *nombre, int *array, int columnas, FILE *output_txt)
{
    int i = 0;
    while (i < columnas)
    {
        if (i == 0)
        {
            fprintf(output_txt, "%i ", array[i]);
        }
        else
        {
            fprintf(output_txt, "| %i ", array[i]);
        }
        i++;
    }
}

void print_array_i_2d_to_file(char *nombre, int *array, int columnas, int filas)
{
    int j = 0;
    FILE *output_txt = fopen(nombre, "w");
    while (j < filas)
    {
        print_array_i_1d_to_file(nombre, &array[j * columnas], columnas, output_txt);
        if (j != filas - 1)
        {
            fprintf(output_txt, "\n");
        }
        j++;
    }
    fclose(output_txt);
}

int simularDesintegracion(int arrayIn[], int arrayOut[], int length, float p, float *t, float dt)
{
    int desintegraciones = 0, i;
    for (i = 0; i < length; ++i)
    {
        arrayOut[i] = arrayIn[i];
        if (arrayIn[i] == 0)
        {
            if (randomProbability() < p)
            {
                arrayOut[i] = 1;
                desintegraciones++;
            }
        }
    }
    *t = *t + dt;
    return desintegraciones;
}

void initializeChunkedArray(int * mainArray, int * chunkPointersArray, int * sizesArray, int chunks) {
//    int position = 4;
    int *pttr, j;
    char *p;
    printf("Reading array");
    printf("%i", chunks);
    for (j = 0; j < chunks; ++j) {
        printf("reading chunk");
        pttr = mainArray;
//        p = (char *) pttr;
        printf("Moving pointer");
//        p += position;    //increments pointer by 8 bytes
//        pttr = (int *) p;
//        chunkPointersArray[j] = (int)pttr;
        printf("Initializing array");
        inicializar_i_unos_1d(&pttr, sizesArray[j]);
//        position += sizesArray[j];
        printf("chunk read");
    }
    return;
}
