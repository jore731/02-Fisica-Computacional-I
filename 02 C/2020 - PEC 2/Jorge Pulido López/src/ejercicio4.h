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
 * Durante la ejecución del código del ejercicio 4, se procederá a la simulación de la desintegración completa de M conjuntos de N_0 núcleos activos de Cobalto 60. Mediante esta simulación, podremos comprobar la `markovianidad` de este suceso, es decir, que el proceso de desintegración de núcleos radioactivos no tiene memoria. Para ello, hemos de justificar que la probabilidad de desintegración de un núcleo radioactivo no depende de estados previos, sino del estado presente. Para ello, calcularemos la probabilidad que tiene un núcleo no desintegrado en el estado `j`, de no haberse desintegrado tras un tiempo :math:`\Delta t` , es decir, en un estado :math:`j+\Delta t`, para todos los estados del proceso de desintegración. Para ello, aplicaremos la siguiente ecuación:
 * 
 * .. math::
 *      :label: Probabilidad de no-desintegración de un núcleo activo tras l etapas de desintegración.
 *      
 *      \operatorname{prob}(X>t+\Delta t | X>t)=\left\langle\frac{N(j+l)}{N(j)}\right\rangle_{N}
 * 
 * En este caso, al tratarse de una simulación, utilizaremos, como venimos haciendo en los ejercicios anteriores, un valor :math:`d t` constante para cada etapa de desintegración, de forma que :math:`t=j\times d t`, y por lo tanto, utilizaremos el paso `l`, almacenado en el array unidimensional `plottingStep[]` para calcular la diferencia de tiempo entre el estado en el que el núcleo no está desintegrado :math:`\Delta t=l \times d t`, y el estado para el que queremos calcular que la desintegración siga sin producirse.
 * 
 * Cabe destacar que este suceso será el que rija el comportamiento individual de cada uno de los núcleos activos para cada una de las etapas de la desintegración, a diferencia de los :c:func:`ejercicio1`, :c:func:`ejercicio2`, y :c:func:`ejercicio3`, en los que se analizaba el comportamiento como conjunto de núcleos activos.
 * 
 * Una vez calculados los resultados con ayuda de la :c:func:`checkMarkov`, comprobaremos que su comportamiento se rige por la siguiente ecuación:
 * 
 * 
 * .. math::
 *      :label: Recta de probabilidad de no-desintegración de un núcleo activo tras `l` etapas de desintegración.
 *      
 *      e^{-\lambda_{0} \Delta t}
 * 
 * 
 * 
 * En el código de este ejercicio se facilita la opción de realizar una simulación parametrizada mediante:
 * 
 * 
 *      Parameters
 *      ----------
 *      maxScenarios: int
 *           Número de escenarios distintos que se analizarán.
 * 
 *      maxTime: int
 *           De cara a la representación gráfica de los resultados, se da la posibilidad de ampliar o reducir el límite de tiempo a representar en dichas gráficas, pudiéndose así focalizar en las zonas deseadas de la misma. Una vez introducido este parámetro, las entradas del archivo de datos generado se verán alteradas así como su correspondiente representación. (Aplica a todos los casos en conjunto)
 *      
 *      N_0: int[]
 *           Cantidad inicial de núcleos a desintegrar. (Por caso estudiado)
 *      
 *      p_disintegration: float[]
 *           Probabilidad de desintegración de cada núcleo en cada paso del proceso. (Por caso estudiado)
 * 
 *      plottingStep: int[]
 *           Paso a utilizar a la hora de exportar los datos. Cuando `plottingStep > 1`, se representarán exclusivamente aquellos pasos de la desintegración múltiplos de `plottingStep`. En este caso, `plottingStep` también definirá :math:`\Delta t`, por lo que la simulación y los resultados dependerán de este parámetro. A pesar de ello, las gráficas producidas solo se deberán ver afectadas por la cantidad de datos representados.
 * 
 *           >>> plottingStep = 3 ->  dataSimulated   = 1, 2, 3, 4, 5, 6, 7, 8, 9
 *           >>>                      dataRepresented = 3, 6, 9
 *      
 *      lambda_0: float[]
 *           Parámetro característico del los núcleos a simular (Cobalto 60 : 0.13), que describe el comportamiento de dichos núcleos en función del tiempo. (Por caso estudiado)
 * 
 *      M: int[]
 *           Ciclos de repetición de la simulación para la ponderación de los resultados. (Por caso estudiado)
 * 
 * En este caso, nos ceñiremos a la simulación de los casos planteados en la PEC, que constan de los siguientes datos:
 * 
 *      Examples
 *      --------
 * 
 *      >>> N_0 = 10000, p_disintegration = 0.001, lambda_0 = 0.13, l=130, M = 10
 *      >>> N_0 = 10000, p_disintegration = 0.001, lambda_0 = 0.13, l=130,, M = 100
 *      >>> N_0 = 10000, p_disintegration = 0.001, lambda_0 = 0.13, l=130,, M = 1000
 * 
 * 
 * Para cada una de las casuísticas planteadas, se realizará el siguiente proceso:
 *
 * Basándonos en la metodología del :c:func:`ejercicio3`, y con ayuda de la función :c:func:`checkMarkov` realizaremos la simulación de desintegración completa del conjunto M veces, almacenando los datos en un array bidimensional temporal, para posteriormente ponderar el número de núcleos activos para cada una de las etapas del periodo de desintegración, generando un array unidimensional ponderado que utilizaremos para aplicar la ecuación :eq:`Probabilidad de no-desintegración de un núcleo activo tras l etapas de desintegración.`, generando así el array unidimensional  `markov[]` que contendrá la probabilidad de no-desintegración para cada una de las etapas del proceso. También producirá un array `t[]` que contendrá la base de tiempos para cada una de las etapas.
 * 
 * Así mismo, esta función devolverá los tiempos de desintegración y semidesintegración del conjunto, esta vez ponderados, que podremos comparar posteriormente con los resultados teóricos del Cobalto60.
 * 
 * Una vez obtenidos estos resultados, utilizaremos GNUPlot para graficar los datos obtenidos en los escenarios analizados así como la recta teórica que definirá el comportamiento de los mismos. En este caso, dada la similitud de los resultados de los casos a analizar en esta PEC, utilizaremos una gráfica para cada una de las simulaciones para facilitar su visualización. Por lo que serán los parámetros característicos de cada una de los datos simulados los que definan el comportamiento de la recta teórica, pudiendo obtener varias rectas teóricas diferentes en cada uno de los escenarios.
 * 
 * Como podemos comprobar en las siguientes figuras, los datos obtenidos en la simulación se corresponden con la recta teórica y su precisión mejora a medida que incrementa el número de simulaciones (`M`), como ya mencionamos en el :c:func:`ejercicio2`. Podemos por lo tanto concluir que el suceso de desintegración de un núcleo es markoviano, puesto que su probabilidad de desintegración en un periodo de tiempo :math:`\Delta t` dependerá exclusivamente de su estado actual y de dicho :math:`\Delta t`, sin importar el estado anterior.
 * 
 * .. figure:: ../_static/ejercicio4_resultados_1.png
 *      :align: center
 * 
 *      Probabilidad de no-desintegración de un núcleo activo de Cobalto60 tras un periodo :math:`\Delta t \approx 1`  (M = 10).
 *      
 * .. figure:: ../_static/ejercicio4_resultados_2.png
 *      :align: center
 * 
 *      Probabilidad de no-desintegración de un núcleo activo de Cobalto60 tras un periodo :math:`\Delta t \approx 1`  (M = 100).
 *      
 * .. figure:: ../_static/ejercicio4_resultados_3.png
 *      :align: center
 * 
 *      Probabilidad de no-desintegración de un núcleo activo de Cobalto60 tras un periodo :math:`\Delta t \approx 1` (M = 1000).
 * 
 * .. Note:: Como podemos comprobar, la recta teórica se cumple para todo `t` pero es a causa de la aleatoriedad en sucesos avanzados en `t` y la falta de muestreo de los mismos lo que hace que, para M=10 y M=100, los resultados simulados, diverjan de lo esperado.*/
int ejercicio4(const char outPath[]);