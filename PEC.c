#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main() {
  srand(time(NULL));

 int L_poroso, ratio_porosidad, i,buffer1,buffer2;
 printf("Introduzca longitud del poroso:");
 scanf("%i", &L_poroso);
 printf("Introduzca el ratio de porosidad (0/1):");
 scanf("%i", &ratio_porosidad);
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
 int ciclos=rand()%100+100;
 printf("%i\n",ciclos );
 int posicion1=rand()%(L_poroso-1);
 int posicion2=rand()%(L_poroso-1);
while (i<ciclos){
  printf("%i -> %i\n",posicion1,posicion2);
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
  printf("%i ",poroso[i]);
i++;
}
}
