Ejercicios
=========================================================

A continuación se describe el desarrollo de cada uno de los ejercicios propuestos en la PEC.

.. Attention:: A lo largo de todo el proceso de simulación así como en su documentación, se utilizará una metodología diferente a la planteada en el enunciado de la prueba. Se considerarán activos los núcleos que figuren como 0 e inactivos aquellos que figuren como 1. Esto se debe a una simplificación en el código debido a la estructura interna del comando `calloc`, encargado de declarar e inicializar los arrays dinámicos que se utilizarán para el proceso de simulación. Este comando, define un array dinámico de N posiciones e inicializa cada una de las posiciones del mismo a cero, evitando así tener que crear un bucle de inicialización para cada una de las posiciones de este (Lo mismo sucede con los arrays bidimensionales). Dada esta posibilidad de simplificación y el hecho de que, como tal, esta modificación no alterará los resultados finales dado que solo se aplicará a etapas intermedias del desarrollo, se toma la decisión de seguir adelante con la misma.

Para la ejecución del código de los diversos ejercicios, será suficiente con ejecutar el archivo `main.exe` de la carpeta `src/buid`.

El programa está planteado de forma que se puedan ejecutar cada una de las simulaciones planteadas de forma rápida y sencilla, por lo que será suficiente con presionar `Enter` en la toma de datos para utilizar los parámetros por defecto exceptuando el bucle inicial en el que habrá que seleccionar por consola el ejercicio que querremos simular.

.. Attention:: La ejecución de este programa está pensada para poder simular los casos planteados en el enunciado de la PEC así como multitud de casos similares que se rijan por los mismos parámetros que estos. No obstante, dicha ejecución solo está testeada con los casos planteados originalmente, por lo que no se podrá garantizar el correcto funcionamiento ante cualquier casuística planteada.

Si se deseara compilar de nuevo el código completo, se deberá utilizar el siguiente comando desde el directorio `src` donde podremos encontrar el código fuente.:

      >>> gcc -std=c99 -o build/main main.c PEC2Lib.c PEC2Lib.h ejercicio1.c ejercicio1.h ejercicio2.c ejercicio2.h ejercicio3.c ejercicio3.h ejercicio4.c ejercicio4.h


.. toctree::
   :maxdepth: 4
   :caption: Ejercicios:

   ejercicio1.rst
      
   ejercicio2.rst

   ejercicio3.rst

   ejercicio4.rst