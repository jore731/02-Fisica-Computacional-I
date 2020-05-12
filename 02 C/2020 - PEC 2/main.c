//
// Created by Jorge Pulido on 09/05/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "PEC2Lib.h"


int position=4, testvasr = 0;
const int MAX_SCENARIOS = 2;
char answer;
int read = 1, scenarios = 0;
int ** nucleosIniciales, ** nucleosEtapa1;
int * N_0, * M;
float * p_desintegracion, * dt, * t;
int main() {
    setbuf(stdout, 0);
    N_0 = (int*)calloc(MAX_SCENARIOS, sizeof(int));
    M = (int*)calloc(MAX_SCENARIOS, sizeof(int));
    p_desintegracion=(float * )calloc(MAX_SCENARIOS, sizeof(float));
    dt=(float * )calloc(MAX_SCENARIOS, sizeof(float));
    t=(float * )calloc(MAX_SCENARIOS, sizeof(int));

    int i, j;

    //inicializaci�n del seed aleatorio con una variable de tiempo, de forma que la iteraci�n no sea siempre la misma.
    srand(time(NULL));

    //toma de datos en la consola
    while (read == 1) {
        printf("Insert N_0: ");
        scanf(" %i", &N_0[scenarios]);
        printf("N_0[%i] = %i\n", scenarios, N_0[scenarios]);
        printf("Insert p: ");
        scanf(" %f", &p_desintegracion[scenarios]);
        printf("p[%i] = %f\n", scenarios, p_desintegracion[scenarios]);
        printf("Insert dt: ");
        scanf(" %f", &dt[scenarios]);
        printf("dt[%i] = %f\n", scenarios, dt[scenarios]);
        printf("Insert M: ");
        scanf(" %i", &M[scenarios]);
        printf("M[%i] = %i\n", scenarios, M[scenarios]);
        scenarios += 1;
        if (scenarios >= MAX_SCENARIOS) {
            printf("You reached the maximum supported scenarios\n");
            scanf(" %c");
            read = 0;
        } else {
            answer = ' ';
            while (1) {
                printf("Do you want to add more scenarios? (y/n):\n");
                scanf(" %c", &answer);
                if (answer != 'n' && answer != 'y') { /* Input "abc" */
                    printf("Invalid input. Try again\n");
                } else {
                    break;
                }
            }
        }
        if (answer == 'n') {
            read = 0;
        }
    }


    //Asignaci�n de memorias de tama�o variable
    nucleosIniciales = (int **) calloc(scenarios, sizeof(int *));
    if (nucleosIniciales == NULL) {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }
    nucleosEtapa1 = (int **) calloc(scenarios, sizeof(int *));
    if (nucleosEtapa1 == NULL) {
        printf("No se ha podido asignar el espacio de memoria\n");
        exit(1);
    }

    for (i = 0; i < scenarios; i++) {
        nucleosIniciales[i] = (int *) calloc(N_0[i], sizeof(int));
        if (nucleosIniciales[i] == NULL) {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
        nucleosEtapa1[i] = (int *) calloc(N_0[i], sizeof(int));
        if (nucleosEtapa1[i] == NULL) {
            printf("No se ha podido asignar el espacio de memoria\n");
            exit(1);
        }
    }
    printf("\nAnalizando %i casos\n", scenarios);
    for (i=0; i<scenarios;i++){
        //Actuaci�n sobre cada casuistica
        int * histograma=(int*)calloc(N_0[i], sizeof(int));
        printf("\n---------Histograma vacio %i-----------\n", i);
        print_array_i_1d(histograma,N_0[i],1);
        for (j = 0; j<M[i]; j++){
            //Actuaci�n por cada muestra
            int desintegraciones = simularDesintegracion(nucleosIniciales[i], nucleosEtapa1[i], N_0[i],p_desintegracion[i],&t[i],dt[i]);
            histograma[desintegraciones]++;
        }
        printf("\n---------Histograma %i-----------\n", i);
        print_array_i_1d(histograma,N_0[i],1);
        int total=0;
        for (j = 0; j < N_0[i]; ++j) {
            total+=histograma[j];
        }
        printf("\n---------Total %i-----------\n", total);
        printf("\n---------M %i-----------\n", M[i]);
        printf("\n---------P %f-----------\n", p_desintegracion[i]);
        free(histograma);
    }
    free(nucleosIniciales);
    free(nucleosEtapa1);
    free(N_0);
    free(M);
    free(p_desintegracion);
    free(dt);
    free(t);
}


//
//    nucleosIniciales[0]=datosIniciales;
//    nucleosIniciales[1]=nucleosIniciales[0]+N_0[0];
//    printf("initializing");
//    for (int j = 0; j < sizeof(datosIniciales)*totalNucleos+40 ; ++j) {
//        datosIniciales[j]=j;
//    }
//    print_array_i_1d((int*)nucleosIniciales[0], 1000, 0);
//    printf("\n\n\n\n");
//    print_array_i_1d(datosIniciales, 1000, 0);
//    initializeChunkedArray(datosIniciales, nucleosIniciales, N_0, scenarios);
//
//    printf("initializing Etapa1");

//    initializeChunkedArray(datosEtapa1, nucleosEtapa1, N_0, scenarios);

//    for (int j = 0; j < scenarios; ++j) {
//        int *pttr = datosIniciales;
//        char *p = (char*)pttr;
//        p+=position*sizeof(*datosIniciales);    //increments pointer by 8 bytes
//        pttr = (int *)p;
//        nucleosIniciales[j]=pttr;
//        testvasr = N_0[j];
//        inicializar_i_unos_1d(pttr, N_0[j]);
//        position += testvasr;
//    }
//    printf("Starting");
//
//    print_array_i_1d((int *)nucleosIniciales[0], N_0[0], 1);
//    printf("---->>");
//    int tempT=t[0];
//    simularDesintegracion(nucleosIniciales[0], nucleosEtapa1[0],N_0[0], p_desintegracion[0],&t[0], dt[0]);
//    print_array_i_1d(nucleosEtapa1[0], N_0[0], 1);
//    printf("\nTook %f seconds\n", t[0]);
//    int i;
//    for (i = 0; i < scenarios; ++i) {
//        print_array_i_1d((int*)nucleosIniciales[i], N_0[i], 1);
//        printf("---->>");
//        int tempT=t[i];
//        simularDesintegracion((int*)nucleosIniciales[i], (int*)nucleosEtapa1[i],N_0[i], p_desintegracion[i],&t[i], dt[i]);
//        print_array_i_1d((int*)nucleosEtapa1[i], N_0[i], 1);
//        printf("\nTook %f seconds\n", t[i]);
//
//    }
//
//    free(datosIniciales);
//    free(datosEtapa1);






    /*
    float histograma[N_0[0]];
    float max_histograma_y, max_histograma_x;
    int nucleosIniciales[N_0[0]];
    int nucleosPaso2[N_0[0]];
    int desintegraciones=0;
    inicializar_f_ceros_1d(histograma,N_0[0]);
    inicializar_i_unos_1d(nucleosIniciales, N_0[0]);
    //crear_histograma(histograma,cases,N_0[0])

    for (int i = 0; i < M[0]; ++i) {
        desintegraciones = simularDesintegracion(nucleosIniciales,nucleosPaso2,N_0[0],p_desintegracion[0],&t[0],dt[0]);
        printf("total: %i desintegraciones\n", desintegraciones);
        histograma[desintegraciones]=histograma[desintegraciones]+1;
    }
    printf("Elapsed time = %f seg\n", t);

    print_array_f_1d(histograma, N_0[0], 1, 0);

     */





