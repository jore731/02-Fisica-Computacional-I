//
// Created by Jorge Pulido on 09/05/2020.
//
//TODO Comentar
//TODO checkear liberacion de memorio
//TODO limpiar
//TODO documentar
//TODO Eliminar funciones no usadas


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

void rangosArrayUnidimensional_float(float *array, int columnas, float *rangeX, float *rangeY, int accumulated, float step)
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
            if (((float)i * step) > rangeX[1])
            {
                rangeX[1] = (float)i * step;
            }
        }
        i++;
    }
}

void rangosArrayUnidimensional_int(int *array, int columnas, float *rangeX, float *rangeY, int accumulated, float step)
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
        if ((float)array[i] > rangeY[1])
        {
            rangeY[1] = (float)array[i];
        }
        if ((float)array[i] < rangeY[0])
        {
            rangeY[0] = (float)array[i];
        }
        if (array[i] > 0)
        {
            if (((float)i * step) > rangeX[1])
            {
                rangeX[1] = (float)i * step;
            }
        }
        i++;
    }
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
    if (dt > 0)
    {
        *t = *t + dt;
    }
    return desintegraciones;
}

void simulateFirstStepDisintegrationsMTimes(int *arrayIn, int *arrayOut, int length, float p, int *histogram, int M)
{
    int j;
    for (j = 0; j < M; j++)
    {
        //Actuación por cada muestra
        int disintegrations = simularDesintegracion(arrayIn, arrayOut, length, p, 0, 0);
        histogram[disintegrations]++;
    }
}

void simulateFullDisintegration(int *arrayIn, int *arrayOut, int length, float p, int *disintegrations, float *t, float dt, int steps, float *disintegrationTime, float *accumulated, int accumulate)
{
    int totalDisintegrations = length, i = 0;
    float totalTime = 0;
    while (totalDisintegrations > 0 || i < steps)
    {
        totalDisintegrations -= simularDesintegracion(arrayIn, arrayOut, length, p, &totalTime, dt);
        if (i <= steps)
        {
            t[i] = totalTime;
            if (accumulate == 1)
            {
                accumulated[i] += totalDisintegrations;
            }
            else
            {
                disintegrations[i] = totalDisintegrations;
            }
        }
        i++;
        if (totalDisintegrations <= length / 2 && disintegrationTime[0] == 0)
        {
            disintegrationTime[0] = totalTime;
        }
        if (totalDisintegrations == 0 && disintegrationTime[1] == 0)
        {
            disintegrationTime[1] = totalTime;
        }
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

void print_array_2d_to_file_float_int(char *nombre, float *col1, int *col2, int columnas)
{
    int i = 0;
    FILE *output_txt = fopen(nombre, "w");
    while (i < columnas)
    {
        fprintf(output_txt, "%f %i\n", col1[i], col2[i]);
        i++;
    }
    fclose(output_txt);
}

void print_array_2d_to_file_float_float(char *nombre, float *col1, float *col2, int columnas, int skippingStep)
{
    int i = 0;
    FILE *output_txt = fopen(nombre, "w");
    while (i < columnas)
    {
        if (i % skippingStep == 0)
        {
            fprintf(output_txt, "%f %f\n", col1[i], col2[i]);
        }
        i++;
    }
    fclose(output_txt);
}

void print_array_1d_to_file_float(char *nombre, float *array, int columnas)
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

void print_array_1d_to_file_int(char *nombre, int *array, int columnas)
{
    int i = 0;
    FILE *output_txt = fopen(nombre, "w");
    while (i < columnas)
    {
        fprintf(output_txt, "%i\n", array[i]);
        i++;
    }
    fclose(output_txt);
}

float inputParameter(char name[], int iterator, float defaultValue)
{
    if (name[0] != ' ')
    {
        if (iterator == -1)
        {
            printf("Insert %s (default = %f): ", name, defaultValue);
        }
        else
        {
            printf("Insert %s[%i] (default = %f): ", name, iterator, defaultValue);
        }
    }
    int i = 0;
    char buffer[10] = "";
    float returnVal = 0;
    while ((buffer[i++] = getchar()) != '\n')
    {
    }
    if (buffer[0] == '\n')
    {
        returnVal = defaultValue;
    }
    else
    {
        sscanf(buffer, "%f", &returnVal);
    }
    return returnVal;
}

void simulateF_t(float *F_t, float *t, int length, float p, float dt, int steps, int M, float *disintegrationTimes)
{
    int i, j;
    int **disintegrations = (int **)calloc(steps, sizeof(int *));
    if (disintegrations == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    float **disintegrationTimes_temp = (float **)calloc(M, sizeof(float *));
    if (disintegrationTimes_temp == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    int **disintegrationArray = (int **)calloc(M, sizeof(int *));
    if (disintegrationArray == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    for (i = 0; i < M; i++)
    {
        disintegrationArray[i] = (int *)calloc(length, sizeof(int));
        if (disintegrationArray[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        disintegrationTimes_temp[i] = (float *)calloc(2, sizeof(float));
        if (disintegrationTimes_temp[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        disintegrations[i] = (int *)calloc(steps, sizeof(int));
        if (disintegrations[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }
    float disintegrationTime = 0, semidisintegrationTime = 0;
    for (i = 0; i < M; i++)
    {
        simulateFullDisintegration(disintegrationArray[i], disintegrationArray[i], length, p, disintegrations[i], t, dt, steps, disintegrationTimes_temp[i], NULL, 0);
        semidisintegrationTime += disintegrationTimes_temp[i][0];
        disintegrationTime += disintegrationTimes_temp[i][1];
    }
    disintegrationTimes[0] = (float)(semidisintegrationTime / M);
    disintegrationTimes[1] = (float)(disintegrationTime / M);
    for (j = 0; j < steps; j++)
    {
        long temp = 0;
        for (i = 0; i < M; i++)
        {
            temp += disintegrations[i][j];
        }
        F_t[j] += ((float)length - (float)(temp / M)) / (float)length;
    }
    free(disintegrationTimes_temp);
    free(disintegrations);
}

void checkMarkov(float *markov, float *t, int length, float p, float dt, int steps, int M, int l, float *disintegrationTimes)
{
    int i, j;
    float *accumulated = (float *)calloc(steps, sizeof(float));
    if (accumulated == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    float **disintegrationTimes_temp = (float **)calloc(M, sizeof(float *));
    if (disintegrationTimes_temp == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    int **disintegrationArray = (int **)calloc(M, sizeof(int *));
    if (disintegrationArray == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    for (i = 0; i < M; i++)
    {
        disintegrationArray[i] = (int *)calloc(length, sizeof(int));
        if (disintegrationArray[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        disintegrationTimes_temp[i] = (float *)calloc(2, sizeof(float));
        if (disintegrationTimes_temp[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }
    float disintegrationTime = 0, semidisintegrationTime = 0;
    for (i = 0; i < M; i++)
    {
        simulateFullDisintegration(disintegrationArray[i], disintegrationArray[i], length, p, NULL, t, dt, steps, disintegrationTimes_temp[i], accumulated, 1);
        semidisintegrationTime += disintegrationTimes_temp[i][0];
        disintegrationTime += disintegrationTimes_temp[i][1];
    }
    disintegrationTimes[0] = (float)(semidisintegrationTime / M);
    disintegrationTimes[1] = (float)(disintegrationTime / M);
    for (j = 0; j + l < steps; j++)
    {
        markov[j]= (float)(accumulated[j + l] / accumulated[j]);
    }
    free(disintegrationTimes_temp);
}
