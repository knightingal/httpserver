#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "http_req_parser.h"


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
        //char buff_content[READ_LEN_ONCE] = {0};
        //Buff buff = {buff_content, READ_LEN_ONCE, 0};
        //My_string fd_read_buff = {&buff, 0, READ_LEN_ONCE};

        printf("server_waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
                (struct sockaddr*) &client_address, &client_len);
        int pid = fork();
        if (pid == 0)
        {
            Buff buff;
            My_string read_buff;
            read_buff.buff = &buff;
            read_buff.start_index = 0;
            read_buff.end_index = 0;
            on_request(client_sockfd, &read_buff, do_request);
            exit(0);
        }
        
    }
}
