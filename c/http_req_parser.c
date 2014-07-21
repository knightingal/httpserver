#include "http_req_parser.h"
#include "http_protocol.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int read_line(int fd, My_string* read_buff, My_string* line)
{
    char* tmp_buff_content = "\r\n";
    Buff tmp_buff = {tmp_buff_content, 2, 0};
    My_string temp_string = {&tmp_buff, 0, 2};

    int index;
    while(1)
    {

        index = index_of_sub_string(read_buff, &temp_string);
        if (index >= 0)
        {
            break;
        }
        int read_buff_len = get_string_len(read_buff);
        if (read_buff_len < 0)
        {
            printf("error in http_req_parser.c:22\n");
            return -1;
        }
        
        int whole_buff_len = read_buff_len + READ_LEN_ONCE;
        Buff* read_buff_appended = (Buff*)malloc(sizeof(Buff));
        read_buff_appended->buff_content = 
            (char*)malloc(sizeof(char) * whole_buff_len);
        read_buff_appended->buff_len = whole_buff_len;

        memcpy(read_buff_appended->buff_content, 
                read_buff->buff->buff_content + read_buff->start_index,
                get_string_len(read_buff));

        int read_len = read(fd, 
                read_buff_appended->buff_content + get_string_len(read_buff),
                READ_LEN_ONCE); 

        read_buff->buff = read_buff_appended;
        read_buff->start_index = 0;
        read_buff->end_index = read_buff_len + read_len;
        
    }
    line->buff = read_buff->buff;
    line->start_index = read_buff->start_index;
    line->end_index = read_buff->start_index + index + 2;

    read_buff->start_index = line->end_index;
    return 0;
}

Buff POST_BUFF = {"POST", 4, 0};
My_string POST_STR = {&POST_BUFF, 0, 4};

Buff GET_BUFF = {"GET", 3, 0};
My_string GET_STR = {&GET_BUFF, 0, 3};


//int Headers_count = sizeof(Headers) / sizeof(My_string*);

Req_line get_req_line(int fd, My_string* read_buff)
{
    Req_line req_line;
    req_line.method = 0;
    My_string req_str;
    read_line(fd, read_buff, &req_str);
    
    My_string method_str, path_str, version_str;
    int split_index = split_string(&req_str, &method_str, &path_str, ' ');
    if (split_index < 0)
    {
        return req_line;
    }
    req_str.start_index += split_index + 1;
    split_index = split_string(&req_str, &path_str, &version_str, ' ');

    if (split_index < 0)
    {
        return req_line;
    }
    version_str.start_index += 1;

    if (cmp_string(&method_str, &POST_STR) == 0)
    {
        req_line.method = METHOD_POST;
    }
    else if (cmp_string(&method_str, &GET_STR) == 0)
    {
        req_line.method = METHOD_GET;
    }
    else
    {
        return req_line;
    }
    
    cpy_string_from_string(
            &req_line.path, &path_str, 
            0, get_string_len(&path_str)
    );

    req_line.version = 1;


    return req_line;
}
    

Header get_header(int fd, My_string* read_buff)
{

    Header header;
    header.header_name = -1;
    My_string header_str;
    read_line(fd, read_buff, &header_str);

    My_string header_name_str, header_value_str;
    int split_index = split_string(
            &header_str, 
            &header_name_str, 
            &header_value_str, 
            ':'
    );
    if (split_index < 0)
    {
        return header;
    }
    header_value_str.start_index += 2;
    header_value_str.end_index -= 2;
    int i;

    for (i = 0; i < HEADER_COUNT; i++)
    {
        if (cmp_string(&header_name_str, Headers[i]) == 0)
        {
            break;
        }
    }
    header.header_name = i;
    
    header.header_value = header_value_str;

    return header;
}

int read_length(int fd, My_string* read_buff, My_string* out_line, int len)
{
    int read_buff_len = get_string_len(read_buff);
    if (read_buff_len < 0)
    {
        return -1;
    }
    if (out_line == NULL)
    {
        return -1;
    }
    int read_len = 0;
    while(read_buff_len < len)
    {
        int whole_buff_len = read_buff_len + READ_LEN_ONCE;
        Buff* read_buff_appended = (Buff*)malloc(sizeof(Buff));
        read_buff_appended->buff_content = 
            (char*)malloc(sizeof(char) * whole_buff_len);
        read_buff_appended->buff_len = whole_buff_len;

        memcpy(read_buff_appended->buff_content, 
                read_buff->buff->buff_content + read_buff->start_index,
                get_string_len(read_buff));

        read_len = read(fd, 
                read_buff_appended->buff_content + get_string_len(read_buff),
                READ_LEN_ONCE
        ); 
        if (read_len <= 0)
        {
            return -1;
        }

        read_buff->buff = read_buff_appended;
        read_buff->start_index = 0;
        read_buff->end_index = read_buff_len + read_len;
        read_buff_len = get_string_len(read_buff);
    }
    
    out_line->buff = read_buff->buff;
    out_line->start_index = read_buff->start_index;
    out_line->end_index = read_buff->start_index + len;

    read_buff->start_index = out_line->end_index;

    return len;
}

int parse_request(int fd, My_string* read_buff, Request* request)
{
    if (get_string_len(read_buff) < 0)
    {
        read_buff->buff->buff_content = (char*)malloc(READ_LEN_ONCE * sizeof(char));
        read_buff->buff->buff_len = READ_LEN_ONCE;
        read_buff->start_index = 0;
        read_buff->end_index = 0;
    }
    Req_line req_line = get_req_line(fd, read_buff);
    
    My_string* headers
        = (My_string*)malloc(sizeof(My_string) * HEADER_COUNT);

    Header header;
    while(1)
    {
        header = get_header(fd, read_buff);
        if (header.header_name < 0)
        {
            break;
        }
        headers[header.header_name] = header.header_value;
    }

    My_string body;
    int body_len;
    if (string_to_int(&headers[CONTENT_LENGTH_INDEX], &body_len) != 0)
    {
        return -1;
    }
    read_length(fd, read_buff, &body, body_len);

    request->req_line = req_line;

    request->headers = headers;

    request->body = body;

    return 0;

}
    
int on_request(int fd, My_string* read_buff, Request_callback do_request)
{
    Request request;
    if (parse_request(fd, read_buff, &request) != 0)
    {
        return -1;
    }

    return do_request(fd, &request);
}

int do_request(int fd, Request* request)
{
    printf("do request\n");
    print_request(request);
char *resp_buff = "\
HTTP/1.1 200 OK\r\n\
Server: nginx/0.8.55\r\n\
Content-Length: 6\r\n\
Content-Type: text/html\r\n\
\r\n\
123456";
    write(fd, resp_buff, strlen(resp_buff));
    close(fd);
    return 0;
}

void print_request(Request* request)
{
    printf("req line = \n");
    print_req_line(&(request->req_line));

    printf("\nheaders = \n");
    int i;
    for (i = 0; i < HEADER_COUNT; i++)
    {
        print_string(request->headers + i);
    }

    printf("\nbody = \n");
    print_string(&(request->body));
}


void print_req_line(Req_line* req_line)
{
    printf("method = %d\n", req_line->method);
    printf("path = ");
    print_string(&(req_line->path));
}

