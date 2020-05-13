//
// Created by Jorge Pulido on 09/05/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

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
    int *ptr = array;
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

void rangosArrayUnidimensional(float *array, int columnas, float *rangeX, float *rangeY, int accumulated)
{
    int i = 0;
    if (accumulated == 0)
    {
        rangeX[0] = 0;
        rangeX[1] = 0;
        rangeY[0] = 0;
        rangeY[1] = 0;
    }
    while (i < columnas)
    {
        if (array[i] > rangeY[1])
        {
            rangeY[1] = array[i];
        }
        if (array[i] < rangeY[0])
        {
            rangeY[0] = array[i];
        }
        if (array[i] > 0)
        {
            rangeX[1] = i;
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

void simulateFirstStepDisintegrationsMTimes(int *arrayIn, int *arrayOut, int length, float p, float *t, float dt, int *histogram, int M)
{
    int j;
    for (j = 0; j < M; j++)
    {
        //Actuación por cada muestra
        int disintegrations = simularDesintegracion(arrayIn, arrayOut, length, p, t, dt);
        histogram[disintegrations]++;
    }
}

void arrayIterationalDivider(int *arrayIn, float *arrayOut, int divider, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        arrayOut[i] = (float)arrayIn[i] / divider;
    }
}

int checkAndCreateDirectory(const char *directory)
{
    int mkDirDone = 0;
    while (1)
    {
        DIR *dir = opendir(directory);
        if (dir)
        {
            return 0;
        }
        else if ((ENOENT == errno) && (mkDirDone == 0))
        {
            mkdir(directory);
            mkDirDone = 1;
        }
        else
        {
            printf("\nERROR: COULD NOT CREATE OUTPUT DIRECTORY.\nPlease create %s directory manually\n");
            char answer = ' ';
            while (1)
            {
                answer = ' ';
                printf("Done/cancel (d/c): ");
                scanf(" %c", &answer);
                if (answer == 'd')
                {
                    mkDirDone = 0;
                    break;
                }
                else if (answer == 'c')
                {
                    return -1;
                }
            }
        }
    }
}

void print_array_1d_to_file(char *nombre, float *array, int columnas)
{
    int i = 0;
    FILE *output_txt = fopen(nombre, "w");
    while (i < columnas)
    {
        fprintf(output_txt, "%f\n", array[i]);
        i++;
    }
    fclose(output_txt);
}