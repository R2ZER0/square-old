/* parse.c */

#include "parse.h"
#include <stdlib.h>
#include <wctype.h>
#include <string.h>

int parse_white(const wchar_t** code)
{
        while( iswspace(**code) ) { ++(*code); }
        return 1;
}

int parse_string(value* val, const wchar_t** code)
{
        const wchar_t* c = *code;
        
        if(*c != '"') return 0;
        ++c;
        
        /* First we need the length of the string */
        const wchar_t* string_start = c;
        
        int len = 0;
        while(*c != '"') {
                if(*c == '\0') { return 0; } /* Fail if End-of-Code */
                ++c;
                ++len;
        }
        
        /* Allocate a copy */
        wchar_t* strval = (wchar_t*) calloc(len+1, sizeof(wchar_t));
        
        /* Make the copy */
        int i = 0;
        while(i < len) {
                strval[i] = string_start[i];
                ++i;
        }
        
        /* Fast-forward over last " */
        ++c;
        
        /* Setup the value */
        val->type = VALUE_STRING;
        val->string = strval;
        
        *code = c;
        return 1;
}

int parse_symbol(value* val, const wchar_t** code)
{
        /* Must start with alpha character */
        if(!iswalpha(**code)) { return 0; }
        
        const wchar_t* c = *code;
        
        /* Get string length */
        int len = 0;
        while(!iswspace(*c) && *c != '\0' && !iswpunct(*c)) {
                ++c;
                ++len;
        }
        
        /* Allocate copy */
        wchar_t* strval = (wchar_t*) calloc(len+1, sizeof(wchar_t));
        
        /* Make the copy */
        int i = 0;
        while(i < len) {
                strval[i] = (*code)[i];
                ++i;
        }
        
        /* Setup value */
        val->type = VALUE_SYMBOL;
        val->string = strval;
        
        *code = c;
        
        return 1;
}

int parse_list(value* val, const wchar_t** code)
{
        /* Must start with [ */
        if(**code != L'[') { return 0; }
        
        const wchar_t* c = *code;
        ++c; /* Skip '[' */
        
        /* Create list */
        value* tval = alloc_val();
        value* tval_start = tval;
        
        while(*c != L']') {                
                if(*c == L'\0') { return 0; } /* Fail if End-of-Code */
                
                parse_white(&c);
                
                tval->next = alloc_val();
                tval = tval->next;
                
                int result = parse_symbol(tval, &c);
                if(!result) { return 0; }
                
                parse_white(&c);
        }
        
        ++c; /* Skip ']' */
        
        /* Setup value */
        val->type = VALUE_LIST;
        val->list_first = tval_start->next;
        
        *code = c;
        
        return 1;
}