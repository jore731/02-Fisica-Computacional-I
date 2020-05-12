//
// Created by Jorge Pulido on 09/05/2020.
//

#include <stdlib.h>
#include <stdio.h>

#include "PEC2Lib.h"

const int MAX_SCENARIOS = 2;
const char outPath[40] = "outputFiles/testing/some";

int main()
{
    // *************************************************************************
    // Declaración de variables generales y arrays dinámicos
    // *************************************************************************
    int scenarios = 0;
    char answer = ' ';
    int i, j;

    int *N_0 = (int *)calloc(MAX_SCENARIOS, sizeof(int));
    int *M = (int *)calloc(MAX_SCENARIOS, sizeof(int));
    float *p_desintegration = (float *)calloc(MAX_SCENARIOS, sizeof(float));
    float *dt = (float *)calloc(MAX_SCENARIOS, sizeof(float));
    float *t = (float *)calloc(MAX_SCENARIOS, sizeof(int));

    // *****************************************************************************
    // Bucle de toma de datos por consola
    // *****************************************************************************
    while (1)
    {
        printf("Insert N_0: ");
        scanf(" %i", &N_0[scenarios]);
        printf("N_0[%i] = %i\n", scenarios, N_0[scenarios]);
        printf("Insert p: ");
        scanf(" %f", &p_desintegration[scenarios]);
        printf("p[%i] = %f\n", scenarios, p_desintegration[scenarios]);
        printf("Insert dt: ");
        scanf(" %f", &dt[scenarios]);
        printf("dt[%i] = %f\n", scenarios, dt[scenarios]);
        printf("Insert M: ");
        scanf(" %i", &M[scenarios]);
        printf("M[%i] = %i\n", scenarios, M[scenarios]);
        scenarios += 1;
        if (scenarios >= MAX_SCENARIOS)
        {
            printf("You reached the maximum supported scenarios\n");
            scanf(" %c");
            break;
        }
        else
        {
            char answer = ' ';
            while (1)
            {
                printf("Do you want to add more scenarios? (y/n):\n");
                scanf(" %c", &answer);
                if (answer != 'n' && answer != 'y')
                { /* Input "abc" */
                    printf("Invalid input. Try again\n");
                }
                else if (answer == 'n')
                {
                    break;
                }
                else
                {
                    break;
                }
            }
            if (answer == 'n')
            {
                break;
            }
        }
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Asignación de memorias en array bidimensional de tamaño variable
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    int **initialNucleus = (int **)calloc(scenarios, sizeof(int *));
    if (initialNucleus == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    int **disintegrationArray = (int **)calloc(scenarios, sizeof(int *));
    if (disintegrationArray == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    int **P_x = (int **)calloc(scenarios, sizeof(int *));
    if (P_x == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    float **p_x = (float **)calloc(scenarios, sizeof(float *));
    if (p_x == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    // Bucle de asignación de memorias para cada fila del array bidimensional
    for (i = 0; i < scenarios; i++)
    {

        initialNucleus[i] = (int *)calloc(N_0[i], sizeof(int));
        if (initialNucleus[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        disintegrationArray[i] = (int *)calloc(N_0[i], sizeof(int));
        if (disintegrationArray[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        P_x[i] = (int *)calloc(N_0[i], sizeof(int));
        if (P_x[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        p_x[i] = (float *)calloc(N_0[i], sizeof(float));
        if (p_x[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }

    // *************************************************************************
    // Bucle de procesamiento aplicado a cada casuística por igual
    // *************************************************************************
    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 1/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");
    printf("\nAnalizando %i casos\n", scenarios);
    for (i = 0; i < scenarios; i++)
    {
        //Actuación sobre cada casuistica
        simulateFirstStepDisintegrationsMTimes(initialNucleus[i],
                                               disintegrationArray[i],
                                               N_0[i],
                                               p_desintegration[i],
                                               &t[i],
                                               dt[i],
                                               P_x[i],
                                               M[i]);

        arrayIterationalDivider(P_x[i], p_x[i], M[i], N_0[i]);

        // printf("\n---------P_x %i-----------\n", i);
        // print_array_i_1d(P_x[i],N_0[i],1);
        // printf("\n---------p_x %i-----------\n", i);
        // print_array_f_1d(p_x[i],N_0[i],1,1);

        if (checkAndCreateDirectory(outPath) == -1)
        {
            return -1;
        }
        char filename[50];
        sprintf(filename, "%s/data_%i.plot", outPath, i);
        print_array_f_2d_to_file(filename, p_x[i], N_0[i], 1);
    }
    free(P_x);
    free(initialNucleus);
    free(disintegrationArray);
    free(N_0);
    free(M);
    free(p_desintegration);
    free(dt);
    free(t);
}