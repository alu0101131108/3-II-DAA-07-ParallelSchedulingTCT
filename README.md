# DAA-P07-ParallelSchedulingTCT
### Sebastián Daniel Tamayo Guzmán.

El fichero ejecutable se encuentra en /build/main. Para compilar situarse en al carpeta build y ejecutar el comando make. Cabe destacar que en mi algoritmo voraz alternativo, en vez de buscar la mejor tarea-maquina-posicion en cada iteración, lo que hago es buscar la mejor tarea-posicion para cada máquina y realizo la inserción. 
La ejecución del programa devuelve una serie de datos en relación a los archivos de entrada de ejemplo propuestos por la profesora, mostrando el valor de la suma de los tct's de cada máquina, para cada problema. Se puede agregar la orden framework.printMachineSchedules() en src/main.cpp para mostrar el orden de asignacion de las tareas para cada máquina.