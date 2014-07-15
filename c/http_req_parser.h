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

Req_line get_req_line(int fd, My_string* read_buff);

struct st_header
{
    int header_name;
    My_string header_value;
};

typedef struct st_header Header;

Header get_header(int fd, My_string* read_buff);

int read_line(int fd, My_string* read_buff, My_string* line);


#endif
