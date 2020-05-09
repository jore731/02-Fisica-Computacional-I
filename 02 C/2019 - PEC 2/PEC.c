#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

void inicializar_i_ceros_1d (int *array,int L_filas){
  int i=0;
  while (i<L_filas){
    array[i]=0;
    i++;
  }
}

void inicializar_f_ceros_1d (float *array,int L_filas){
  int i=0;
  while (i<L_filas){
    array[i]=0;
    i++;
  }
}

void inicializar_i_unos_1d (int *array,int L_filas){
  int i=0;
  while (i<L_filas){
    array[i]=1;
    i++;
  }
}

void inicializar_f_unos_1d (float *array,int L_filas){
  int i=0;
  while (i<L_filas){
    array[i]=1;
    i++;
  }
}

//función que crea el poroso en el array especificado con el tamaño deseado y la cantidad de unos especificada. (primero unos, después ceros)
void crear_poroso (int * array, int L_array, int n_unos) {
  int i=0;
  while (i<L_array){
    if (i<n_unos) {
      array[i]=1;
    }
    else {
      array[i]=0;
    }
    // printf("%i ",array[i]);
    i++;
  }
}

//función que reorganiza de manera aleatoria los valores de un array
void randomizar_array (int * array,int L_array){
  int ciclos=rand()%100+L_array*10;
   // printf("\n%i\n",ciclos );
   int buffer1, buffer2, i=0;
   int posicion1=rand()%(L_array-1);
   int posicion2=rand()%(L_array-1);
  while (i<ciclos){
    //printf("%i -> %i\n",posicion1,posicion2);
     posicion1=rand()%(L_array-1);
     posicion2=rand()%(L_array-1);
    while (posicion1==posicion2){
      posicion2=rand() % (L_array-1);
    }

    buffer1=array[posicion1];
    buffer2=array[posicion2];
    array[posicion1]=buffer2;
    array[posicion2]=buffer1;
    i++;
  }
}

void print_array_1d (float *array, int columnas, int espacio, int printfloat){
  int i=0;
  while (i<columnas){
    if (espacio==0) {
      if (printfloat==0) {
        printf("%i",array[i]);
      }else {printf("%.4f",array[i]);}
    }else {
      if (printfloat==0) {printf("%i |",array[i]);}
      else{printf("%.4f |",array[i]);}
    }
    i++;
  }
}

void print_array_2d (int *array, int columnas, int filas,int espacio){
  int i=0, j=0;
  while (i<filas){
    while (j<columnas){
      if (espacio==1) {
        printf("%i |",array[i*columnas+j]);
      }
    else{printf("%i",array[i*columnas+j]);}
    j++;
    }
  printf("\n");
  i++;
  j=0;
  }
}


void crear_matriz_porosos (int *array,int L_filas, int filas, int unos){
  int i=0;
  while (i<filas){
    crear_poroso (&array[i*L_filas],L_filas,unos);
    // print_array_1d(&array[i],L_filas);
    //  printf("\n");
    randomizar_array (&array[i*L_filas],L_filas);
    // print_array_1d(&array[i*L_filas],L_filas);
    // printf("\n");
    i++;
  }
}

void calcular_huecos (int *array, int * huecos, int L_filas){
int i=0,h_act=0;
  while (i<L_filas){
    if (array[i]==0) {
      h_act++;
    }
    else {
      if (h_act!=0) {
          huecos[h_act]++;
          // printf("%i, %i\n",i, &array[i] );
      }
      h_act=0;
    }
    // printf("%i, %i, %i\n",i,h_act,array[i]);
    i++;
  }
  if (h_act!=0) {
    huecos[h_act]++;
  }
}


void crear_matriz_huecos (int * array,int * huecos,int filas,int columnas){
  int i=0;
  while (i<filas){
    inicializar_i_ceros_1d (&huecos[i*columnas/2],columnas/2);
    calcular_huecos (&array[i*columnas],&huecos[i*columnas/2],columnas);
    i++;
  }
}


void crear_histograma (int * array,float * histograma,int filas, int columnas){
  int i=0, j=0;
  inicializar_f_ceros_1d (histograma,columnas);
  while (i<filas){
    while (j<columnas) {
      histograma[j]=histograma[j]+array[i*columnas+j];
      j++;
    }
    j=0;
    i++;
  }

}

void dividir_array (float * array,int columnas, int dividendo){
  int j=0;
  while (j<columnas) {
    array[j]=array[j]/dividendo;
    j++;
  }
}

void escala_histograma (float *array,int columnas,float *max_x, float *max_y){
  int i=0;
  *max_x=0;
  *max_y=0;
  while (i<columnas/2){
    if (array[i]>*max_y) {
      *max_y=array[i];
    }
    if (array[i]>0) {
      *max_x=i;
    }
  i++;
  }
}

void print_array_f_1d_to_file (char * nombre,float * array,int columnas, FILE * output_txt){
  int i=0;
  while (i<columnas){
    if (i==0) {
      fprintf(output_txt,"%f ",array[i]);
    }
    else {
      fprintf(output_txt,"| %f ",array[i]);
    }
    i++;
  }
}

void print_array_f_2d_to_file (char * nombre,float * array,int columnas, int filas){
  int j=0;
  FILE * output_txt = fopen(nombre, "w");
  while (j<filas) {
    print_array_f_1d_to_file(nombre,&array[j*columnas],columnas,output_txt);
    if (j!=filas-1){
      fprintf(output_txt,"\n");
    }
    j++;
  }
  fclose(output_txt);
}

void print_array_i_1d_to_file (char * nombre,int * array,int columnas, FILE * output_txt){
  int i=0;
  while (i<columnas){
    if (i==0) {
      fprintf(output_txt,"%i ",array[i]);
    }
    else {
      fprintf(output_txt,"| %i ",array[i]);
    }
    i++;
  }
}

void print_array_i_2d_to_file (char * nombre,int * array,int columnas, int filas){
  int j=0;
  FILE * output_txt = fopen(nombre, "w");
  while (j<filas) {
    print_array_i_1d_to_file(nombre,&array[j*columnas],columnas,output_txt);
    if (j!=filas-1){
      fprintf(output_txt,"\n");
    }
    j++;
  }
  fclose(output_txt);
}


int main() {
    //inicialización del seed aleatorio con una variable de tiempo, de forma que la iteración no sea siempre la misma.
    srand(time(NULL));
    int N_0,M;
    float p_desintegracion,dt;

    //toma de datos en la consola
    printf("Insert N_0: ");
    scanf("%i", &N_0);
    printf("Insert p: ");
    scanf("%f", &p_desintegracion);
    printf("Insert dt: ");
    scanf("%f", &dt);
    printf("Insert M: ");
    scanf("%i", &M);

    float histograma[N_0];
    float max_histograma_y,max_histograma_x;
    int nucleosActivos[N_0];
    inicializar_i_unos_1d(nucleosActivos,N_0);
    print_array_1d(nucleosActivos,N_0,0,0)
  //creación del array sin aleatorizar

  crear_matriz_porosos (porosos,L_poroso,n_porosos,unos);
  crear_matriz_huecos (porosos,huecos,n_porosos,L_poroso);

  printf("\n");
  printf("\n");
  printf("Matriz de porosidad con L=%i, r=%.2f y N=%i\n",L_poroso,ratio_porosidad,n_porosos);
  printf("----------------------------------------------------------------------\n");
  print_array_2d (porosos,L_poroso,n_porosos,0);
  printf("----------------------------------------------------------------------\n");
  printf("\n");
  printf("\n");
  printf("Matriz de huecos de cada ejemplar de poroso generado aleatoriamente.\n");
  printf("----------------------------------------------------------------------\n");
  //print_array_2d (huecos,L_poroso/2,n_porosos,1);
  printf("\n");
  printf("\n");
  printf("Histograma:\n");
  printf("Acumulado\n");
  printf("----------------------------------------------------------------------\n");
  crear_histograma(huecos,histograma,n_porosos,L_poroso/2);
  //print_array_1d (histograma,L_poroso/2,1,1);
  printf("\n");
  printf("Promedio\n");
  printf("----------------------------------------------------------------------\n");
  dividir_array (histograma,L_poroso/2,n_porosos);
  //print_array_1d (histograma,L_poroso/2,1,1);
  printf("\n");
  printf("\n");
  printf("Histograma normalizado (en porcentaje):\n");
  printf("----------------------------------------------------------------------\n");
  dividir_array (histograma,L_poroso/2,L_poroso);
  //print_array_1d (histograma,L_poroso/2,1,1);

  escala_histograma (histograma,L_poroso,&max_histograma_x,&max_histograma_y);

  print_array_f_2d_to_file ("histograma.txt",histograma,L_poroso/2,1);
  print_array_i_2d_to_file ("output.txt",porosos,L_poroso,n_porosos);

  char * config_plot_histograma[] = {"","","","set key",""};
  char titulo[100],ejes_x[100],ejes_y[100],ploteo[1000];
  sprintf(titulo, "set title \"Histograma de porosidad (L = %i, r=%.2f, N=%i)\"",L_poroso,ratio_porosidad,n_porosos);
  sprintf(ejes_x,"set xrange [0:%f]",1.2*max_histograma_x);
  sprintf(ejes_y,"set yrange [0:%f]",1.2*max_histograma_y);
  sprintf(ploteo,"plot \"histograma.txt\" title \"Experimental\" with histogram linecolor rgb \"red\" fs solid 1 noborder,(%f**x)/((1+%f)**(2+x)) title \"Teórico\" linecolor rgb \"black\" lw 1",ratio_porosidad,ratio_porosidad);

  config_plot_histograma[0]=titulo;
  config_plot_histograma[1]=ejes_x;
  config_plot_histograma[2]=ejes_y;
  config_plot_histograma[4]=ploteo;
      /*Se crea una archivo de tipo poen, es una tebería IPC que se usa, para
       * ejecutar gnuplot y enviarle el archivo a graficar*/
      FILE * gnuplot_histograma = popen ("gnuplot -persist", "w");
      // Executing gnuplot commands one by one
int i=0;
      for (i=0;i<5;i++){
    fprintf(gnuplot_histograma, "%s \n", config_plot_histograma[i]);
   }

   pclose(gnuplot_histograma);
}