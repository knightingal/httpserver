struct ST_Buff
{
    char* buff_content;
    int buff_len;
    int refered;
};

typedef struct ST_Buff Buff;

struct ST_My_string
{
    Buff *buff;
    int start_index;
    int end_index;
};

typedef struct ST_My_string My_string;

int cmp_string(My_string* str1, My_string* str2);

void cpy_string_from_char(My_string* dst, char* src, int len);

int cpy_string_from_string(My_string* dst, My_string* src, int start, int end);

int verify_string(My_string* str);

int get_string_len(My_string* str);

char get_char_of_index(My_string* str, int index);

int find_char_in_string(My_string* str, char ch);
