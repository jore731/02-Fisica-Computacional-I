//
// Created by Jorge Pulido on 09/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "PEC2Lib.h"

/** Ejercicio2 */
int ejercicio2(const char outPath[])
{

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Declaraci�n de variables generales y arrays din�micos
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /** Number of scenarios to be analyzed*/
    int scenarios = 0;

    // Generic iterator
    int i, j;

    // Plotting X range
    float *rangeX = (float *)calloc(2, sizeof(float));

    // Plotting Y range
    float *rangeY = (float *)calloc(2, sizeof(float));

    // Default values for N_0
    int defaultN_0[4] = {10000, 10000, 10000, 10000};

    // Default values for p_desintegration
    float defaultp[4] = {0.5, 0.1, 0.01, 0.001};

    // Default values for lambda_0
    float defaultlambda_0[4] = {0.13, 0.13, 0.13, 0.13};

    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 2/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");

    int maxScenarios = (int)inputParameter("maxScenarios", -1, 4);

    int maxTime = (int)inputParameter("maxTime", -1, 80);

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *N_0 = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the iterations to be simulated for each scenario
    float *p_desintegration = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning the iterations to be simulated for each scenario
    float *lambda_0 = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *steps = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning initial amount of nuceleous of each scenario
    float *dt = (float *)calloc(maxScenarios, sizeof(float));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Bucle de toma de datos por consola
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    while (1)
    {
        if (scenarios < 4)
        {
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, defaultN_0[scenarios]);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, defaultp[scenarios]);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, defaultlambda_0[scenarios]);
        }
        else
        {
            //En caso de que queramos a�adir m�s casos de los especificados en el enunciado
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, 0);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, 0);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, 0);
        }
        dt[scenarios] = p_desintegration[scenarios] / lambda_0[scenarios];
        steps[scenarios] = (int)((float)maxTime / (dt[scenarios]));
        scenarios += 1;
        if (scenarios >= maxScenarios)
        {
            printf("You reached the maximum supported scenarios, press enter to start simulation.\n");
            while (getchar() != '\n')
            {
            }
            break;
        }
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Asignaci�n de memorias en array bidimensional de tama�o variable
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    int **disintegrationArray = (int **)calloc(scenarios, sizeof(int *));
    if (disintegrationArray == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    float **t = (float **)calloc(scenarios, sizeof(float *));
    if (t == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    float **totalTime = (float **)calloc(scenarios, sizeof(float *));
    if (totalTime == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    int **disintegrations = (int **)calloc(scenarios, sizeof(int *));
    if (disintegrations == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // Bucle de asignaci�n de memorias para cada fila del array bidimensional
    for (i = 0; i < scenarios; i++)
    {
        disintegrationArray[i] = (int *)calloc(N_0[i], sizeof(int));
        if (disintegrationArray[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        disintegrations[i] = (int *)calloc(steps[i], sizeof(int));
        if (disintegrations[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        t[i] = (float *)calloc(steps[i], sizeof(float));
        if (t[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        totalTime[i] = (float *)calloc(2, sizeof(float));
        if (totalTime[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }

    printf("\nAnalizando %i casos\n", scenarios);

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Bucle de actuaci�n sobre cada casu�stica
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for (i = 0; i < scenarios; i++)
    {
        printf("\n-------------SIMULANDO CASO %i-------------\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // C�lculo de P(x)
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        simulateFullDisintegration(disintegrationArray[i],
                                   disintegrationArray[i],
                                   N_0[i],
                                   p_desintegration[i],
                                   disintegrations[i],
                                   t[i],
                                   dt[i],
                                   steps[i],
                                   totalTime[i]);
        printf("\nSemidesintegracion completada en :%f years\n", totalTime[i][0]);
        printf("\nDesintegracion completada en :%f years\n", totalTime[i][1]);

        // *********************************************************************
        // Comprobaci�n de que outputPath est� accesible
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
        sprintf(fileName, "%s/data2_%i.plot", outPath, i);

        print_array_2d_to_file_float_int(fileName, t[i], disintegrations[i], steps[i]);

        printf("\n------CALCULANDO LIMITES DE GRAFICA-----\n");
        // *********************************************************************
        //  C�lculo de m�ximos y m�nimos en ambos ejes de todas las casu�sticas
        //        para englobar todos los valores en una misma gr�fica
        // *********************************************************************
        rangosArrayUnidimensional_int(disintegrations[i], steps[i], rangeX, rangeY, 1, dt[i]);
    }

    // *************************************************************************
    // Verificaci�n de valores por defecto para a�adir recta te�rica
    // *************************************************************************
    printf("\n------VERIFICANDO UNIFORMIDAD DE DATOS-----\n");

    int theoreticalN_0 = N_0[0];
    float theoreticalLambda_0 = lambda_0[0];
    for (i = 1; i < scenarios; i++)
    {
        if ((theoreticalN_0 != N_0[i]) || (theoreticalLambda_0 != lambda_0[i]))
        {
            theoreticalN_0 = 0;
            theoreticalLambda_0 = 0;
        }
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Configuraci�n de pipe con GNUPlot para ploteo por pantalla
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    printf("\n-------------GENERANDO GRAFICA-------------\n");

    FILE *GNUPlotPipe = popen("GNUplot -persist", "w");
    FILE *GNUPlotPipe2 = popen("GNUplot -persist", "w");
    int GNUNumberOfCommands = 6; //N�mero de mensajes que se enviar�n por el pipe
    int commandLengths[GNUNumberOfCommands];
    j = 0;
    commandLengths[j++] = 80;
    commandLengths[j++] = 25;
    commandLengths[j++] = 25;
    commandLengths[j++] = 50;
    commandLengths[j++] = 10;

    for (i = 0; i < scenarios + 1; i++)
    {
        commandLengths[j] += 100;
    }

    char **GNUCommands = (char **)calloc(GNUNumberOfCommands, sizeof(char *));
    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        GNUCommands[i] = (char *)calloc(commandLengths[i], sizeof(char));
        if (GNUCommands[i] == NULL)
        {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }

    //Creaci�n de strings con formato
    j = 0;
    if (theoreticalLambda_0 > 0)
    {
        sprintf(GNUCommands[j++], "set title \"Curva(s) de desintegraci�n N(t) para N_0 = %i  con {/Symbol l}_0 =%.3f\"", theoreticalN_0, theoreticalLambda_0);
    }
    else
    {
        sprintf(GNUCommands[j++], "set title \"Curva(s) de desintegraci�n N(t)");
    }
    sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]\n set xlabel \"t (years)\"", rangeX[0], rangeX[1] * 1.2);
    sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]\n set ylabel \"N\"", rangeY[0], rangeY[1] * 1.2);
    sprintf(GNUCommands[j++], "set key");
    sprintf(GNUCommands[j++], "theoretical(x, N_0,mu) = N_0*exp(-mu*x)");
    if (theoreticalLambda_0 > 0)
    {
        sprintf(GNUCommands[j], "plot theoretical(x, %i, %f) title \"Te�rica\" linecolor rgb \"black\" lw 1", theoreticalN_0, theoreticalLambda_0);
        i = 0;
    }
    else
    {
        i = 0;
        sprintf(GNUCommands[j], "plot  \"%s/data2_%i.plot\" using 1 : 2 with lines title \"Sim p=%.3f, {/Symbol l}_0 =%.3f\"", outPath, i, p_desintegration[i], lambda_0[i]);
        i++;
    }

    for (i = i; i < scenarios; i++)
    {
        char temp[100] = "";
        sprintf(temp, ", \"%s/data2_%i.plot\" using 1 : 2 with lines title \"Sim p=%.3f, {/Symbol l}_0 =%.3f\"", outPath, i, p_desintegration[i], lambda_0[i]);
        strcat(GNUCommands[j], temp);
    }

    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        fprintf(GNUPlotPipe, "%s \n", GNUCommands[i]);
    }

    sprintf(GNUCommands[1], "set xrange [50:%.2f]\n set xlabel \"t (years)\"", rangeX[1] * 1.2);
    sprintf(GNUCommands[2], "set autoscale y\n set ylabel \"N\"");
    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        fprintf(GNUPlotPipe2, "%s \n", GNUCommands[i]);
    }


    pclose(GNUPlotPipe);
    pclose(GNUPlotPipe2);
    free(rangeX);
    free(rangeY);
    free(N_0);
    free(p_desintegration);
    free(lambda_0);
    free(steps);
    free(dt);
    free(totalTime);
    free(disintegrationArray);
    free(t);
    free(disintegrations);
    free(GNUCommands);
    return 0;
}