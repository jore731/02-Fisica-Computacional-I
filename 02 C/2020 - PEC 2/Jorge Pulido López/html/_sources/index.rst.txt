.. PEC2-C documentation master file, created by
   sphinx-quickstart on Sat May  9 12:24:51 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

PEC2 - C: Procesos de Poisson y desintegración radiactiva
=========================================================
Para el desarrollo de la siguiente memoria y mejor integración con las referencias al código en C, se utilizará la librería ``Sphinx 3.0.3`` [1]_ así como un módulo de documentación en C, ``Hawkmoth 0.5`` [2]_ para la propia librería. Todo ello ejecutado sobre ``Python 3.7.6`` [3]_ .

Para el desarrollo del contenido de la misma, se utilizará el código documentado en las siguientes páginas. Se trata de una archivo ejecutable en C compilado mediante el compilador ``gcc 4.9.2`` [4]_ así como la comunicación mediante pipes con ``GNUplot 5.2`` [5]_ para la graficación de los resultados.

Esta documentación estará disponible tanto en formato PDF como en formato HTML (`index.html`) a libre elección del lector.

.. toctree::
   :maxdepth: 4
   :caption: Contenidos
   
   rstFiles/ejercicios.rst
   rstFiles/PEC2Lib.rst



.. References

.. [1] **Sphinx** is a tool that makes it easy to create intelligent and beautiful documentation, written by Georg Brandl and licensed under the BSD license. -- https://www.sphinx-doc.org/

.. [2] **Hawkmoth** is a minimalistic Sphinx C Domain autodoc directive extension to incorporate formatted C source code comments written in reStructuredText into Sphinx based documentation. -- https://hawkmoth.readthedocs.io/

.. [3] **Python** is a programming language that lets you work quickly and integrate systems more effectively -- https://www.python.org

.. [4] **GCC** (The GNU Compiler Collection) includes front ends for C, C++, Objective-C, Fortran, Ada, Go, and D, as well as libraries for these languages. -- https://gcc.gnu.org

.. [5] **GNUplot** is a portable command-line driven graphing utility for Linux, OS/2, MS Windows, OSX, VMS, and many other platforms. -- http://www.gnuplot.info
