/** @brief Física Computacional I: Prueba de Evauación Continua 1
@author Jorge Pulido López
@email jpulido147@alumno.uned.es
@dni 05950206Z
@date 10 Abril 2020
**/

/**
@brief EJERCICIO 1: Interpolación lineal, lagrangiana y por medio de splines 
de los datos importados de un fichero.

@Param rawDataFilePath Nombre/Ruta del archivo a importar.
    - Ruta completa al archivo
    - Nombre del archivo de datos
    - Funciona con y sin extensión
@param kargs Parámetros opcionales para la ejecución de la función.
    @optparam rawOutputPlotFileName Nombre del archivo gráfico generado (.pdf).
                                    Funciona con y sin extensión.
                                    Comprueba que la extensión sea correcta.
    @optparam rawOutputDataFileName Nombre/Ruta del archivo de datos generado (.lisp).
                                    Funciona con y sin extensión.
                                    Comprueba que la extensión sea correcta.
    @optparam forceOutputPath   Ruta de destino de los archivos generados.
                                Formato Linux (Acepta "/" y "\\", pero no "\").
@Return Una vez el proceso ha concluido y los archivos han sido generados correctamente, retorna 0.
        Los siguientes errores están contemplados:
            - "{DataFilePath} not found"
            - "Invalid output plot-file name"
            - "Invalid output data-file name"
**/
multi_interpolation(rawDataFilePath,[kargs]) := block(
    [rawOutputPlotFileName, rawOutputDataFileName, 
    forceOutputPath, rawDataFileName,rawDataFileDirectory, 
    workingDirectory, dataFileName, dataFileExtension, dataFilePath,
    data, mData, outputDataFileName, outputDataFileExtension, outputDataPath,
    outputPlotFileName, outputPlotFileExtension, outputPlotPath, data_x,
    data_y, dom_x, dom_y, data_linear, data_lagrange, data_splines
    ]
    ,
    load(interpol)
    ,
    load(operatingsystem)
    ,
    load(stringproc)
    ,
    if length(kargs)>0 then rawOutputPlotFileName : kargs[1]
    ,
    if length(kargs)>1 then rawOutputDataFileName : kargs[2]
    ,
    if length(kargs)>2 then forceOutputPath : kargs[3]
    ,
    rawDataFileName: pathname_name(rawDataFilePath)
    ,
    rawDataFileDirectory: pathname_directory(rawDataFilePath)
    ,
    if rawDataFileDirectory="" then workingDirectory: getcurrentdirectory()
    else workingDirectory: rawDataFileDirectory
    ,
    if (ssearch(".",rawDataFileName)=false) then (
        dataFileName: rawDataFileName,
        dataFileExtension: "out"
    )
    else [dataFileName,dataFileExtension] : split(rawDataFileName, ".")
    ,
    dataFilePath : sconcat(workingDirectory,"/",dataFileName,".",dataFileExtension)
    ,
    if not file_search(dataFilePath) then error(sconcat(rawDataFilePath," not found"))
    ,
    data:read_nested_list(dataFilePath)
    ,
    if not stringp(forceOutputPath) then outputPath: workingDirectory
    else outputPath: forceOutputPath
    ,
    if not stringp(rawOutputPlotFileName) then (
        outputPlotFileName: dataFileName,
        outputPlotFileExtension: "pdf"
    )
    else (
        if (ssearch(".",rawOutputPlotFileName)=false) then (
            outputPlotFileName: rawOutputPlotFileName,
            outputPlotFileExtension: "pdf"
        )
        else (
            [outputPlotFileName,outputPlotFileExtension] : split(rawOutputPlotFileName, ".")
            
        )
    )
    ,
    if outputPlotFileExtension="pdf" then 
        outputPlotPath: sconcat(outputPath,"/", outputPlotFileName,".",outputPlotFileExtension)
    else
        error(sconcat("Invalid output plot-file name"))
    ,
    if not stringp(rawOutputDataFileName) then (
        outputDataFileName: dataFileName,
        outputDataFileExtension: "lisp"
    )
    else (
        if (ssearch(".",rawOutputDataFileName)=false) then (
            outputDataFileName: rawOutputDataFileName,
            outputDataFileExtension: "lisp"
        )
        else (
            [outputDataFileName,outputDataFileExtension] : split(rawOutputDataFileName, ".")
            
        )
    )
    ,
    if outputDataFileExtension="lisp" then 
        outputDataPath: sconcat(outputPath,"/", outputDataFileName,".",outputDataFileExtension)
    else
        error(sconcat("Invalid output data-file name"))
    ,
    mData:apply(matrix,data),
    data_x:transpose(mData)[1],
    data_y:transpose(mData)[2],
    
    data_linear:linearinterpol(data),
    data_lagrange:lagrange(data),
    data_splines:cspline(data),
    
    dom_x:[x,apply(min,data_x), apply(max,data_x)],
    dom_y:[y,apply(min,data_y), apply(max,data_y)],
    plot2d ([[discrete,data],data_linear,data_lagrange, data_splines],  
            dom_x,dom_y,
            [style,points,lines,lines,lines],
            [pdf_file,outputPlotPath]),
    plot2d ([[discrete,data],data_linear,data_lagrange, data_splines],  
            dom_x,dom_y,
            [style,points,lines,lines,lines]),
    save(outputDataPath,data_linear,data_lagrange,data_splines),

    return (sconcat(outputPlotFileName, " and ", outputDataPath, " generated"))
);
