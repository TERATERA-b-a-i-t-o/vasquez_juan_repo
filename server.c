#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> 
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
 

void func(int connfd)
{
    char buff[MAX];
    int n;
   
    for (;;) {
        bzero(buff, MAX);
 
        
        read(connfd, buff, sizeof(buff));
       
        printf("de: %s\t para: ", buff);
        bzero(buff, MAX);
        n = 0;
       
        while ((buff[n++] = getchar()) != '\n')
            ;
 
        
        write(connfd, buff, sizeof(buff));
 
        
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
 

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
 
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error de creacion del socket...\n");
        exit(0);
    }
    else
        printf("Se creo el socket :D..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
 
    
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Fallo :C\n");
        exit(0);
    }
    else
        printf("El socket se conecto con exito yippieeee..\n");
 
    
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen fallo...\n");
        exit(0);
    }
    else
        printf("El servidor esta escuchando ..\n");
    len = sizeof(cli);
 
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("error de aceptacion del servidor...\n");
        exit(0);
    }
    else
        printf("El servidor a aceptado...\n");
 
    func(connfd);
 
   
    close(sockfd);
}