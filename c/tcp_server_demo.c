#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
char *resp_buff = "\
HTTP/1.1 200 OK\r\n\
Server: nginx/0.8.55\r\n\
Content-Length: 6\r\n\
Content-Type: text/html\r\n\
\r\n\
123456";


int main(int argc, char** argv)
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    unlink("server_socket");
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8081);
    server_len = sizeof(server_address);
    int ret = bind(
            server_sockfd, 
            (struct sockaddr *)&server_address, 
            server_len
    );
    listen(server_sockfd, 5);
    while(1)
    {
        //char ch;
        char buff[2048] = {0};
        

        printf("server_waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
                (struct sockaddr*) &client_address, &client_len);
        read(client_sockfd, buff, 2048);
//        ch++;
//        write(client_sockfd, &ch, 1);
        printf("buff = %s\n", buff);
        write(client_sockfd, resp_buff, strlen(resp_buff));

        close(client_sockfd);
    }
}
