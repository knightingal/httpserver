#include "http_req_parser.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>


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

Req_line get_req_line(int fd, My_string* read_buff)
{
    Req_line req_line;
    req_line.method = 0;
    My_string req_str;
    read_line(fd, read_buff, &req_str);
    
    My_string method_str, path_str, version_str;
    int split_index = split_string(read_buff, &method_str, &path_str, ' ');
    if (split_index < 0)
    {
        return req_line;
    }
    read_buff->start_index += split_index + 1;
    split_index = split_string(read_buff, &path_str, &version_str, ' ');
    if (split_index < 0)
    {
        return req_line;
    }
    version_str.start_index += 1;

    if (cmp_string(method_str, &POST_STR) == 0)
    {
        req_line.method = METHOD_POST;
    }
    else if (cmp_string(method_str, &GET_STR) == 0)
    {
        req_line.method = METHOD_GET;
    }
    else
    {
        return req_line;
    }


    //to be continue
    return req_line;
}
    



    
