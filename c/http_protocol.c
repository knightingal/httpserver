#include "http_protocol.h"

Buff CONTENT_LENGTH_BUFF =      {"Content-Length", 14, 0}; 
My_string CONTENT_LENGTH_STR = {&CONTENT_LENGTH_BUFF, 0, 14};

Buff ACCEPT_LANGUAGE_BUFF =     {"Accept-Language", 15, 0}; 
My_string ACCEPT_LANGUAGE_STR = {&ACCEPT_LANGUAGE_BUFF, 0, 15};

Buff ACCEPT_ENCODING_BUFF =     {"Accept-Encoding", 15, 0};
My_string ACCEPT_ENCODING_STR = {&ACCEPT_ENCODING_BUFF, 0, 15};

Buff HOST_BUFF =                {"Host", 4, 0};
My_string HOST_STR = {&HOST_BUFF, 0, 4};

Buff ACCEPT_BUFF =              {"Accept", 6, 0};
My_string ACCEPT_STR = {&ACCEPT_BUFF, 0, 6};

Buff USER_AGENG_BUFF =          {"User-Agent", 10, 0};
My_string USER_AGENG_STR = {&USER_AGENG_BUFF, 0, 10};

Buff ACCPET_CHARSET_BUFF =      {"Accept-Charset", 14, 0};
My_string ACCPET_CHARSET_STR = {&ACCPET_CHARSET_BUFF, 0, 14};

Buff CONNECTION_BUFF =          {"Connection", 10, 0};
My_string CONNECTION_STR = {&CONNECTION_BUFF, 0, 10};

Buff CONTENT_TYPE_BUFF =        {"Content-Type", 12, 0};
My_string CONTENT_TYPE_STR = {&CONTENT_TYPE_BUFF, 0, 12};

My_string* Headers[] = {
    &CONTENT_LENGTH_STR,    
    &ACCEPT_LANGUAGE_STR, 
    &ACCEPT_ENCODING_STR, 
    &HOST_STR, 
    &ACCEPT_STR,
    &USER_AGENG_STR, 
    &ACCPET_CHARSET_STR, 
    &CONNECTION_STR, 
    &CONTENT_TYPE_STR
};
