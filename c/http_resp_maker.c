#include "http_resp_maker.h"
#include <stdlib.h>
#include "my_string.h"
#include "http_protocol.h"

My_string* RESP_CODE[404];
void init_RESP_CODE()
{
    My_string* p_resp_code;
    RESP_CODE[200] = (My_string*)malloc(sizeof(My_string));
    p_resp_code = RESP_CODE[200];
    p_resp_code->buff = (Buff*)malloc(sizeof(Buff));
    p_resp_code->buff->buff_content = "200 OK";
    p_resp_code->buff->buff_len = 6;
    p_resp_code->start_index = 0;
    p_resp_code->end_index = 6;

    RESP_CODE[404] = (My_string*)malloc(sizeof(My_string));
    p_resp_code = RESP_CODE[404];
    p_resp_code->buff = (Buff*)malloc(sizeof(Buff));
    p_resp_code->buff->buff_content = "404 NOT FOUND";
    p_resp_code->buff->buff_len = 13;
    p_resp_code->start_index = 0;
    p_resp_code->end_index = 13;
}

void init_resp(Response *resp)
{
    resp->resp_code = 404;
    int i;
    resp->headers = (My_string*)malloc(sizeof(My_string) * HEADER_COUNT);
    for (i = 0; i < HEADER_COUNT; i++)
    {
        resp->headers[i].buff = NULL;
        resp->headers[i].start_index = 0;
        resp->headers[i].end_index = 0;
    }
    resp->body.buff = NULL;
    resp->body.start_index = 0;
    resp->body.end_index = 0;
}
    

void set_resp_code(Response *resp, int resp_code)
{
    resp->resp_code = resp_code;
}

void set_header(Response *resp, int header_index, My_string* header_value)
{
    My_string* p_header = resp->headers + header_index;
    p_header->buff = header_value->buff;
    p_header->start_index = header_value->start_index;
    p_header->end_index = header_value->end_index;
}

void set_body(Response *resp, My_string* body)
{
    My_string* p_body = &(resp->body);
    p_body->buff = body->buff;
    p_body->start_index = body->start_index;
    p_body->end_index = body->end_index;
}

void send_resp(int fd, Response* resp)
{
    write(fd, "HTTP/1.1 ", 9);
    My_string* resp_code_str = RESP_CODE[resp->resp_code];
    write(
            fd, 
            resp_code_str->buff->buff_content + resp_code_str->start_index,
            get_string_len(resp_code_str)
    );
    write(fd, "\r\n", 2);

    int i;
    for (i = 0; i < HEADER_COUNT; i++)
    {
        if (resp->headers[i].buff != NULL)
        {
            My_string* header_name = Headers[i];
            My_string* header_value = resp->headers + i;
            write(
                fd,
                header_name->buff->buff_content + header_name->start_index,
                get_string_len(header_name)
            );
            write(fd, ": ", 2);
            write(fd,
                header_value->buff->buff_content + header_value->start_index,
                get_string_len(header_value)
            );
            write(fd, "\r\n", 2);
        }
    }
    write(fd, "\r\n", 2);
    write(fd, 
            resp->body.buff->buff_content + resp->body.start_index,
            get_string_len(&(resp->body))
    );


}
