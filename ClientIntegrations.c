#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TAMANO_BUFFER 2048

int main(int argc, char *argv[]) {
    // Ensure correct usage
    if (argc != 2) {
        printf("Usage: %s <Location/log.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *logPath = argv[1]; // Log file path from the command line argument

    char ip[INET_ADDRSTRLEN]; // Buffer for IP address input by the user
    int port; // Variable to store the user-input port number

    // Prompt the user for the IP address of the MQTT broker
    printf("Aplicacion Cliente\n");
    printf("Ingrese la IP del broker: ");
    scanf("%15s", ip); // Capture IP address from the user

    // Prompt the user for the port number
    printf("Ingrese el puerto: ");
    scanf("%d", &port); // Capture port number from the user

    // Logging connection attempt
    FILE *logFile = fopen(logPath, "a");
    if (logFile == NULL) {
        perror("Error al abrir el archivo de log");
        exit(EXIT_FAILURE);
    }
    fprintf(logFile, "Intentando conectar al servidor MQTT en %s:%d\n", ip, port);
    fclose(logFile);

    // Creating the socket
    int sockfd;
    struct sockaddr_in direccionServidor;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(port); // Use user-specified port
    direccionServidor.sin_addr.s_addr = inet_addr(ip); // Use user-specified IP

    // Attempt to connect to the MQTT broker

    if (connect(sockfd, (struct sockaddr *)&direccionServidor, sizeof(direccionServidor)) < 0) {
        perror("Conexión fallida");
        close(sockfd);
        exit(EXIT_FAILURE);
        
    } else {
        printf("Conectado al servidor MQTT.\n");
        fflush(stdout);
    }

    // Placeholder for MQTT CONNECT message. Should be replaced with actual implementation.
    char mensajeConnect[] = "0001xxxx";
    if (send(sockfd, mensajeConnect, strlen(mensajeConnect), 0) < 0) {
        perror("Fallo al enviar mensaje CONNECT");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else {
        printf("Mensaje CONNECT enviado, esperando CONNACK...\n");
    }

    // Receive response from the server
    char bufferRespuesta[TAMANO_BUFFER];
    ssize_t lenRespuesta = recv(sockfd, bufferRespuesta, TAMANO_BUFFER - 1, 0);

    if (lenRespuesta > 0) {
        bufferRespuesta[lenRespuesta] = '\0'; // Ensure null-terminated string for printing

        // Placeholder for parsing server response. Implementation depends on protocol details.
        printf("Respuesta recibida del servidor: %s\n", bufferRespuesta);
    } else if (lenRespuesta == 0) {
        printf("El servidor cerró la conexión\n");
    } else {
        perror("Error al recibir respuesta");
    }

    // Interactive loop for sending messages to the server
    while (1) {
        printf("Ingrese su mensaje (escriba 'salir' para terminar): ");
        char mensajeUsuario[TAMANO_BUFFER];
        if (fgets(mensajeUsuario, TAMANO_BUFFER, stdin) != NULL) {
            // Check if the user wants to exit
            if (strcmp(mensajeUsuario, "salir\n") == 0) {
                break;
            }

            // Send the user's message to the server
            if (send(sockfd, mensajeUsuario, strlen(mensajeUsuario), 0) < 0) {
                perror("Fallo al enviar el mensaje");
                break;
            }
        }
    }

    // Close the socket and end the program
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