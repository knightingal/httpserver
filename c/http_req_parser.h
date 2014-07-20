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

#define CONTENT_LENGTH_INDEX 0

#define ACCEPT_LANGUAGE_INDEX 1

#define ACCEPT_ENCODING_INDEX 2

#define HOST_INDEX 3

#define ACCEPT_INDEX 4

#define USER_AGENG_INDEX 5

#define ACCPET_CHARSET_INDEX 6

#define CONNECTION_INDEX 7

#define CONTENT_TYPE_INDEX 8

#define HEADER_COUNT 9
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

int Headers_count;

int parse_request(int fd, My_string* read_buff, Request* request);

typedef int (*Request_callback)(int fd, Request* request) ;
int on_request(int fd, My_string* read_buff, Request_callback do_request);

int do_request(int fd, Request* request);

#endif
