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

int ejercicio2(const char outPath[])
{

    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 2/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");
    printf("\nComprobacion de la ley de decaimiento exponencial aplicada al proceso de desintegracion completo del cobalto 60.\n\n\n");

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Variables declaration and input data
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Number of scenarios to be analyzed
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

    // Input maxScenarios from console
    int maxScenarios = (int)inputParameter("maxScenarios", -1, 4);

    // Input maxTime to be represented ( not simulated)
    int maxTime = (int)inputParameter("maxTime", -1, 80);

    printf("\n\n");

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *N_0 = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the threshold value for p to be used in simulation
    // for each scenario
    float *p_desintegration = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning the lambda_0 value to be used in simulation
    // for each scenario
    float *lambda_0 = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning the number of steps to be represented for each scenario
    int *steps = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the dt of each step on each scenario
    float *dt = (float *)calloc(maxScenarios, sizeof(float));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Console input data loop for adding scenarios
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
            //Non default scenarios
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, 0);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, 0);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, 0);
        }
        printf("\n\n");
        // Dependent parameters
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
    //          Dyncamic arrays declaration and initialization depending on
    //                      the scenarios to be simulated
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // 2D array that will hold the nucleous information during the simulation for each scenario
    int **disintegrationArray = (int **)calloc(scenarios, sizeof(int *));
    if (disintegrationArray == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // 2D array that will hold the values of t on each step during the simulation for each scenario
    float **t = (float **)calloc(scenarios, sizeof(float *));
    if (t == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // 2D array that will hold the semidisintegration and disintegration times for each scenario
    float **totalTime = (float **)calloc(scenarios, sizeof(float *));
    if (totalTime == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // 2D array that will hold the number of remaining nucleous during the simulation for each scenario
    int **disintegrations = (int **)calloc(scenarios, sizeof(int *));
    if (disintegrations == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // Bidimensional array rows initizalization
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

    for (i = 0; i < scenarios; i++)
    {
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Data processing loop for each scenario
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        printf("\n-------------SIMULANDO CASO %i-------------\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Full disintegration simulation
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        simulateFullDisintegration(disintegrationArray[i],
                                   disintegrationArray[i],
                                   N_0[i],
                                   p_desintegration[i],
                                   disintegrations[i],
                                   t[i],
                                   dt[i],
                                   steps[i],
                                   totalTime[i],
                                   NULL,
                                   0);

        printf("\nSemidesintegracion completada en :%f years\n", totalTime[i][0]);
        printf("\nDesintegracion completada en :%f years\n", totalTime[i][1]);

        // *********************************************************************
        // Check if outpath is available
        // *********************************************************************

        if (checkAndCreateDirectory(outPath) == -1)
        {
            return -1;
        }

        printf("\n-------------EXPORTANDO CASO %i-------------\n", i);

        // *********************************************************************
        // Data export (GNUPlot input file created)
        // *********************************************************************

        // Output file name (and path if applies)
        char fileName[50];
        sprintf(fileName, "%s/data2_%i.plot", outPath, i);

        print_array_2d_to_file_float_int(fileName, t[i], disintegrations[i], steps[i]);

        // *********************************************************************
        //  Plotting ranges calculation
        // *********************************************************************

        rangosArrayUnidimensional_int(disintegrations[i], steps[i], rangeX, rangeY, 1, dt[i]);
    }

    // *************************************************************************
    //                   Checking theoretical curve viability
    //          (Only if N_0 and lambda_0 are equal for every scenario)
    // *************************************************************************

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

    // *************************************************************************
    // GNUPlot configuration
    // *************************************************************************

    printf("\n-------------GENERANDO GRAFICA-------------\n");

    // Pipe1 to communicate with GNUPlot
    FILE *GNUPlotPipe = popen("gnuplot -persist", "w");

    // Pipe2 to communicate with GNUPlot
    FILE *GNUPlotPipe2 = popen("gnuplot -persist", "w");

    //Messages to be sent throught the pipe
    int GNUNumberOfCommands = 6;

    // Array to define each messages length (Hard coded since it shouldnt change)
    int commandLengths[GNUNumberOfCommands];
    j = 0;
    commandLengths[j++] = 100;
    commandLengths[j++] = 100;
    commandLengths[j++] = 100;
    commandLengths[j++] = 50;
    commandLengths[j++] = 50;

    for (i = 0; i < scenarios + 1; i++)
    {
        commandLengths[j] += 100;
    }

    // Array of strings of with size defined by commandLengths
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

    // GNU Commands definition.
    j = 0;
    if (theoreticalLambda_0 > 0)
    {
        sprintf(GNUCommands[j++], "set title \"Curva(s) de desintegración N(t) para N_0 = %i  con {/Symbol l}_0 =%.3f\"", theoreticalN_0, theoreticalLambda_0);
    }
    else
    {
        sprintf(GNUCommands[j++], "set title \"Curva(s) de desintegración N(t)");
    }
    sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]\n set xlabel \"t (years)\"", rangeX[0], rangeX[1] * 1.2);
    sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]\n set ylabel \"N\"", rangeY[0], rangeY[1] * 1.2);
    sprintf(GNUCommands[j++], "set key");
    sprintf(GNUCommands[j++], "theoretical(x, N_0,mu) = N_0*exp(-mu*x)");

    // If there is a common theoretical curve
    if (theoreticalLambda_0 > 0)
    {
        sprintf(GNUCommands[j], "plot theoretical(x, %i, %f) title \"Teórica\" linecolor rgb \"black\" lw 1", theoreticalN_0, theoreticalLambda_0);
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

    //Execution of GNUPlot commands
    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        fprintf(GNUPlotPipe, "%s \n", GNUCommands[i]);
    }

    // Closes the pipe after GNUPlot is closed.
    pclose(GNUPlotPipe);

    sprintf(GNUCommands[1], "set xrange [50:%.2f]\n set xlabel \"t (years)\"", rangeX[1] * 1.2);
    sprintf(GNUCommands[2], "set autoscale y\n set ylabel \"N\"");

    //Execution of GNUPlot commands
    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        fprintf(GNUPlotPipe2, "%s \n", GNUCommands[i]);
    }

    // Closes the pipe after GNUPlot is closed.
    pclose(GNUPlotPipe2);

    // Freeing up memory after the simulation and plotting is done. (Could be better to do it right after stopping to use each variable)
    free(rangeX);
    free(rangeY);
    free(N_0);
    free(p_desintegration);
    free(lambda_0);
    free(steps);
    free(dt);
    free(disintegrationArray);
    free(t);
    free(totalTime);
    free(disintegrations);
    free(GNUCommands);

    return 0;
}