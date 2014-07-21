#ifndef HTTP_REQ_PARSER_H
#define HTTP_REQ_PARSER_H

#include "my_string.h"

#define READ_LEN_ONCE 16 
#define METHOD_GET 1
#define METHOD_POST 2
struct st_req_line
{
    int method;
    My_string path;
    int version;
};
typedef struct st_req_line Req_line;
void print_req_line(Req_line* req_line);

Req_line get_req_line(int fd, My_string* read_buff);

struct st_header
{
    int header_name;
    My_string header_value;
};

typedef struct st_header Header;

struct st_Request
{
    Req_line req_line;
    My_string* headers;
    My_string body;
};

typedef struct st_Request Request;
void print_request(Request* request);

Header get_header(int fd, My_string* read_buff);

int read_line(int fd, My_string* read_buff, My_string* line);

int read_length(int fd, My_string* read_buff, My_string* out_line, int len);


int parse_request(int fd, My_string* read_buff, Request* request);

typedef int (*Request_callback)(int fd, Request* request) ;
int on_request(int fd, My_string* read_buff, Request_callback do_request);

int do_request(int fd, Request* request);

#endif
