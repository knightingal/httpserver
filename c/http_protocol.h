#ifndef HTTP_PROTOCOL_H
#define HTTP_PROTOCOL_H

#include "my_string.h"

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

My_string* Headers[HEADER_COUNT];

#endif
