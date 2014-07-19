#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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

    return split_index;
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

int index_of_sub_string(My_string* str, My_string* sub)
{
    int str_len = get_string_len(str);
    int sub_len = get_string_len(sub);
    if (str_len < 0 || sub_len < 0 || str_len < sub_len)
    {
        return -1;
    }
    if (str->buff == sub->buff)
    {
        if (sub->start_index >= str->start_index
                && sub->end_index <= str->end_index)
        {
            return sub->start_index - str->start_index;
        }
        else
        {
            return -1;
        }
    }
    int i;
    int j;
    for (i = str->start_index; i != str->end_index; i++)
    {
        for (j = sub->start_index; j != sub->end_index; j++)
        {
            if (sub->buff->buff_content[j] 
                    != str->buff->buff_content[i + j - sub->start_index])
            {
                break;
            }
        }
        if (j == sub->end_index)
        {
            return i - str->start_index;
        }
    }
    return -1;
}

int append_str(My_string* str1, My_string* str2, My_string* ret)
{
    int len1 = get_string_len(str1);
    int len2 = get_string_len(str2);
    if (ret == NULL || ret->buff == NULL || ret->buff->buff_content == NULL)
    {
        return -1;
    }
    if (len1 < 0 || len2 < 0 || len1 + len2 == 0) return -1;
    if (len1 + len2 > ret->buff->buff_len) return -1;
    //char* buff_content = (char*)malloc(sizeof(char) * (len1 + len2));
    //Buff* buff = (Buff*)malloc(sizeof(Buff));
    //buff->buff_content = buff_content;
    //buff->buff_len = len1 + len2;
    //buff->refered = 0;
    char* buff_content = ret->buff->buff_content;
    memcpy(buff_content, str1->buff->buff_content + str1->start_index, len1);
    memcpy(buff_content + len1, str2->buff->buff_content + str2->start_index, len2);
    //str1->buff = buff;
    ret->start_index = 0;
    ret->end_index = len1 + len2;
    return 0;

}


int string_to_int(My_string* str, int* output)
{
    int ret = 0;
    int index;
    for (index = str->start_index; index != str->end_index; index++)
    {
        if (str->buff->buff_content[index] > '9' ||
                str->buff->buff_content[index] < '0')
        {
            return -1;
        }
        ret = ret * 10 + str->buff->buff_content[index] - '0';
    }
    *output = ret;
    return 0;

}
#if 0
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

    Buff buff2 = {"1234567890", 10};
    My_string child_str = {&buff2, 8, 10};
    print_string(&child_str);
    printf("sub index = %d\n", index_of_sub_string(&parent_str, &child_str));

    append_str(&parent_str, &child_str);
    print_string(&parent_str);
    return 0;
}
    
#endif
