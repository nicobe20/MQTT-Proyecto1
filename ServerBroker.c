#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
//standard libraries used for programming with threads

#define MAX_CLIENTES 10
#define TAMAÑO_BUFFER 1024  

// Structure to hold client information
typedef struct {
    int sockfd;
    struct sockaddr_in addr;  //address info of the client connecting to the server
    pthread_t thread;
} Client;

//void *manejoDeClientes(void *arg);
//void addCliente(int sockfd, struct sockaddr_in addr, pthread_t thread) //address info, socketfd is socket file description 
//void removerCliente(int index) //remover de la lista de clientes
//void clean();

Client cliente[MAX_CLIENTS];
pthread_mutex_t mutex;

//Aqui vamos a crear el manejo de los clientes, como aceptamos a los clientes que se quieren conectar y los que se van a desconectar.

int main(int argc, char *argv[]){
    pthread_mutex_init(&mutex, NULL);
    if(argc != 4 ){
        printf("Input incorrecto -> ./ %s <ip> <port> </path/log.log ", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    char *port = argv[2];
    char *logPath = argv[3];

    /*
    printf("ip = %s",ip);
    printf("port = %s",port);
    printf("logPath = %s",logPath)
    */
    

//socket
int server_sockfd = socket(AF_INET, SOCK_STREAM, 0); // <- wtf?? explicar esto bien y entenderlo bien
if (server_sockfd == -1){
    perror("Error al crear sockets");
    return 1;

}
}

//Aqui inicializar mutex threads

//Servidor 
//REVISAR ESTO MUY BIEN PORFAVOR.
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(ip);
server_addr.sin_port = htons(atoi(port));

//Vincular el socket del server con el address y el port (port para usar 1883)
if(bind(server_sockfd,(struct sockaddr_in* )&server_addr, sizeof(server_addr)) == -1){ //manejo del error en la vinculacion del servidor y vinculacion, REVISAR BIEN ESTO!!!!
    perror("Error de vinculo");
    close(server_sockfd);
    return 1; 
}

//Revisar conexiones entrantes
//#include <sys/socket.h>
//int listen(int socket, int backlog);
if(listen(server_sockfd, MAX_CLIENTES == -1) == -1){
    perror("Error aqui :/");
    close(server_sockfd);
    return 1;
}

//Funciones de clientes!
void añadirCliente(){


}

void eliminarCliente(){


}



//el return 1, simplemente es un indicador que muestra que la aplicacion no se termino de ejecutar bien.
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/listen.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html
//esas paginas esta buenas 

