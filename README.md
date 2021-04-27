# DAA-P07-ParallelSchedulingTCT
### Sebastián Daniel Tamayo Guzmán.

El fichero ejecutable se encuentra en /build/main. Para compilar situarse en al carpeta build y ejecutar el comando make. Cabe destacar que en mi algoritmo voraz alternativo, en vez de buscar la mejor tarea-maquina-posicion en cada iteración, lo que hago es buscar la mejor tarea-posicion para cada máquina y realizo la inserción. 
La ejecución del programa desplega un menú interactivo que permite cargar uno de los ficheros de entrada de problemas que se encuentran en input-problems/ y aplicarle uno de los cuatro algoritmos desarrollados, permitiendo tambien escoger los parámetros para estos algoritmos si los precisan. El programa devolverá el tiempo que tardó en calcular la solución, mostrará el TCT asociado e imprimirá los programas de trabajo de cada máquina en el orden calculado.
