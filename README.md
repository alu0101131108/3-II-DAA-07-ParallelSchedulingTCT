# DAA-P07-ParallelSchedulingTCT
### Sebastián Daniel Tamayo Guzmán.

El fichero ejecutable se encuentra en /build/main. Para compilar situarse en al carpeta build y ejecutar el comando make.
Por motivos de tiempo y problemas con los algoritmos no he podido realizar un informe apropiado. En su lugar coloco este archivo.
Cabe destacar que en mi algoritmo voraz alternativo, en vez de buscar la mejor tarea-maquina-posicion en cada iteración, lo que hago es buscar la mejor tarea-posicion para cada máquina e ir insertándola poco a poco.
No he tenido tiempo de realizar el apartado c propuesto.
La ejecución del programa devuelve una serie de datos en relación a los archivos de entrada de ejemplo propuestos por la profesora, mostrando el valor de la suma de los tct's de cada máquina, para cada problema. Se pueden descomentar las dos lineas correspondientes en src/main.cpp para mostrar el orden de asignacion de las tareas para cada máquina.

Resultados entrega 1:
==========Tasks: 40, Machines: 2, S1_1.==========

----------Constructive-TCT: 13664----------

----------Alternative-TCT: 13739----------


==========Tasks: 40, Machines: 4, S1_1.==========

----------Constructive-TCT: 7459----------

----------Alternative-TCT: 7572----------


==========Tasks: 40, Machines: 6, S1_1.==========

----------Constructive-TCT: 5377----------

----------Alternative-TCT: 5552----------


==========Tasks: 40, Machines: 8, S1_1.==========

----------Constructive-TCT: 4415----------

----------Alternative-TCT: 4558----------


Resultados entrega 2:
==========Tasks: 40, Machines: 2, S1_1.==========

----------Constructive-TCT: 13664----------

----------Alternative-TCT: 13739----------

----------Grasp-IntraSwap-TCT: 13913----------

----------Grasp-IntraInsert-TCT: 13908----------

----------Grasp-InterSwap-TCT: 14070----------

----------Grasp-InterInsert-TCT: 13703----------


==========Tasks: 40, Machines: 4, S1_1.==========

----------Constructive-TCT: 7459----------

----------Alternative-TCT: 7572----------

----------Grasp-IntraSwap-TCT: 7564----------

----------Grasp-IntraInsert-TCT: 7609----------

----------Grasp-InterSwap-TCT: 7336----------

----------Grasp-InterInsert-TCT: 7323----------


==========Tasks: 40, Machines: 6, S1_1.==========

----------Constructive-TCT: 5377----------

----------Alternative-TCT: 5552----------

----------Grasp-IntraSwap-TCT: 5341----------

----------Grasp-IntraInsert-TCT: 5427----------

----------Grasp-InterSwap-TCT: 5228----------

----------Grasp-InterInsert-TCT: 5238----------


==========Tasks: 40, Machines: 8, S1_1.==========

----------Constructive-TCT: 4415----------

----------Alternative-TCT: 4558----------

----------Grasp-IntraSwap-TCT: 4321----------

----------Grasp-IntraInsert-TCT: 4353----------

----------Grasp-InterSwap-TCT: 4236----------

----------Grasp-InterInsert-TCT: 4292----------