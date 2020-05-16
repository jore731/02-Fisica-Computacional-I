//
// Created by Jorge Pulido on 09/05/2020.
//

#include <stdio.h>
#include <stdlib.h>

#include "PEC2Lib.h"
#include "ejercicio1.h"
#include "ejercicio2.h"
#include "ejercicio3.h"
#include "ejercicio4.h"

//Default path for ouput data files
const char outPath[40] = "outputFiles";

int main()
{
    system("mode 650");

    int answer = 0;
    do
    {
        do
        {
            srand(time(NULL));
            printf("\n-----------------------------------------------------------\n");
            printf("\n-PEC2 - C: Procesos de Poisson y desintegracion radiactiva-\n");
            printf("\n-----------------------------------------------------------\n");
            printf("\nJorge Pulido Lopez\n");
            printf("\njpulido147@alumno.uned.es\n");
            printf("\n\n\n");
            printf("\nPorfavor, seleccione uno de los siguientes ejercicios:\n");
            printf("\n    0: exit\n\n");
            printf("\n    1: Comprobacion de la distribucion de Poisson aplicada a la primera etapa del proceso de desintegracion del cobalto 60.\n\n");
            printf("\n    2: Comprobacion de la ley de decaimiento exponencial aplicada al proceso de desintegracion completo del cobalto 60.\n\n");
            printf("\n    3: \n\n");
            printf("\n    4: \n\n");
            printf("\n0, 1, 2, 3, 4 (default 0) >> ");
            scanf("%i", &answer);
            getchar();
        } while (answer < 0 || answer > 4);
        switch (answer)
        {
        case 1:
            system("cls");
            ejercicio1(outPath);
            break;
        case 2:
            system("cls");
            ejercicio2(outPath);
            break;
        case 3:
            system("cls");
            ejercicio3(outPath);
            break;
        case 4:
            system("cls");
            ejercicio4(outPath);
            break;
        default:
            break;
        }
        printf("\nPress enter to go back to main menu.\n");
        getchar();
        system("cls");
    } while (answer != 0);
    return 0;
}