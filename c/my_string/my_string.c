#include "my_string.h"
#include <stdio.h>

int cmp_string(My_string* str1, My_string* str2)
{
    int len1 = get_string_len(str1);
    int len2 = get_string_len(str2);
    if (len1 < 0 || len2 < 0)
    {
        return -1;
    }
    if (len1 == len2) 
    {
        int i;
        for (i = 0; i < len1; i++)
        {
            char char1 = get_char_of_index(str1, i);
            char char2 = get_char_of_index(str2, i);
            if (char1 != char2)
            {
                return char1 < char2 ? 1 : 2;
            }
        }
        return 0;
    }
    return len1 < len2 ? 1 : 2;
}

int get_string_len(My_string* str)
{
    if (verify_string(str) != 0) return -1;
    return str->end_index - str->start_index;
}

char get_char_of_index(My_string* str, int index)
{
    if (verify_string(str) != 0) return '\0';
    if (index >= get_string_len(str) || index < 0) return '\0';
    return str->buff->buff_content[str->start_index + index];
}

int verify_string(My_string* str)
{
    if (str == NULL)
    {
        return -1;
    }
    if (str->buff == NULL || str->buff->buff_content == NULL)
    {
        return -1;
    }
    if (str->end_index < str->start_index) 
    {
        return -1;
    }
    if (str->end_index > str->buff->buff_len)
    {
        return -1;
    }
    if (str->start_index > str->buff->buff_len)
    {
        return -1;
    }
    if (str->start_index < 0)
    {
        return -1;
    }
    return 0;
}

int cpy_string_from_string(My_string* dst, My_string* src, int start, int end)
{
    if (dst == NULL) return -1;
    if (verify_string(src) != 0) return -1;
    if (end < start || start < 0 || end > get_string_len(src))
    {
        return -1;
    }
    dst->buff = src->buff;
    dst->start_index = src->start_index + start;
    dst->end_index = src->start_index + end;
    return 0;
}


int find_char_in_string(My_string* str, char ch)
{
    int len = get_string_len(str);
    if (len < 0) return -1;

    int index;
    for(index = 0; index != len; index++)
    {
        if (str->buff->buff_content[str->start_index + index] == ch)
        return index;
    }
    return -1;
}

int split_string(My_string* str, My_string* frt, My_string* bck, char ch)
{
    if (frt == NULL || bck == NULL) return -1;
    int split_index = find_char_in_string(str, ch);
    if (split_index < 0) return -1;
    
    frt->buff = str->buff;
    frt->start_index = str->start_index;
    frt->end_index = str->start_index + split_index;

    bck->buff = str->buff;
    bck->start_index = str->start_index + split_index;
    bck->end_index = str->end_index;

    return 0;
}

void print_string(My_string* str)
{
    if (verify_string(str) != 0) return;
    int i;
    for(i = str->start_index; i != str->end_index; i++)
    {
        printf("%c", str->buff->buff_content[i]);
    }
    printf("\n");
}

int main()
{
    Buff buff1= {"0123456789", 10};
    My_string parent_str = {&buff1, 2, 10};

    My_string frt, bck;

    int split_ret = split_string(&parent_str, &frt, &bck, 'a');


    print_string(&parent_str);    

    if (split_ret == 0)
    {
        print_string(&frt);
        print_string(&bck);
    }
    return 0;
}
    
