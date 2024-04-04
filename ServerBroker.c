#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
//standard libraries used for programming with threads

#define MAX_CLIENTES 10
#define BUFFER_SIZE 2048  // Tamaño suficiente para la mayoría de los paquetes MQTT
//#define PUERTO_MQTT 1883
#define DEFAULT_PORT 1883
// Structure to hold client information
typedef struct {
    int sockfd;
    struct sockaddr_in addr; //address info of the client connecting to the server
} Cliente;

Cliente clientes[MAX_CLIENTES];
pthread_mutex_t mutexClientes = PTHREAD_MUTEX_INITIALIZER;


void *manejarConexionCliente(void *data) {
    int sockfd = *((int*)data);
    free(data);  // Liberar memoria asignada para el descriptor del socket

    char buffer[BUFFER_SIZE];
    ssize_t mensajeLen;

    // Bucle de lectura: leer los datos del cliente
    while ((mensajeLen = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
        // Aquí se manejarían los mensajes MQTT recibidos
        //POR IMPLEMENTAR Almacenamiento de mensajes


        printf("Mensaje recibido (bytes): %zd\n", mensajeLen);
        // Por simplicidad, solo imprimimos la longitud del mensaje
    }
    if (mensajeLen == 0) {
        // Cliente desconectado
        printf("Cliente desconectado\n");
    } else if (mensajeLen < 0) {
        perror("Error en recv");
    }

    close(sockfd);  // Cerrar la conexión
    return NULL;
}

int main(int argc, char argv[]) {
// manejo de argumentos por consola

    if(argc != 4){
        fprintf(stderr, "Uso: %s <ip> <port> <path/log.log>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip = argv[1];
    char *port = argv[2];
    char *logPath = argv[3];

    // Asegurándose de que el puerto no esté vacío, si lo está, usa el puerto por defecto
    if (strlen(port) == 0) {
        port = DEFAULT_PORT;
    }

    // Por ahora, solo imprimimos los valores para verificar

    //Server Sturcture
    struct sockaddr_in servidorAddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(ip),
        .sin_port = htons(atoi(port)),
    };
    printf("Iniciando el servidor en IP: %s, Puerto: %s\n", ip, port);

    //Creacion del socket
    int servidorSockfd = socket(AF_INET, SOCK_STREAM, 0);  //AF_INET VERIFICAR !!!! "SOCK_STREAM IS STANDAR TCP. CONNECTION BASED PROTOCOL, SENDS VARIOUS PACKETS"
    if (servidorSockfd < 0) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

      //bind server to socket
    if (bind(servidorSockfd, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0) {
        perror("Error al vincular el socket del servidor");
        close(servidorSockfd);
        exit(EXIT_FAILURE);
    }
    //listen for incoming connections
    if (listen(servidorSockfd, MAX_CLIENTES) < 0) {
        perror("Error al escuchar en el socket del servidor");
        close(servidorSockfd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor MQTT ejecutándose en el puerto %s...\n", port);

    // Manejo del archivo de log
    FILE *logFile = fopen(logPath, "a"); // Abre el archivo en modo append
    if (logFile == NULL) {
        perror("Error al abrir el archivo de log");
        exit(EXIT_FAILURE);
    }
     // Registrando el inicio del servidor en el archivo de log
    fprintf(logFile, "Servidor iniciado en IP: %s, Puerto: %s\n", ip, port);
    fclose(logFile); 

/*
old
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(ip);
server_addr.sin_port = htons(atoi(port));
*/


//manejo de clientes continuos, alocar espacio de memoria para los clientes entrantes, desalocar las threads para darselas a los nuevos clientes.
    while (1) {

        struct sockaddr_in clienteAddr;
        socklen_t clienteAddrLen = sizeof(clienteAddr);
        int* nuevoSockfd = malloc(sizeof(int));
        *nuevoSockfd = accept(servidorSockfd, (struct sockaddr *)&clienteAddr, &clienteAddrLen);

        if (*nuevoSockfd < 0) {
            perror("Error al aceptar conexión del cliente");
            free(nuevoSockfd);
            continue;
        }

        pthread_t threadId;
        if (pthread_create(&threadId, NULL, manejarConexionCliente, nuevoSockfd) != 0) {
            perror("Error al crear el hilo del cliente");
            close(*nuevoSockfd);
            free(nuevoSockfd);
        }
    }

    return 0;
}
