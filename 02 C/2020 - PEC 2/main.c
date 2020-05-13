#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "PEC2Lib.h"
//
// Created by Jorge Pulido on 09/05/2020.
//

const int MAX_SCENARIOS = 4;
const char outPath[40] = "outputFiles/testing/some";

int main()
{
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Declaración de variables generales y arrays dinámicos
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    int scenarios = 0, DEBUG = 0;
    char answer = ' ';
    int i, j;

    int *N_0 = (int *)calloc(MAX_SCENARIOS, sizeof(int));
    int *M = (int *)calloc(MAX_SCENARIOS, sizeof(int));
    float *p_desintegration = (float *)calloc(MAX_SCENARIOS, sizeof(float));
    float *dt = (float *)calloc(MAX_SCENARIOS, sizeof(float));
    float *t = (float *)calloc(MAX_SCENARIOS, sizeof(int));
    float *rangeX = (float *)calloc(2, sizeof(float));
    float *rangeY = (float *)calloc(2, sizeof(float));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Bucle de toma de datos por consola
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Asignación de memorias en array bidimensional de tamaño variable
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
        printf("\n-------------SIMULANDO CASO %i-------------\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Actuación sobre cada casuística
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Cálculo de P(x)
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        simulateFirstStepDisintegrationsMTimes(initialNucleus[i],
                                               disintegrationArray[i],
                                               N_0[i],
                                               p_desintegration[i],
                                               &t[i],
                                               dt[i],
                                               P_x[i],
                                               M[i]);
        // ******************************************************************
        // Declaración de variables generales y arrays dinámicos
        // ******************************************************************
        arrayIterationalDivider(P_x[i], p_x[i], M[i], N_0[i]);

        // *********************************************************************
        // Comprobación de que outputPath está accesible
        // *********************************************************************
        if (checkAndCreateDirectory(outPath) == -1)
        {
            return -1;
        }

        printf("\n-------------EXPORTANDO CASO %i-------------\n", i);
        // *********************************************************************
        // Exportar datos de ploteado a outputPath
        // *********************************************************************
        char fileName[50];
        sprintf(fileName, "%s/data_%i.plot", outPath, i);

        print_array_1d_to_file(fileName, p_x[i], N_0[i]);

        // *********************************************************************
        //  Cálculo de máximos y mínimos en ambos ejes de todas las casuísticas
        //        para englobar todos los valores en una misma gráfica
        // *********************************************************************
        rangosArrayUnidimensional(p_x[i], N_0[i], rangeX, rangeY, 1);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Configuración de pipe con GNUPlot para ploteo por pantalla
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    printf("\n-------------GENERANDO GRAFICA-------------\n");

    FILE *GNUPlotPipe = popen("GNUplot -persist", "w");
    int GNUNumberOfCommands = 6; //Número de mensajes que se enviarán por el pipe
    int commandLengths[GNUNumberOfCommands];
    j=0;
    commandLengths[j++] = 80;
    commandLengths[j++] = 25;
    commandLengths[j++] = 25;
    commandLengths[j++] = 50;
    commandLengths[j++] = 10;

    for (i = 0; i < scenarios+1; i++)
    {
        commandLengths[j]+=100;
    }

    char **GNUCommands = (char **)calloc(GNUNumberOfCommands, sizeof(char *));
    for ( i = 0; i < GNUNumberOfCommands; i++)
    {
        GNUCommands[i] = (char *)calloc(commandLengths[i], sizeof(char));
        if (GNUCommands[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }

    //Creación de strings con formato
    j=0;
    sprintf(GNUCommands[j++], "set title \"Distribución de probabilidad de Poisson con {/Symbol l}=10\"");
    sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]", rangeX[0], rangeX[1] * 1.2);
    sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]", rangeY[0], rangeY[1] * 1.2);
    sprintf(GNUCommands[j++], "set key");
    sprintf(GNUCommands[j++], "poisson(x, mu) = exp(-mu)*(mu**x)/gamma(x + 1)");
    sprintf(GNUCommands[j], "plot poisson(x, % i) title \"Teórica\" linecolor rgb \"black\" lw 1", 10);

    for ( i = 0; i < scenarios; i++)
    {
        char temp[100]="";
        sprintf(temp, ",  \"%s/data_%i.plot\" title \"Sim N_0=%i, p=%.2f\" with lines", outPath,i,N_0[i], p_desintegration[i]);
        strcat(GNUCommands[j], temp);
    }
    

    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        fprintf(GNUPlotPipe, "%s \n", GNUCommands[i]);
    }

    pclose(GNUPlotPipe);

    free(P_x);
    free(p_x);
    free(initialNucleus);
    free(disintegrationArray);
    free(N_0);
    free(M);
    free(p_desintegration);
    free(dt);
    free(t);
    free(rangeX);
    free(rangeY);
    getchar();
    getchar();
}