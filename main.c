/* main.c */

#include <stdlib.h>
#include <stddef.h>
#include <wctype.h>

enum value_type {
        VALUE_NULL,
        VALUE_STRING,
        VALUE_NUMBER,
        VALUE_LIST
};

wchar_t a;

typedef struct value value;
struct value {
        enum value_type type;
        value* next;
        
        union {
                const wint_t* string;
                double number;
                value* list_first;
        };
};

value* alloc_val()
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
                dest->array_first = src->array_first;
                
        }
}

/* Parsing functions */
int parse_white(const wint_t** code);
int parse_string(value* val, const wint_t** code);
int parse_ident(value* val, const wint_t** code);
int parse_list(value* val, const wint_t** code);
int parse_number(value* val, const wint_t** code);
int parse_value(value* val, const wint_t** code);

int parse_white(const wint_t** code)
{
        while( iswspace(**code) ) { ++(*code); }
        return 1;
}

int parse_string(value* val, const wint_t** code)
{
        const wint_t* c = *code;
        
        if(*c != '"') return 0;
        ++c;
        
        /* First we need the length of the string */
        const wint_t* string_start = c;
        
        int len = 0;
        while(*c != '"') {
                if(*c == '\0') { return 0; } /* Fail if End-of-Code */
                ++c;
                ++len;
        }
        
        /* Allocate a copy */
        const wint_t* strval = (const wint_t*) calloc(len+1, sizeof(wint_t));
        
        /* Make the copy */
        while(len > 0) {
                strval[len] = string_start[len];
                --len;
        }
        
        /* Fast-forward over last " */
        ++c;
        
        /* Setup the value */
        val->type = VALUE_STRING;
        val->string = strval;
        
        *code = c;
        return 1;
}

int parse_ident(value* val, const wint_t** code)
{
        /* Must start with alpha character */
        if(!iswalpha(**code)) { return 0; }
        
        const wint_t* c = *code;
        
        /* Get string length */
        int len = 0;
        while(!iswspace(*c) && *c != '\0') {
                ++c;
                ++len;
        }
        
        /* Allocate copy */
        const wint_t* strval = (const wint_t*) calloc(len+1, sizeof(wint_t));
        
        /* Make the copy */
        while(len > 0) {
                strval[len] = code[len];
                --len;
        }
        
        /* Setup value */
        val->type = VALUE_STRING;
        val->string = strval;
        
        *code = c;
        
        return 1;
}

int parse_list(value* val, const wint_t** code)
{
        /* Must start with [ */
        if(**code != '[') { return 0; }
        
        const wint_t* c = *code;
        ++c; /* Skip '[' */
        
        /* Create list */
        value* tval = alloc_val();
        value* tval_start = tval;
        
        while(*c != ']') {
                if(*c == '\0') { return 0; } /* Fail if End-of-Code */
                
                parse_white(&c);
                
                tval->next = alloc_val();
                tval = tval->next;
                
                int result = parse_ident(&c, tval);
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