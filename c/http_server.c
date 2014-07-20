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
        char buff_content[READ_LEN_ONCE] = {0};
        Buff buff = {buff_content, READ_LEN_ONCE, 0};
        My_string fd_read_buff = {&buff, 0, READ_LEN_ONCE};

        printf("server_waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
                (struct sockaddr*) &client_address, &client_len);
        My_string read_buff;
        Request request;
        //parse_request(client_sockfd, &read_buff, &request); 
        on_request(client_sockfd, &read_buff, do_request);
#if 0
        int read_len = read(client_sockfd, buff_content, READ_LEN_ONCE);
        if (read_len <= 0)
        {
            close(client_sockfd);
            continue;
        }
        fd_read_buff.end_index = read_len;

//        ch++;
//        write(client_sockfd, &ch, 1);
        print_string(&fd_read_buff);
        Req_line req_line  = get_req_line(client_sockfd, &fd_read_buff);

        print_string(&req_line.path);

        My_string* headers 
            = (My_string*)malloc(sizeof(My_string) * Headers_count);
        Header header;
        while(1)
        {
            header = get_header(client_sockfd, &fd_read_buff);
            if (header.header_name < 0)
            {
                break;
            }
            print_string(&header.header_value);
            headers[header.header_name] = header.header_value;
        }

        My_string body;

        int body_len;
        if (string_to_int(&headers[CONTENT_LENGTH_INDEX], &body_len) != 0)
        {
            break;
        }
        read_length(client_sockfd, &fd_read_buff, &body, body_len);
        print_string(&body);
#endif
#if 0
        My_string line;
        int i;
        for(i = 0; i < 4; i++)
        {
            read_line(client_sockfd, &fd_read_buff, &line);
            print_string(&line);


        }
#endif
        
        write(client_sockfd, resp_buff, strlen(resp_buff));

        close(client_sockfd);
    }
}
