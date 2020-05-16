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

/**
 * 
 * Objetivos
 * =========
 * 
 * Simulación de la primera etapa de desintegración del isótopo de cobalto 60 para diversas casuísticas,cálculo de histogramas para cada una de las iteraciones de dichos casos, y ponderación de todos los histogramas obtenidos.
 * 
 * Para cada una de las casuísticas planteadas, se realizará el siguiente proceso:
 *
 * Mediante la randomización computacional, se tomará un array unidimensional de tamaño ``N_0`` con valores inicializados a 0, y se recorrerán sus posiciones una a una, generandose un número aleatorio entre 0 y 1, y se comparará con el valor ``p_desintegration`` que marcará el 
 * 
 * 
 * 
 * .. figure:: ../_static/ejercicio1_resultados.png
 *    :align: center 
 * 
 *    Resultados de simulación */
int ejercicio1(const char outPath[])
{

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Declaración de variables generales y arrays dinámicos
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
    int defaultN_0[4] = {20, 50, 100, 1000};
    
    // Default values for p_desintegration
    float defaultp[4] = {0.5,0.2,0.1,0.01};
    
    // Default values for M
    int defaultM[4] = {1000000,1000000,1000000,1000000};

    printf("\n/////////////////////////////////////////////////////\n");
    printf("\n/////////////////////EJERCICIO 1/////////////////////\n");
    printf("\n/////////////////////////////////////////////////////\n");

    
    int maxScenarios = (int)inputParameter("maxScenarios",-1,4);

    // Dynamic array contaning initial amount of nuceleous of each scenario
    int *N_0 = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the iterations to be simulated for each scenario
    int *M = (int *)calloc(maxScenarios, sizeof(int));

    // Dynamic array contaning the iterations to be simulated for each scenario
    float *p_desintegration = (float *)calloc(maxScenarios, sizeof(float));

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Bucle de toma de datos por consola
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    while (1)
    {
        if (scenarios < 4){
            N_0[scenarios]=(int)inputParameter("N_0",scenarios,defaultN_0[scenarios]);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, defaultp[scenarios]);
            M[scenarios]=(int)inputParameter("M",scenarios,defaultM[scenarios]);
        }
        else {
            //En caso de que queramos añadir más casos de los especificados en el enunciado
            N_0[scenarios]=(int)inputParameter("N_0",scenarios,0);
            p_desintegration[scenarios] = inputParameter("p_desintegration", scenarios, 0);
            M[scenarios]=(int)inputParameter("M",scenarios,0);

        }
        scenarios += 1;
        if (scenarios >= maxScenarios)
        {
            printf("You reached the maximum supported scenarios, press enter to start simulation.\n");
            while (getchar()!='\n'){}
            break;
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

    printf("\nAnalizando %i casos\n", scenarios);

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Bucle de actuación sobre cada casuística
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for (i = 0; i < scenarios; i++)
    {
        printf("\n-------------SIMULANDO CASO %i-------------\n", i);

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Cálculo de P(x)
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        simulateFirstStepDisintegrationsMTimes(initialNucleus[i],
                                               disintegrationArray[i],
                                               N_0[i],
                                               p_desintegration[i],
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
        sprintf(fileName, "%s/data1_%i.plot", outPath, i);

        print_array_1d_to_file_float(fileName, p_x[i], N_0[i]);

        // *********************************************************************
        //  Cálculo de máximos y mínimos en ambos ejes de todas las casuísticas
        //        para englobar todos los valores en una misma gráfica
        // *********************************************************************
        rangosArrayUnidimensional_float(p_x[i], N_0[i], rangeX, rangeY, 1, 1);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Configuración de pipe con GNUPlot para ploteo por pantalla
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // *************************************************************************
    // Verificación de valores por defecto para añadir recta teórica
    // *************************************************************************
    float lambda=0;
    for (i = 0; i < scenarios; i++)
    {
        if (i==0){
            lambda=((float)N_0[i])*p_desintegration[i];
        }else
        {
            if (((float)N_0[i])*p_desintegration[i] != lambda){
                lambda=0;
            }
        }
        
    }
    
    printf("\n-------------GENERANDO GRAFICA-------------\n");


    FILE *GNUPlotPipe = popen("GNUplot -persist", "w");
    int GNUNumberOfCommands = 6; //Número de mensajes que se enviarán por el pipe
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

    //Creación de strings con formato
    j = 0;
    if (lambda>0){
    sprintf(GNUCommands[j++], "set title \"Distribución de probabilidad de Poisson con {/Symbol l}=%2.f\"", lambda);
    }else
    {
    sprintf(GNUCommands[j++], "set title \"Distribución de probabilidad de Poisson");
    }
    sprintf(GNUCommands[j++], "set xrange [%.2f:%.2f]\n set xlabel \"Desintegraciones\"", rangeX[0], rangeX[1] * 1.2);
    sprintf(GNUCommands[j++], "set yrange [%.2f:%.2f]\n set ylabel \"p\"", rangeY[0], rangeY[1] * 1.2);
    sprintf(GNUCommands[j++], "set key");
    sprintf(GNUCommands[j++], "poisson(x, mu) = exp(-mu)*(mu**x)/gamma(x + 1)");
    if (lambda>0){
        sprintf(GNUCommands[j], "plot poisson(x, %f) title \"Teórica\" linecolor rgb \"black\" lw 1", lambda);
        i=0;
    }else{
        i=0;
        sprintf(GNUCommands[j], "plot  \"%s/data1_%i.plot\" title \"Sim N_0=%i, p=%.2f\" with lines", outPath, i, N_0[i], p_desintegration[i]);
        i++;
    }

    for (i = i; i < scenarios; i++)
    {
        char temp[100] = "";
        sprintf(temp, ",  \"%s/data1_%i.plot\" title \"Sim N_0=%i, p=%.2f\" with lines", outPath, i, N_0[i], p_desintegration[i]);
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
    free(rangeX);
    free(rangeY);
    free(GNUCommands);
    return 0;
}