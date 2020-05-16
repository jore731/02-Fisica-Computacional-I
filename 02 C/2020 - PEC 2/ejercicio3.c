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

/** Ejercicio3 */
int ejercicio3(const char outPath[])
{

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Declaraci?n de variables generales y arrays din?micos
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
    int defaultN_0[2] = {1000, 1000};

    // Default values for p_desintegration
    float defaultp[2] = {0.001, 0.001};

    // Default values for M
    float defaultM[4] = {1, 100};

    // Default values for lambda_0
    float defaultLambda_0[2] = {0.13, 0.13};

    // Default values for dt
    float defaultdt[2] = {0.007692, 0.007692};

    // Default values for dt
    int defaultPlottingStep[2] = {1, 1};

    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 3/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");

    int maxScenarios = (int)inputParameter("maxScenarios", -1, 2);

    int maxTime = (int)inputParameter("maxTime", -1, 80);

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *N_0 = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the iterations to be simulated for each scenario
    float *p_desintegration = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning the iterations to be simulated for each scenario
    int *M = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *steps = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning initial amount of nuceleous of each scenario
    float *lambda_0 = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning initial amount of nuceleous of each scenario
    float *dt = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *plottingStep = (int *)calloc(maxScenarios, sizeof(int));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Bucle de toma de datos por consola
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    while (1)
    {
        if (scenarios < 4)
        {
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, defaultN_0[scenarios]);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, defaultp[scenarios]);
            plottingStep[scenarios] = inputParameter("plottingStep", scenarios, defaultPlottingStep[scenarios]);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, defaultLambda_0[scenarios]);
            M[scenarios] = inputParameter("M", scenarios, defaultM[scenarios]);
        }
        else
        {
            //En caso de que queramos a?adir m?s casos de los especificados en el enunciado
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, 0);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, 0);
            plottingStep[scenarios] = inputParameter("plottingStep", scenarios, 0);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, 0);
            M[scenarios] = inputParameter("M", scenarios, 0);
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
    // Asignaci?n de memorias en array bidimensional de tama?o variable
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
    float **F_t = (float **)calloc(scenarios, sizeof(float *));
    if (F_t == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // Bucle de asignaci?n de memorias para cada fila del array bidimensional
    for (i = 0; i < scenarios; i++)
    {
        F_t[i] = (float *)calloc(steps[i], sizeof(float));
        if (F_t[i] == NULL)
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
    // Bucle de actuaci?n sobre cada casu?stica
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for (i = 0; i < scenarios; i++)
    {
        printf("\n-------------SIMULANDO CASO %i-------------\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // C?lculo de P(x)
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        simulateF_t(F_t[i],
                    t[i],
                    N_0[i],
                    p_desintegration[i],
                    dt[i],
                    steps[i],
                    M[i],
                    totalTime[i]);
        printf("\nTiempo promedio de semidesintegracion :%f years\n", totalTime[i][0]);
        printf("\nTiempo promedio de desintegracion :%f years\n", totalTime[i][1]);

        // *********************************************************************
        // Comprobaci?n de que outputPath est? accesible
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
        sprintf(fileName, "%s/data3_%i.plot", outPath, i);



        print_array_2d_to_file_float_float(fileName, t[i], F_t[i], steps[i], plottingStep[i]);

        printf("\n------CALCULANDO LIMITES DE GRAFICA-----\n");
        // *********************************************************************
        //  C?lculo de m?ximos y m?nimos en ambos ejes de todas las casu?sticas
        //        para englobar todos los valores en una misma gr?fica
        // *********************************************************************
        rangosArrayUnidimensional_float(F_t[i], steps[i], rangeX, rangeY, 0, dt[i]);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Configuraci?n de pipe con GNUPlot para ploteo por pantalla
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        printf("\n-------------GENERANDO GRAFICA CASO %i-------------\n", i);

        FILE *GNUPlotPipe = popen("GNUplot -persist", "w");
        int GNUNumberOfCommands = 6; //N?mero de mensajes que se enviar?n por el pipe
        int commandLengths[GNUNumberOfCommands];
        j = 0;
        commandLengths[j++] = 80;
        commandLengths[j++] = 25;
        commandLengths[j++] = 25;
        commandLengths[j++] = 50;
        commandLengths[j++] = 10;
        commandLengths[j++] = 200;

        char **GNUCommands = (char **)calloc(GNUNumberOfCommands, sizeof(char *));
        for (j = 0; j < GNUNumberOfCommands; j++)
        {
            GNUCommands[j] = (char *)calloc(commandLengths[j], sizeof(char));
            if (GNUCommands[j] == NULL)
            {
                printf("No se ha podido asignar el espacio de memoria\n");
                exit(1);
            }
        }

        //Creaci?n de strings con formato
        j = 0;
        sprintf(GNUCommands[j++], "set title \"Distribución acumulada del tiempo de desintegración para {/Symbol l}_0 =%.3f\"", lambda_0[i]);
        sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]\n set xlabel \"t (years)\"", rangeX[0], rangeX[1] * 1.2);
        sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]\n set ylabel \"F\"", rangeY[0], rangeY[1] * 1.2);
        sprintf(GNUCommands[j++], "set key");
        sprintf(GNUCommands[j++], "theoretical(x, mu) = 1-exp(-mu*x)");
        sprintf(GNUCommands[j], "plot theoretical(x, %f) title \"Teórica\" linecolor rgb \"black\" lw 1", lambda_0[i]);
        char temp[100] = "";
        sprintf(temp, ", \"%s/data3_%i.plot\" using 1 : 2 with lines title \"Sim p=%.3f, {/Symbol l}_0 =%.3f\"", outPath, i, p_desintegration[i], lambda_0[i]);
        strcat(GNUCommands[j], temp);

        for (j = 0; j < GNUNumberOfCommands; j++)
        {
            fprintf(GNUPlotPipe, "%s \n", GNUCommands[j]);
        }
        pclose(GNUPlotPipe);
        free(GNUCommands);
    }

    free(rangeX);
    free(rangeY);
    free(N_0);
    free(p_desintegration);
    free(lambda_0);
    free(steps);
    free(dt);
    free(totalTime);
    free(t);
    free(F_t);
    return 0;
}