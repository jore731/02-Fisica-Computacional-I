//
// Created by Jorge Pulido on 09/05/2020.
//
//TODO Comentar
//TODO limpiar
//TODO documentar

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "PEC2Lib.h"

/** Ejercicio3 */
int ejercicio4(const char outPath[])
{
    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 4/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");
    printf("\nComprobacion de markovianidad durante la simulacion de desintegracion de M conjuntos de N_0 nucleos activos de Cobalto 60.\n\n\n");

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
    int defaultN_0[3] = {10000, 10000, 10000};

    // Default values for p_desintegration
    float defaultp[3] = {0.001, 0.001, 0.001};

    // Default values for M
    float defaultM[3] = {10, 100, 1000};

    // Default values for lambda_0
    float defaultLambda_0[3] = {0.13, 0.13, 0.13};

    // Default values for plottingStep
    int defaultPlottingStep[3] = {130, 130, 130};

    // Input maxScenarios from console
    int maxScenarios = (int)inputParameter("maxScenarios", -1, 3);

    // Input maxTime to be represented ( not simulated)
    int maxTime = (int)inputParameter("maxTime", -1, 80);

    printf("\n\n");

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *N_0 = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the threshold value for p to be used in simulation
    // for each scenario
    float *p_desintegration = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning the iterations to be simulated for each scenario
    int *M = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the lambda_0 value to be used in simulation
    // for each scenario
    float *lambda_0 = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning the number of steps to be represented for each scenario
    int *steps = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the dt of each step on each scenario
    float *dt = (float *)calloc(maxScenarios, sizeof(float));

    // Dynamic array contaning plotting step for the representation of each scenario.
    int *plottingStep = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the timestep(plottingStep * ) of each scenario
    float *Dt = (float *)calloc(maxScenarios, sizeof(float));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Console input data loop for adding scenarios
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    while (1)
    {
        if (scenarios < 3)
        {
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, defaultN_0[scenarios]);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, defaultp[scenarios]);
            plottingStep[scenarios] = inputParameter("plottingStep", scenarios, defaultPlottingStep[scenarios]);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, defaultLambda_0[scenarios]);
            M[scenarios] = inputParameter("M", scenarios, defaultM[scenarios]);
        }
        else
        {
            //Non default scenarios
            N_0[scenarios] = (int)inputParameter("N_0", scenarios, 0);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, 0);
            plottingStep[scenarios] = inputParameter("plottingStep", scenarios, 0);
            lambda_0[scenarios] = inputParameter("lambda_0", scenarios, 0);
            M[scenarios] = inputParameter("M", scenarios, 0);
        }
        printf("\n\n");
        // Dependent parameters
        dt[scenarios] = p_desintegration[scenarios] / lambda_0[scenarios];
        Dt[scenarios] = plottingStep[scenarios] * dt[scenarios];
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

    // 2D array that will hold the results on the markov verification along the simulation for each scenario
    float **markov = (float **)calloc(scenarios, sizeof(float *));
    if (markov == NULL)
    {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    // Bidimensional array rows initizalization
    for (i = 0; i < scenarios; i++)
    {
        markov[i] = (float *)calloc(steps[i], sizeof(float));
        if (markov[i] == NULL)
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

        printf("\nAtención! Este proceso puede durar unos minutos, espere a que la gráfica sea generada.\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Markovian verification
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        checkMarkov(markov[i],
                    t[i],
                    N_0[i],
                    p_desintegration[i],
                    dt[i],
                    steps[i],
                    M[i],
                    plottingStep[i],
                    totalTime[i]);
        printf("\nSemidesintegracion completada en :%f years\n", totalTime[i][0]);
        printf("\nDesintegracion completada en :%f years\n", totalTime[i][1]);

        // *********************************************************************
        // Comprobaci?n de que outputPath est? accesible
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
        sprintf(fileName, "%s/data4_%i.plot", outPath, i);

        print_array_2d_to_file_float_float(fileName, t[i], markov[i], steps[i], plottingStep[i]);

        // *********************************************************************
        //  Plotting ranges calculation
        // *********************************************************************

        rangosArrayUnidimensional_float(markov[i], steps[i], rangeX, rangeY, 0, dt[i]);

        // *************************************************************************
        // GNUPlot configuration
        // *************************************************************************

        printf("\n-------------GENERANDO GRAFICA-------------\n");

        // Pipe1 to communicate with GNUPlot
        FILE *GNUPlotPipe = popen("GNUplot -persist", "w");

        //Messages to be sent throught the pipe
        int GNUNumberOfCommands = 6;

        // Array to define each messages length (Hard coded since it shouldnt change)
        int commandLengths[GNUNumberOfCommands];
        j = 0;
        commandLengths[j++] = 80;
        commandLengths[j++] = 25;
        commandLengths[j++] = 25;
        commandLengths[j++] = 50;
        commandLengths[j++] = 10;
        commandLengths[j++] = 200;

        // Array of strings of with size defined by commandLengths
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

        // GNU Commands definition.
        j = 0;
        sprintf(GNUCommands[j++], "set title \"Tendencia Markoviana para {/Symbol l}_0 =%.3f,{/Symbol D} t = %f\"", lambda_0[i], Dt[i]);
        sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]\n set xlabel \"t (years)\"", rangeX[0], rangeX[1] * 1.2);
        sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]\n set ylabel \"prob(X>t+{/Symbol D} t | X>t)\"", rangeY[0], rangeY[1] * 1.2);
        sprintf(GNUCommands[j++], "set key left bottom");
        sprintf(GNUCommands[j++], "theoretical(x, mu,Dt) = exp(-mu*Dt)");
        sprintf(GNUCommands[j], "plot theoretical(x, %f, %f) title \"Teórica\" linecolor rgb \"black\" lw 1", lambda_0[i], Dt[i]);
        char temp[100] = "";
        sprintf(temp, ", \"%s/data4_%i.plot\" using 1 : 2 pt 7 ps 1  title \"Sim p=%.3f, {/Symbol l}_0 =%.3f\"", outPath, i, p_desintegration[i], lambda_0[i]);
        strcat(GNUCommands[j], temp);

        //Execution of GNUPlot commands
        for (j = 0; j < GNUNumberOfCommands; j++)
        {
            fprintf(GNUPlotPipe, "%s \n", GNUCommands[j]);
        }
        // Closes the pipe after GNUPlot is closed.
        pclose(GNUPlotPipe);
        free(GNUCommands);
    }

    // Freeing up memory after the simulation and plotting is done. (Could be better to do it right after stopping to use each variable)
    free(rangeX);
    free(rangeY);
    free(N_0);
    free(p_desintegration);
    free(M);
    free(steps);
    free(lambda_0);
    free(dt);
    free(plottingStep);
    free(Dt);
    free(t);
    free(totalTime);
    free(markov);

    return 0;
}