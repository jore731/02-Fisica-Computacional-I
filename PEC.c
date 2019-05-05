#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main() {
  srand(time(NULL));
  FILE * output_txt = fopen("output.txt", "w");

 int L_poroso, i,buffer1,buffer2;
 float ratio_porosidad;
 printf("Introduzca longitud del poroso:");
 scanf("%i", &L_poroso);
 printf("Introduzca el ratio de porosidad (0/1):");
 scanf("%f", &ratio_porosidad);
 int poroso[L_poroso];
 int ceros=((ratio_porosidad*L_poroso)/(ratio_porosidad+1));
 int unos=L_poroso-((ratio_porosidad*L_poroso)/(ratio_porosidad+1));
 i=0;
 while (i<L_poroso){
   if (i<unos) {
     poroso[i]=1;
   }
   else {
     poroso[i]=0;
   }
   printf("%i ",poroso[i]);
 i++;
}
i=0;
 int ciclos=rand()%100+L_poroso*10;
 printf("\n%i\n",ciclos );
 int posicion1=rand()%(L_poroso-1);
 int posicion2=rand()%(L_poroso-1);
while (i<ciclos){
  //printf("%i -> %i\n",posicion1,posicion2);
   posicion1=rand()%(L_poroso-1);
   posicion2=rand()%(L_poroso-1);
  while (posicion1==posicion2){
    posicion2=rand() % (L_poroso-1);
  }

  buffer1=poroso[posicion1];
  buffer2=poroso[posicion2];
  poroso[posicion1]=buffer2;
  poroso[posicion2]=buffer1;
  i++;
}
i=0;
while (i<L_poroso){
  fprintf(output_txt,"%i\n",poroso[i]);
i++;
}
// fprintf(output_txt,"\n");
// fprintf(output_txt,"end");

char * configGnuplot[] = {"","",
                                "set yrange [0:1]",
                                "unset key",
                                "unset xtics",
                                "unset ytics",
                                "plot \"output.txt\" with fillsteps fs solid 1 noborder"
                               };
char charbuff[100],charbuff2[100];
sprintf(charbuff, "set title \"Representación del poroso con: L = %i // r=%.2f\"",L_poroso,ratio_porosidad);
configGnuplot[0]=charbuff;
sprintf(charbuff2,"set xrange [0:%i]",L_poroso);
configGnuplot[1]=charbuff2;

    /*Se crea una archivo de tipo poen, es una tebería IPC que se usa, para
     * ejecutar gnuplot y enviarle el archivo a graficar*/
    FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
    // Executing gnuplot commands one by one
    for (i=0;i<7;i++){
  fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
 }

 fclose(output_txt);
 pclose(ventanaGnuplot);
}
