#ifndef HTTP_RESP_MAKER_H
#define HTTP_RESP_MAKER_H
#include "my_string.h"
#include "http_protocol.h"

typedef struct
{
    int resp_code;
    My_string* headers;
    My_string body;
} Response;

void init_resp(Response *resp);

void set_resp_code(Response *resp, int resp_code);

void set_header(Response *resp, int header_index, My_string* header_value);

void set_body(Response *resp, My_string* body);

void send_resp(int fd, Response* resp);
#endif
