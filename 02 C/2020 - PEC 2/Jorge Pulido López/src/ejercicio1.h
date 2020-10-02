//
// Created by Jorge Pulido on 09/05/2020.
//

#ifndef INC_2020___PEC_2_PEC2LIB_H
#define INC_2020___PEC_2_PEC2LIB_H

#endif

/**
 *      Parameters
 *      ----------
 * 
 *      outPath: string
 *              Directorio a utilizar para la salida de los archivos de datos de las diversas simulaciones. Comprobado y/o creado mediante :c:func:`checkAndCreateDirectory`
 * 
 * Durante la ejecución del código del ejercicio 1, se procederá a la simulación de la desintegración de un conjunto de N_0 núcleos activos de Cobalto 60. Mediante esta simulación, podremos comprobar que la probabilidad de desintegración de estos núcleos viene definida por una distribución de Poisson. 
 * 
 * En el código de este ejercicio se facilita la opción de realizar una simulación parametrizada mediante:
 * 
 * 
 *      Parameters
 *      ----------
 *      maxScenarios: int
 *           Número de escenarios distintos que se analizarán.
 *      
 *      N_0: int[]
 *           Cantidad inicial de núcleos a desintegrar. (Por caso estudiado)
 *      
 *      p_disintegration: float[]
 *           Probabilidad de desintegración de cada núcleo en cada paso del proceso. (Por caso estudiado)
 *      
 *      M: int[]
 *           Ciclos de repetición de la simulación para la ponderación de los resultados. (Por caso estudiado)
 * 
 * 
 * En este caso, nos ceñiremos a la simulación de los casos planteados en la PEC, que constan de los siguientes datos:
 * 
 *      Examples
 *      --------
 * 
 *      >>> N_0 = 20, p_disintegration = 0.5, M = 1.000.000
 *      >>> N_0 = 50, p_disintegration = 0.2, M = 1.000.000
 *      >>> N_0 = 100, p_disintegration = 0.1, M = 1.000.000
 *      >>> N_0 = 1000, p_disintegration = 0.01, M = 1.000.000
 * 
 * .. Note:: Hemos de tener en cuenta que el código de este ejercicio está orientado a la comparación de distintas casuísticas equivalentes así como la curva teórica de las mismas. Es por esto que es necesario introducir unos valores acordes a esta curva, es decir, el producto N_0*p de todos los casos a analizar deberá ser igual, de lo contrario, no sería posible representar la curva teórica.
 * 
 * Para cada una de las casuísticas planteadas, se realizará el siguiente proceso:
 *
 * Mediante la randomización computacional, se tomará un array unidimensional de tamaño ``N_0`` con valores inicializados a 0, y se recorrerán sus posiciones una a una, generándose un número aleatorio ``rnd`` entre 0 y 1, y se comparará con el valor ``p_disintegration`` que marcará el umbral de desintegración, de modo que si ``rnd > p_disintegration``, el núcleo pasará de estado 0 a estado 1:
 *      
 * Si analizamos por ejemplo una única simulación para N_0 = 10 y p = 0.4, esperaremos obtener resultados similares a los siguientes.
 * 
 *      >>> 0000000000 -> 0010010011
 *      >>> 0000000000 -> 1000101010
 *      >>> 0000000000 -> 1111000000
 *      >>> 0000000000 -> 1001001001
 * 
 * .. Note:: Para facilitar este proceso, utilizaremos la función :c:func:`simularDesintegracion`
 * 
 * Pero dado que la simulación de una única etapa tiene una gran carga de aleatoriedad, podrían darse casos en los que, el número de desintegraciones no concuerde con la probabilidad de desintegración de dicha casuística:
 * 
 *      >>> 0000000000 -> 1010010010
 *      >>> 0000000000 -> 0010101001
 *      >>> 0000000000 -> 1110110100
 *      >>> 0000000000 -> 1001010100
 * 
 * 
 * Es por esto que, para poder observar el comportamiento de dichas desintegraciones, necesitaremos analizar un mayor número de sucesos. Para ello, utilizaremos la función :c:func:`simulateFirstStepDisintegrationsMTimes`, la cual automatizará la simulación de M desintegraciones de conjuntos, inicialmente iguales, de N_0 núcleos con probabilidades de desintegración iguales, guardando dichos resultados en un array bidimensional de `i` filas correspondientes al número de escenarios a analizar (por defecto 4), y `j` columnas, correspondiendo al número inicial de núcleos, y que contendrá un valor entero en cada una de las posiciones que nos indicará el número casos en los que se han producido `j` desintegraciones durante la simulación del escenario `i`. Produciendo un histograma absoluto del tipo:
 * 
 *      >>> 0003010000
 * 
 * Que se correspondría con los ejemplos de simulación del bloque anterior.
 * 
 * Para poder asemejar dicho histograma a una distribución de Poisson, necesitaremos transformar estos datos a probabilidades entre 0 y 1, para así poder compararlos con la curva teórica:
 * 
 * .. math::
 *      :label: Distribución de probabilidad de Poisson.
 * 
 *      f(x)=\frac{\lambda^{x}}{x !} e^{-\lambda}
 * 
 * Para ello, utilizaremos :c:func:`arrayIterationalDivider` que nos convertirá los datos acumulados en datos ponderados con respecto al número de simulaciones M.
 * 
 * Una vez obtenido el array del histograma ponderado, utilizaremos GNUPlot para graficar los datos obtenidos en los escenarios analizados así como la curva teórica que definirá el comportamiento de los mismos.
 * 
 * Como podemos comprobar en la siguiente figura, los datos obtenidos en la simulación se corresponden con la curva teórica en gran medida, a excepción del primer caso, dado que al tratarse de un valor de M tan bajo los resultados se vuelven poco fiables debido a la alta carga de aleatoriedad mencionada previamente, pero a medida que elevamos el número de simulaciones, la precisión así como la concordancia de dichos datos aumentan.
 * 
 * .. figure:: ../_static/ejercicio1_resultados.png
 *      :align: center
 * 
 *      Comprobación del comportamiento de los núcleos de Cobalto 60 regido por una distribución de Poisson con lambda = 10. */
int ejercicio1(const char outPath[]);