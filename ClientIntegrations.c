#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PUERTO_MQTT 1883
#define TAMANO_BUFFER 2048

char ipClient; //client ip, look for a way to get it from wherever the client is running
char ipBroker; //ip to connect to the broker 
char query; // tipo de mensaje


int main() {

    if(argc != 1){
        printf("Usage: %s <Location/log.txt> \n",argv[0])
    }
      char *logPath = argv[1]; //same implementation from server...
    

    printf("Aplicacion Cliente");
    scanf("Broker Ip: ", ipClient);
    
    //log file modifications:


    //sockets
    int sockfd;
    struct sockaddr_in direccionServidor;
    char bufferRespuesta[TAMANO_BUFFER];
    ssize_t lenRespuesta;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(PUERTO_MQTT);
    direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");  // Asumimos servidor en localhost

    // Conectar al servidor MQTT
    if (connect(sockfd, (struct sockaddr *)&direccionServidor, sizeof(direccionServidor)) < 0) {
        perror("Conexión fallida");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    else{
        printf("Conectado al servidor MQTT.\n");
    }
    

    // Enviar mensaje CONNECT (representación simple)
    
    char mensajeConnect[] = "0001xxxx";
    if (send(sockfd, mensajeConnect, strlen(mensajeConnect), 0) < 0) {
        perror("Fallo al enviar mensaje CONNECT");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    else{
        
        printf("Mensaje CONNECT enviado, esperando CONNACK...\n");
    }

    

    // Asegurarse de que la respuesta es una cadena de caracteres válida
    lenRespuesta = recv(sockfd, bufferRespuesta, TAMANO_BUFFER - 1, 0);

    if(lenRespuesta>0){
    bufferRespuesta[lenRespuesta] = '\0';

    // Deserializar el mensaje MQTT
        char MessageType[5]; // Primeros 4 caracteres + '\0'
        char DUPFlag[2];     // Quinto carácter + '\0'
        char QoSFlag[3];     // Sexto y séptimo caracteres + '\0'
        char RETAIN[2];      // Octavo carácter + '\0'

        strncpy(MessageType, bufferRespuesta, 4);
        MessageType[4] = '\0';

        DUPFlag[0] = bufferRespuesta[4];
        DUPFlag[1] = '\0';

        strncpy(QoSFlag, bufferRespuesta + 5, 2);
        QoSFlag[2] = '\0';

        RETAIN[0] = bufferRespuesta[7];
        RETAIN[1] = '\0';

        // Convertir MessageType de binario a decimal
        int messageTypeInt = strtol(MessageType, NULL, 2);
        printf("Entero MessageType %d",messageTypeInt);
         switch (messageTypeInt) {
            
            case 2: // CONNACK
                printf("CONNACK recibido, puede comenzar a enviar mensajes.\n");
                
                break;
            default:
                printf("\n");
                printf("Longitud de la respuesta: %zd\n", lenRespuesta);
                printf("Respuesta no reconocida: %s\n", bufferRespuesta);
                close(sockfd);
                exit(EXIT_FAILURE);
        
    }
    }

    // Bucle para enviar mensajes ingresados por el usuario
    while (1) {
        printf("Ingrese su mensaje (escriba 'salir' para terminar): ");
        char mensajeUsuario[TAMANO_BUFFER];
        if (fgets(mensajeUsuario, TAMANO_BUFFER, stdin) != NULL) {
            // Verificar si el usuario quiere terminar
            if (strcmp(mensajeUsuario, "salir\n") == 0) {
                break;
            }

            // Enviar el mensaje ingresado al servidor
            if (send(sockfd, mensajeUsuario, strlen(mensajeUsuario), 0) < 0) {
                perror("Fallo al enviar el mensaje");
                break;
            }
        }
    }

    close(sockfd);
    return 0;
}


//Notes 
/*
    -Fix, implement ip and por from client -> Doing.
    -Complete protocol -> Doing.
    -Integrate -> Working.
    -Comments -> Doing.
    
*/