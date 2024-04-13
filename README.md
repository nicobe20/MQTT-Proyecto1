#MQTT-Proyecto1
##Juan Pablo duque Palencia y Nicolas Betancur Ochoa  
###Como ejecutar el proyecto.
La forma de ejecutar el proyecto es simplemente compilando el archivo Servidor.c de esta manera: ´´´gcc Servidor.c -o Servidor.out´´´ y el Cliente de la misma manera ´´´gcc Cliente.c -o Cliente.out´´´ para correr el servidor debes pasar los siguientes argumentos ´´´./Servidor.out <ip> <port> <Path_log/Log.txt>´´´ y para correr el Cliente ´´´./Cliente.out <Path_log/Log.txt>´´´


&centerdot;**Introducción.**<br>
El protocolo fue desarrollado por Juan Pablo Duque Palencia y Nicolás Betancur Ochoa, quienes se encargaron del desarrollo del cliente y del broker en lenguaje C. Se llevó a cabo una investigación exhaustiva sobre las especificaciones del protocolo MQTT. Para la implementación, también fue necesario profundizar en aspectos como la programación de sockets, su funcionamiento y su implementación. Adicionalmente, investigamos sobre las pthreads, su funcionamiento y aplicación, así como sobre los mutex y la concurrencia.

El desarrollo de nuestro proyecto se gestionó en dos repositorios de GitHub, uno de los cuales se utilizó para facilitar el desarrollo y las pruebas en nuestro entorno virtual. También realizamos consultas sobre ciertos aspectos de la instancia de AWS y su capacidad para gestionar conexiones, temas que abordaremos más adelante.

Finalmente, enfrentar este desafío en un lenguaje tan potente como C ha sido tanto interesante como enriquecedor. Hemos adquirido un conocimiento profundo sobre aspectos críticos de este lenguaje, especialmente en lo referente a apuntadores, manejo de memoria y conexiones, lo cual consideramos un logro significativo y gratificante.

&centerdot;**Desarrollo.**<br>
El desarrollo de este proyecto resultó tanto desafiante como interesante. Realizamos una extensiva consulta sobre la especificación del protocolo MQTT y decidimos implementar la versión 3.1. Durante el desarrollo, enfrentamos varios desafíos, desde problemas de conexión hasta cuestiones de manejo de memoria, que se convirtieron en retos interesantes de resolver.

El desarrollo del broker fue particularmente intrigante, ya que logramos adaptar nuestras conexiones para manejar un cliente por hilo, facilitando así la concurrencia del programa. El desarrollo de la aplicación cliente también presentó desafíos significativos, especialmente en la conexión con el servidor, que inicialmente representó varios problemas. Sin embargo, logramos solucionarlos, y fue un logro inmenso poder conectarnos a nuestro servidor con una simple prueba de telnet en localhost.

Nos enfrentamos a problemas con el puerto, ya que inicialmente no nos dimos cuenta de que necesitábamos una regla de seguridad personalizada que escuchara en el puerto 1883 para recibir conexiones. También fue un desafío lograr que nuestro servidor aceptara conexiones desde cualquier ubicación, pero logramos superarlo.

En general, el desarrollo fue productivo y manejable, aunque ciertamente fue difícil entender aspectos específicos, especialmente aquellos relacionados con la memoria y el manejo de punteros y direcciones de memoria. A lo largo del proyecto, aprendimos mucho sobre el lenguaje C, incluyendo estructuras (struct) y sus funciones y utilidades, así como sobre hilos (threads).

El desarrollo presentó muchos problemas, pero consideramos que fue exitoso y nos permitió aprender considerablemente. La aplicación cliente también se desarrolló en C, y representó un desafío que nos enseñó mucho sobre el manejo de variables y tipos de datos. Descubrimos tipos de variables útiles, como el unsigned short y el unsigned long. C ofrece una variedad inmensa de estos tipos de datos.

El desarrollo del cliente en C también fue complicado inicialmente debido a problemas con las conexiones de sockets y la creación de una interfaz usable para el cliente. Aunque algunos problemas nunca fueron completamente comprendidos, el desarrollo nos proporcionó ciertas ventajas, ya que al construir el servidor desde cero en C, estábamos bien preparados para desarrollar el cliente en el mismo lenguaje, encontrando muchas similitudes en la implementación.

&centerdot;**Aspectos Logrados y No logrados.**<br>

&centerdot;**Conclusiones.**<br>
En conclusion fue un proyecto muy desafiante que aunque no lo logramos terminar por completo pudimos aprender mucho sobre diferentes aspectos de la programacion en red, aprendimos sobre el protocolo MQTT y como implementarlo y como funciona, aprendimos nuevas cosas sobre C y diferentes forma de programar, aprendimos sobre concurrencia y como implementarla en C, aprendimos sobre sockets y conexiones me parece curioso el hecho de que tambien aprendimos sobre linux y que para el trabajo tuvimos tambien que aprender sobre ciertos comandos muy utiles como scp para cargar los documentos en la instacia virtual que aunque no terminamos usando aprendimos sobre este, fue un desarollo dificil en el cual tuvimos muchos problemas pero a la vez aprendimos de muchas cosas.

&centerdot;**Referencias**<br>
https://public.dhe.ibm.com/software/dw/webservices/ws-mqtt/mqtt-v3r1.html
https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf
https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
https://www.hivemq.com/blog/mqtt-essentials-part-3-client-broker-connection-establishment/
https://www.geeksforgeeks.org/multithreading-in-c/
https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
https://www.ibm.com/docs/es/i/7.5?topic=functions-atoi-convert-character-string-integer
https://www.tutorialspoint.com/cprogramming/c_pointers.htm
https://www.w3schools.com/c/c_pointers.php
https://pubs.opengroup.org/onlinepubs/009695399/functions/inet_addr.html  <- Esta pagina fue increiblemente util para el desarollo de nuestro proyecto y clave en entender muchas de las funciones usadas en el desarollo.
https://linux.die.net/man/3/inet_addr
https://linux.die.net/man/3/htons
https://www.ibm.com/docs/es/i/7.5?topic=functions-atoi-convert-character-string-integer
https://www.w3schools.com/c/c_structs.php
https://www.geeksforgeeks.org/structures-c/
https://www.tutorialspoint.com/cprogramming/c_structures.htm



Juan Pablo duque Palencia y Nicolas Betancur Ochoa  


