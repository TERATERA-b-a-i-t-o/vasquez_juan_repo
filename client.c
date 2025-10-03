#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
    int stato, reado, client_fd;
    struct sockaddr_in serv_addr;
    char* haro = "Hola desde el clienteeee";
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n error de crecion de socket pipipi \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\ndireccion no soportada PERIOD BV\n");
        return -1;
    }

    if ((stato = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nFallo la conexion jajaja\n");
        return -1;
    }

    send(client_fd, haro, strlen(haro), 0);
    printf("Hwenas, se envio el mensaje\n");
    reado = read(client_fd, buffer,
                   1024 - 1); 
    printf("%s\n", buffer);

    close(client_fd);
    return 0;

}