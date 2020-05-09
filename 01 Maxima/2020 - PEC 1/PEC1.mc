/** @brief Física Computacional I: Prueba de Evauación Continua 1
 @author Jorge Pulido López
 @email jpulido147@alumno.uned.es
 @dni 05950206Z
 @date 10 Abril 2020
**/
/***********************************************************************************/
/************************************EJERCICIO 1************************************/
/***********************************************************************************/
/**
 @brief EJERCICIO 1: Interpolación lineal, lagrangiana y por medio de splines 
        de los datos importados de un fichero.
        Se puede utilizar la función multi_interpolation() si se desea una validación de
        los datos de entrada así como una mayor tolerancia con los mismos 
        (omisiones, extensiones, rutas...)

 @param dataFilePath   Ruta al archivo de datos a utilizar ("*.out").

 @param outputPlotPath Ruta al archivo de datos a generar (".lisp").

 @param outputDataPath Ruta al archivo gráfico a generar (".pdf").

 @return Una vez el proceso ha concluido y los archivos han sido generados 
         correctamente, imprime las rutas de los archivos generados y devuelve
         "done".
**/
multi_interpolation_processed_input(dataFilePath, 
                                    outputPlotPath, 
                                    outputDataPath):= block(
/****************************CREACIÓN DE VARIABLES LOCALES****************************/
    [data, mData, dataIndep, dataDep, domIndep, domDep, data_linear, 
    data_lagrange, data_splines]
    ,
/************************CARGA DE LIBRERÍA PARA INTERPOLACIONES***********************/
    load(interpol)
    ,
/**********************LECTURA DE DATOS COMO LISTA Y COMO MATRIZ**********************/
/****Esto nos permite utilizar el tipo de dato más conveniente en cada contemplados***/
    data:read_nested_list(dataFilePath),
    mData:apply(matrix,data)
    ,
/*****************************CÁLCULO DE INTERPOLACIONES******************************/
    data_linear:linearinterpol(data),
    data_lagrange:lagrange(data),
    data_splines:cspline(data)
    ,
/*****************************CALCULO DE DOMINIO DE X e Y*****************************/
/**********************Requiere separación de los datos por ejes**********************/
    dataIndep:transpose(mData)[1],
    dataDep:transpose(mData)[2]
    ,
    domIndep:[x,apply(min,dataIndep), apply(max,dataIndep)],
    domDep:[y,apply(min,dataDep), apply(max,dataDep)]
    ,

/*******************HITO 3: GUARDADO DE INTERPOLACIONES EN .LISP**********************/
    save(outputDataPath,data_linear,data_lagrange,data_splines)
    ,
/************************HITO 2: GUARDADO DE GRÁFICA EN .PDF*************************/
    plot2d ([[discrete,data],data_linear,data_lagrange, data_splines],  
            domIndep,domDep,
            [style,points,lines,lines,lines],
            [pdf_file,outputPlotPath], 
            [legend, "Input Data", "Linear Interpolation", 
                     "Lagrange Interpolation","Splines Interpolation"])
    ,
/***********************HITO 1: GRAFICADO DE DATOS EN PANTALLA***********************/
    plot2d ([[discrete,data],data_linear,data_lagrange, data_splines],  
            domIndep,domDep,
            [style,points,lines,lines,lines], 
            [legend, "Input Data", "Linear Interpolation", 
                     "Lagrange Interpolation","Splines Interpolation"])
    ,
/****************************MENSAJE DE EJECUCIÓN CORRECTA***************************/
    print(sconcat(outputPlotPath," generated")),
    print(sconcat(outputDataPath," generated")),
    return ("done")
);

/**
 @brief EJERCICIO 1 (Con filtrado de datos):  Filtrado y validación de datos de entrada 
    	antes de pasarlos a la función principal.

 @param rawDataFilePath Nombre/Ruta del archivo a importar.
                        - Ruta completa al archivo
                        - Nombre del archivo de datos
                        - Funciona con y sin extensión

 @param kargs   - Parámetros opcionales para la ejecución de la función.
                - Son argumentos posicionales, que pueden omitirse siempre y cuando se 
                  omitan todos los parametros posteriores.
                - Para omitir parámetros intermedios, le daremos el valor "None".
                  (ejemplo: multi_interpolation("data-1", None, "data-1_processed.lisp")
                   rawOutputPlotFileName y forceOutputPath son omitidos)

    @param rawOutputPlotFileName - Nombre del archivo gráfico generado (.pdf).
                                 - Funciona con y sin extensión.
                                 - Comprueba que la extensión sea correcta.

    @param rawOutputDataFileName - Nombre/Ruta del archivo de datos generado (.lisp).
                                 - Funciona con y sin extensión.
                                 - Comprueba que la extensión sea correcta.

    @param forceOutputPath       - Ruta de destino de los archivos generados.
                                 - Formato Linux (Acepta "/" y "\\", pero no "\").

 @return Valida los datos de entrada y, si estos son válidos, ejecuta la función principal 
        con ellos. Los siguientes errores están contemplados:
            - "{DataFilePath} not found"
            - "Invalid output plot-file name"
            - "Invalid output data-file name"
**/
multi_interpolation(rawDataFilePath,[kargs]) := block(
/****************************CREACIÓN DE VARIABLES LOCALES****************************/
    [rawOutputPlotFileName, rawOutputDataFileName, 
    forceOutputPath,outputPath, rawDataFileName,rawDataFileDirectory, 
    workingDirectory, dataFileName, dataFileExtension, dataFilePath,
    outputPlotFileName, outputPlotFileExtension, outputPlotPath, 
    outputDataFileName, outputDataFileExtension, outputDataPath]
    ,
/**********************CARGA DE LIBRERÍA PARA EVALUACIÓN DE RUTAS*********************/
    load(operatingsystem),
    load(stringproc)
    ,
/********************ASIGNACIÓN DE PARAMETROS OPCIONALES SI PROCEDE*******************/
    if length(kargs)>0 then rawOutputPlotFileName : kargs[1],
    if length(kargs)>1 then rawOutputDataFileName : kargs[2],
    if length(kargs)>2 then forceOutputPath : kargs[3]
    ,

/*****************************ARCHIVO DE ENTRADA DE DATOS****************************/
/******************separación de ruta de archivo de entrada de datos*****************/
    rawDataFileName: pathname_name(rawDataFilePath),
    rawDataFileDirectory: pathname_directory(rawDataFilePath)
    ,
/***************************validación de working directory**************************/
    if rawDataFileDirectory="" then \
        workingDirectory: getcurrentdirectory()
    else workingDirectory: rawDataFileDirectory
    ,
/***************Validación de extensión de archivo de entradad de datos**************/
    if (ssearch(".",rawDataFileName)=false) then (
        dataFileName: rawDataFileName,
        dataFileExtension: "out")
    else [dataFileName,dataFileExtension]:
            split(rawDataFileName, ".")
    ,
/*******************Creación de ruta de archivo de entradad de datos******************/
    dataFilePath : sconcat(workingDirectory,"/",dataFileName,".",dataFileExtension)
    ,
/*************************RUTA DE SALIDA DE ARCHIVOS GENERADOS************************/
/**********************Verificar si existe ruta de salida forzada********************/
    if not stringp(forceOutputPath) then 
        outputPath: workingDirectory
    else outputPath: forceOutputPath
    ,
/*****************Verificar si existe nombre de plot de salida forzado***************/
    if not stringp(rawOutputPlotFileName) then (
        outputPlotFileName: dataFileName,
        outputPlotFileExtension: "pdf")
    else (
        if (ssearch(".",rawOutputPlotFileName)=false) then (
            outputPlotFileName: rawOutputPlotFileName,
            outputPlotFileExtension: "pdf")
        else (
            [outputPlotFileName,outputPlotFileExtension]: 
                split(rawOutputPlotFileName, "."))
    )
    ,
/*******************Verificar extensión de nombre de plot de salida*****************/
    if outputPlotFileExtension="pdf" then 
        outputPlotPath: sconcat(outputPath,"/", 
                                outputPlotFileName,".",
                                outputPlotFileExtension)
    else
        error(sconcat("Invalid output plot-file name"))
    ,
/*****************Verificar si existe nombre de datos de salida forzado***************/
    if not stringp(rawOutputDataFileName) then (
        outputDataFileName: dataFileName,
        outputDataFileExtension: "lisp")
    else (
        if (ssearch(".",rawOutputDataFileName)=false) then (
            outputDataFileName: rawOutputDataFileName,
            outputDataFileExtension: "lisp")
        else (
            [outputDataFileName,outputDataFileExtension]: 
                split(rawOutputDataFileName, "."))
    )
    ,
/*******************Verificar extensión de nombre de datos de salida*****************/
    if outputDataFileExtension="lisp" then 
        outputDataPath: sconcat(outputPath,"/",
                                outputDataFileName,".",
                                outputDataFileExtension)
    else
        error(sconcat("Invalid output data-file name"))
    ,
    if not file_search(dataFilePath) then 
        error(sconcat(rawDataFilePath," not found"))
    ,
/********TRAS LA VERIFICACIÓN DE ENTRADA DE DATOS, EJECUTAR LA FUNCIÓN PRINCIPAL******/
    multi_interpolation_processed_input(dataFilePath,
                                        outputPlotPath,
                                        outputDataPath)
);


/***********************************************************************************/
/************************************EJERCICIO 2************************************/
/***********************************************************************************/
/**
 @brief EJERCICIO 2: Parametrización de modelo aproximado mediante ajuste de mínimos 
        cuadrados de los datos ubicados en el archivo al que apunta dataFilePath.
 
 @param rawDataInput Nombre/Ruta del archivo a importar o lista de datos a utilizar

 @param model Definición del modelo a utilizar en el ajuste. Lista compuesta de:
              - Modelo matemático (ej a*x^2 + b*x + c)
              - Variable independiente de este (ej x)
              - Lista de parámetros característicos que definen el modelo y que serán
                calculados numericamente. (ej [a,b,c])

                ej: [a*x^2 + b*x + c, x, [a,b,c]]

 @param kargs - Parámetros opcionales para la ejecución de la función.
              - Son argumentos posicionales, que pueden omitirse siempre y cuando se 
                omitan todos los parametros posteriores.
        
        @param plotCheck Si true, plotea los datos de entrada junto a la recta de
                         de ajuste calculada.
        
        @param roundTo  Dado que los valores son representados como float, se da la 
                        posibilidad de imprimir por pantalla una versión redondeada
                        de la ecuación característica sin afectar al funcionamiento
                        general de maxima a la hora de representar floats ni perder
                        datos en la ecuación retornada.
                         
 @return devuelve la expresión de la recta de ajuste calculada en formato 
         depVar = f(indepVar)
**/
adjust_to_model(rawDataInput, modelInput, [kargs]):= block(
    [data,mData,LSQuares,function,solutions,    /**aparentemente lsquare_estimates **/
    plotCheck, aux, dataDep,dataIndep,        /**arrastra la variable "solutions"**/
    domDep,domIndep,roundTo, oldFpprintprec, /**fuera de su bloque de ejecución **/
    model, indepVar,parameters]
    ,
/**CARGA DE LIBRERÍAS PARA AJUSTE DE MÍNIMOS CUADRADOS Y GERSTIÓN DE CADENAS DE TEXTO*/
    load(lsquares),
    load(stringproc)
    ,
/*******************************ASIGNACIÓN DE PARAMETROS******************************/   
    model: modelInput[1],
    indepVar: modelInput[2],
    parameters: modelInput[3]
    ,
/********************ASIGNACIÓN DE PARAMETROS OPCIONALES SI PROCEDE*******************/   
    if length(kargs)>0 then plotCheck : kargs[1]
    else plotCheck: false,
    if length(kargs)>1 then roundTo : kargs[2]
    else roundTo: false
    ,
/***********************LECTURA DE DATOS COMO LISTA Y COMO MATRIZ*********************/
/****Esto nos permite utilizar el tipo de dato más conveniente en cada contemplados***/
    if stringp(rawDataInput) then data: read_nested_list(rawDataInput)
    else data: rawDataInput,
    mData: apply(matrix, data)
    ,
/*************PREPARACIÓN DEL MODELO PREVIA AL AJUSTE DE MINIMOS CUADRADOS************/
/*****dado que el ajuste de mínimos requiere una funcion de formato f(x,y):= y=f(x)***/
    generic_expresion(func):= depVar = func,
    func(indepVar, depVar):= generic_expresion(model)
    ,
/*****CALCULO DE PARÁMTROS CARACTERÍSTICOS MEDIANTE EL AJUSTE DE MINIMOS CUADRADO*****/
    LSQuares: lsquares_estimates(mData,
                                [indepVar,depVar],
                                func(indepVar,depVar),
                                parameters),
/***********SUSTITUCIÓN DE PARÁMETROS CARACTERÍSTICOS EN LA FUNCIÓN INICIAL***********/
    function: float(subst(LSQuares[1], func(indepVar,depVar)))
,
/**********GRAFICACIÓN DE LOS DATOS CALCULADOS SI PROCEDE SEGUN CONFIGURACIÓN*********/
    if plotCheck then(
        aux: subst(function, depVar),
        dataIndep: transpose(mData)[1],
        dataDep: transpose(mData)[2],
        domIndep: [x, apply(min, dataIndep), apply(max, dataIndep)],
        domDep: [y, apply(min, dataDep), apply(max, dataDep)],
        plot2d([[discrete, data], aux], domIndep, domDep, 
                [style, points, lines], [legend,"Input data", "Aprox Model"])
    )
    ,
/************IMPRESIÓN DE DATOS REDONDEADOS SI PROCEDE SEGUN CONFIGURACIÓN************/
    if not roundTo=false then (
        oldFpprintprec: fpprintprec,
        fpprintprec: roundTo,
        print(sconcat("Rounded to ", roundTo," significant figures: ", function)),
        fpprintprec: oldFpprintprec),
/******RETORNA LA FUNCIÓN UNA VEZ LOS PARÁMETROS CARACTERÍSTICOS SON SUSTITUIDOS******/
    return (function)
);


/***********************************************************************************/
/*********************************EJERCICIOS 3 y 4**********************************/
/***********************************************************************************/
/**
 @brief EJERCICIOS 3 y 4: Comprovación gráfica de la teoría de diferenciación por 
 diferencias centradas de un modelo de datos. Se compara la derivación numérica de
 la expresión que define un muestreo de datos (puede ser calculada con la función
 adjust_to_model). 
 
 @param  rawDataInput Nombre/Ruta del archivo a importar o lista de datos a utilizar
 
 @param  function Expresión matemática que define los datos de "rawDataInput"

 @param kargs - Parámetros opcionales para la ejecución de la función.
              - Son argumentos posicionales, que pueden omitirse siempre y cuando se 
                omitan todos los parametros posteriores.
        
        @param  evalSDiff Si true, calcula y compara también la segundaa derivada.
                          Implementación del contenido del ejercicio 4.
                          
        
        @param  zoom Con el fin de poder valorar la "precisión" de las derivadas
                     (Primera y segunda) es importante considerar una escala similar
                     tanto al evaluar los datos de entrada como los de salida, por lo
                     que por defecto se utilizará una escala de valores que comprenda
                     todos los posibles valores de los datos de entrada y de salida,
                     pero en caso de querer mayor precisión en las gráficas de salida,
                     podremos utilizar zoom=true para considerar unicamente los valores
                     calculados para cada una de las gráficas.

        @param compareAnalitically Además de la comprobación gráfica, se da la 
                                   posibilidad de aproximar los resultados de los 
                                   cálculos a una expresión mediante la dereivación
                                   del modelo que define "function" para así comparar
                                   dicha aproximación con la derivada directa de la 
                                   misma. Para ello utilizaremos 
                                   compareAnalitically = model 
                                    **siendo model = 
                         
 @return  
**/
compare_first_diff(rawDataInput, function, indepVar,[kargs]):= block(
    [evalSDiff, compareAnalitically, data,mData, dataIndep, dataDep, functionDiff,
    functionSDiff, dataDiff, listDataDiff, dataSDiff, listDataSDiff, domIndep,
    domDiff, domSDiff, modelDiff,LSQuareAproxDiff,modelSDiff,LSQuareAproxSDiff, 
    zoom, numModelDiff, numModelSDiff]
    ,
    load(stringproc)
    ,
/********************ASIGNACIÓN DE PARAMETROS OPCIONALES SI PROCEDE*******************/   
    if length(kargs)>0 then evalSDiff : kargs[1]
    else evalSDiff: false,
    if length(kargs)>1 then zoom : kargs[2]
    else zoom: false,
    if length(kargs)>2 then compareAnalitically : kargs[3]
    else compareAnalitically: false,
/***********************LECTURA DE DATOS COMO LISTA Y COMO MATRIZ*********************/
/****Esto nos permite utilizar el tipo de dato más conveniente en cada contemplados***/
    if stringp(rawDataInput) then data: read_nested_list(rawDataInput)
    else data: rawDataInput,
    mData: apply(matrix, data)
    ,
/*************SEPARACIÓN DE DATOS EN VARIABLE DEPENDIENTE E INDEPENDIENTE************/
/*Esto nos permitirá acceder a los valores de estas de manera rápida con dep/indep(n)*/
    dataIndep: transpose(mData)[1],
    dataDep: transpose(mData)[2]
    ,
/***********CÁLCULO DE LA PRIMERA (Y SEGUNDA SI PROCEDE) DERIVADA DEL MODELO**********/
    functionDiff: diff(function,indepVar),
    if evalSDiff then functionSDiff: diff(functionDiff, indepVar)
    ,
/***************CÁLCULO DE DIFERENCIAS CENTRADAS DE LOS DATOS DE ENTRADA**************/
/***********************************Primera deriada***********************************/
    diffCent(n):= (dataDep[n + 1] - dataDep[n - 1]) / 
                  (dataIndep[n + 1] - dataIndep[n - 1]),
    dataDiff: makelist(diffCent(n), n, 2, length(dataIndep) - 1),
    listDataDiff: makelist([dataIndep[n+1],dataDiff[n]], n, 1, length(dataDiff))
    ,
/****************************Segunda deriada (si procede)*****************************/
    if evalSDiff then (
        sDiffCent(n):= (dataDep[n + 1] - 2*dataDep[n] +dataDep[n-1]) / 
                       (dataIndep[n + 1] - dataIndep[n])^2,
        dataSDiff: makelist(sDiffCent(n), n, 2, length(dataIndep) - 1),
        listDataSDiff: makelist([dataIndep[n+1],dataSDiff[n]], n, 1, length(dataSDiff)))
    ,
/***************CÁLCULO DE DOMINIOS PARA GRÁFICAS SEGÚN CONFIGURACIÓN****************/
    domIndep: [x, apply(min, dataIndep), apply(max, dataIndep)],
    if zoom then (
        domDiff: [y, apply(min, dataDiff), apply(max, dataDiff)],
        if evalSDiff then 
            domSDiff: [y, apply(min, dataSDiff), apply(max,dataSDiff)])
    else (
        domDiff: [y, apply(min, [apply(min,dataDep), apply(min,dataDiff)]), 
                    apply(max, [apply(max,dataDep), apply(max,dataDiff)])],
        if evalSDiff then 
            domSDiff: [y, apply(min, [apply(min,dataDep), apply(min,dataSDiff)]), 
                        apply(max, [apply(max,dataDep), apply(max,dataSDiff)])])
    ,
/*****************************GRAFICACIÓN DE RESULTADOS*******************************/
    plot2d([[discrete, listDataDiff], functionDiff], domIndep, domDiff, 
            [style, points, lines],[legend,"Cent. Diff. Data", "Function"]),
    if evalSDiff then 
        plot2d([[discrete, listDataSDiff], functionSDiff], domIndep, domSDiff, 
                [style, points, lines],[legend,"Cent. Diff. Data", "Function"])
    ,
/****************EVALUACIÓN NUMÉRICA DE LOS RESULTADOS (SI PROCEDE)*******************/
    if not compareAnalitically=false then (
        numModelDiff: diff(compareAnalitically[1],compareAnalitically[2]),
        modelDiff: [numModelDiff, compareAnalitically[2], compareAnalitically[3]],
        LSQuareAproxDiff: subst(adjust_to_model(listDataDiff, modelDiff),depVar),
        if evalSDiff then (
            numModelSDiff: diff(numModelDiff,compareAnalitically[2]),
            modelSDiff: [numModelSDiff, compareAnalitically[2], compareAnalitically[3]],
            LSQuareAproxSDiff: subst(adjust_to_model(listDataSDiff, modelSDiff),depVar))
        ,
/***********MOSTRADO DE RESULTADOS DE LA EVALUACIÓN NUMÉRICA (SI PROCEDE)**************/
        print("Function first derivative:"),
        print(functionDiff),
        print(
         "LSQuare aproximation of centered differences data(first derivative):"),
        print(LSQuareAproxDiff),
        if evalSDiff then (
            print("Function second derivative:"),
            print(functionSDiff),
            print(
             "LSQuare aproximation of centered differences data(second derivative):"),
            print(LSQuareAproxSDiff)))
);
