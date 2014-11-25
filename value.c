/* value.c */

#include "value.h"
#include <stdlib.h>

value* alloc_val(void)
{
        value* val = calloc(1, sizeof(value));
        val->type = VALUE_NULL;
        val->next = NULL;
        return val;
}

void clone_val(value* dest, value* src)
{
        dest->type = src->type;
        dest->next = src->next;
        if(src->type == VALUE_STRING) {
                dest->string = src->string;
                
        } else if(src->type == VALUE_NUMBER) {
                dest->number = src->number;
                
        } else if(src->type == VALUE_LIST) {
                dest->list_first = src->list_first;
                
        }
}