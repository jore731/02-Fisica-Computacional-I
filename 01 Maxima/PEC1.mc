/** @brief Física Computacional I: Prueba de Evauación Continua 1
 @author Jorge Pulido López
 @email jpulido147@alumno.uned.es
 @dni 05950206Z
 @date 10 Abril 2020
**/
/**----------------------------------EJERCICIO 1----------------------------------**/
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
    [data, mData, data_x, data_y, dom_x, dom_y, data_linear, 
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
    data_x:transpose(mData)[1],
    data_y:transpose(mData)[2]
    ,
    dom_x:[x,apply(min,data_x), apply(max,data_x)],
    dom_y:[y,apply(min,data_y), apply(max,data_y)]
    ,

/*******************HITO 3: GUARDADO DE INTERPOLACIONES EN .LISP**********************/
    save(outputDataPath,data_linear,data_lagrange,data_splines)
    ,
/************************HITO 2: GUARDADO DE GRÁFICA EN .PDF*************************/
    plot2d ([[discrete,data],data_linear,data_lagrange, data_splines],  
            dom_x,dom_y,
            [style,points,lines,lines,lines],
            [pdf_file,outputPlotPath])
    ,
/***********************HITO 1: GRAFICADO DE DATOS EN PANTALLA***********************/
    plot2d ([[discrete,data],data_linear,data_lagrange, data_splines],  
            dom_x,dom_y,
            [style,points,lines,lines,lines])
    ,
/****************************MENSAJE DE EJECUCIÓN CORRECTA***************************/
    print(sconcat(outputPlotPath," generated")),
    print(sconcat(outputDataPath," generated")),
    return ("done")
);

/**
 @brief EJERCICIO 1 (Con filtrado de datos):  Filtra y valida la entrada de datos antes
                                             de pasarlos a la función principal.

 @param rawDataFilePath Nombre/Ruta del archivo a importar.
    - Ruta completa al archivo
    - Nombre del archivo de datos
    - Funciona con y sin extensión
 @param kargs    - Parámetros opcionales para la ejecución de la función.
                - Son argumentos posicionales, que pueden omitirse siempre y cuando se 
                    omitan todos los parametros posteriores.
                - Para omitir parámetros intermedios, le daremos el valor "None".
                    (ejemplo: multi_interpolation("data-1",
                                                  None,
                                                  "data-1_processed.lisp")
                        rawOutputPlotFileName y forceOutputPath son omitidos)
    @param rawOutputPlotFileName - Nombre del archivo gráfico generado (.pdf).
                                    - Funciona con y sin extensión.
                                    - Comprueba que la extensión sea correcta.
    @param rawOutputDataFileName - Nombre/Ruta del archivo de datos generado (.lisp).
                                    - Funciona con y sin extensión.
                                    - Comprueba que la extensión sea correcta.
    @param forceOutputPath   - Ruta de destino de los archivos generados.
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