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

int ejercicio1(const char outPath[])
{

    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 1/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");
    printf("\nComprobacion de la distribucion de Poisson aplicada a la primera etapa del proceso de desintegracion del cobalto 60.\n\n\n");
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
    int defaultN_0[4] = {20, 50, 100, 1000};

    // Default values for p_disintegration
    float defaultp[4] = {0.5, 0.2, 0.1, 0.01};

    // Default values for M
    int defaultM[4] = {1000000, 1000000, 1000000, 1000000};

    // Input maxScenarios from console
    int maxScenarios = (int)inputParameter("maxScenarios", -1, 4);

    printf("\n\n");

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *N_0 = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the iterations to be simulated for each scenario
    int *M = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the threshold value for p to be used in simulation
    // for each scenario
    float *p_disintegration = (float *)calloc(maxScenarios, sizeof(float));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Console input data loop for adding scenarios
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    while (1)
    {
        if (scenarios < 4)
        {
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, defaultN_0[scenarios]);
            p_disintegration[scenarios] = inputParameter("p_disintegration", scenarios, defaultp[scenarios]);
            M[scenarios] = (int)inputParameter("M", scenarios, defaultM[scenarios]);
        }
        else
        {
            //Non default scenarios
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, 0);
            p_disintegration[scenarios] = inputParameter("p_disintegration", scenarios, 0);
            M[scenarios] = (int)inputParameter("M", scenarios, 0);
        }
        printf("\n\n");
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

    // 2D array that holds the values for the nucleus ready to start the simulation
    int **initialNucleus = (int **)calloc(scenarios, sizeof(int *));
    if (initialNucleus == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // 2D array that will hold the simulation output data for each scenario
    int **disintegrationArray = (int **)calloc(scenarios, sizeof(int *));
    if (disintegrationArray == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    //2D array that will hold the absolute histogram data for each scenario
    int **P_x = (int **)calloc(scenarios, sizeof(int *));
    if (P_x == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    //2D array that will hold the ponderated histogram data for each scenario (P_x/M)
    float **p_x = (float **)calloc(scenarios, sizeof(float *));
    if (p_x == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // Bidimensional array rows initizalization
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

    printf("\nAnalizando %i casos\n", scenarios);

    for (i = 0; i < scenarios; i++)
    {
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Data processing loop for each scenario
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        printf("\n-------------SIMULANDO CASO %i-------------\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Disintegration simulation
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        simulateFirstStepDisintegrationsMTimes(initialNucleus[i],
                                               disintegrationArray[i],
                                               N_0[i],
                                               p_disintegration[i],
                                               P_x[i],
                                               M[i]);

        // ******************************************************************
        // P_x -> p_x
        // ******************************************************************

        arrayIterationalDivider(P_x[i], p_x[i], M[i], N_0[i]);

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
        sprintf(fileName, "%s/data1_%i.plot", outPath, i);

        print_array_1d_to_file_float(fileName, p_x[i], N_0[i]);

        // *********************************************************************
        //  Plotting ranges calculation
        // *********************************************************************

        rangosArrayUnidimensional_float(p_x[i], N_0[i], rangeX, rangeY, 1, 1);
    }

    // *************************************************************************
    //            Lambda calculation for theoretical curve if apply
    //              (Only if p*N_0 is equal for every scenario)
    // *************************************************************************

    float lambda = 0;
    for (i = 0; i < scenarios; i++)
    {
        if (i == 0)
        {
            lambda = ((float)N_0[i]) * p_disintegration[i];
        }
        else
        {
            if (((float)N_0[i]) * p_disintegration[i] != lambda)
            {
                lambda = 0;
            }
        }
    }

    // *************************************************************************
    // GNUPlot configuration
    // *************************************************************************

    printf("\n-------------GENERANDO GRAFICA-------------\n");

    // Pipe to communicate with GNUPlot
    FILE *GNUPlotPipe = popen("gnuplot -persist", "w");

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
    if (lambda > 0)
    {
        sprintf(GNUCommands[j++], "set title \"Distribución de probabilidad de Poisson con {/Symbol l}=%2.f\"", lambda);
    }
    else
    {
        sprintf(GNUCommands[j++], "set title \"Distribución de probabilidad de Poisson\"");
    }
    sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]\n set xlabel \"Desintegraciones\"", rangeX[0], rangeX[1] * 1.2);
    sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]\n set ylabel \"p\"", rangeY[0], rangeY[1] * 1.2);
    sprintf(GNUCommands[j++], "set key");
    sprintf(GNUCommands[j++], "poisson(x, mu) = exp(-mu)*(mu**x)/gamma(x + 1)");

    // If there is a common theoretical curve
    if (lambda > 0)
    {
        sprintf(GNUCommands[j], "plot poisson(x, %f) title \"Teórica\" linecolor rgb \"black\" lw 1", lambda);
        i = 0;
    }
    else
    {
        i = 0;
        sprintf(GNUCommands[j], "plot  \"%s/data1_%i.plot\" title \"Sim N_0=%i, p=%.2f\" with lines", outPath, i, N_0[i], p_disintegration[i]);
        i++;
    }

    for (i = i; i < scenarios; i++)
    {
        char temp[100] = "";
        sprintf(temp, ",  \"%s/data1_%i.plot\" title \"Sim N_0=%i, p=%.2f\" with lines", outPath, i, N_0[i], p_disintegration[i]);
        strcat(GNUCommands[j], temp);
    }

    //Execution of GNUPlot commands
    for (i = 0; i < GNUNumberOfCommands; i++)
    {
        fprintf(GNUPlotPipe, "%s \n", GNUCommands[i]);
    }

    // Closes the pipe after GNUPlot is closed.
    pclose(GNUPlotPipe);

    // Freeing up memory after the simulation and plotting is done. (Could be better to do it right after stopping to use each variable)
    free(rangeX);
    free(rangeY);
    free(N_0);
    free(M);
    free(p_disintegration);
    free(initialNucleus);
    free(disintegrationArray);
    free(P_x);
    free(p_x);
    free(GNUCommands);
    
    return 0;
}