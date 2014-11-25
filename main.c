/* main.c */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <wctype.h>
#include <string.h>
#include <wchar.h>

enum value_type {
        VALUE_NULL,
        VALUE_SYMBOL,
        VALUE_STRING,
        VALUE_NUMBER,
        VALUE_LIST
};

typedef struct value value;
struct value {
        enum value_type type;
        value* next; /* The next value in a list */
        
        /* String/Symbol Type */
        const wchar_t* string;
        
        /* Number Type */
        double number;
        
        /* List Type */
        value* list_first;
};

/* Value management functions */
value* alloc_val(void);
void clone_val(value* dest, value* src);

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

/* Parsing functions */
int parse_white(const wchar_t** code);
int parse_string(value* val, const wchar_t** code);
int parse_symbol(value* val, const wchar_t** code);
int parse_list(value* val, const wchar_t** code);
int parse_number(value* val, const wchar_t** code);
int parse_value(value* val, const wchar_t** code);

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

void fprintvalue(FILE* file, value* val);
/* Print a tree of Values */
void fprintvalue(FILE* file, value* val) {
        if(val->type == VALUE_NULL) {
                fprintf(file, "null");
                
        } else if(val->type == VALUE_STRING) {
                fprintf(file, "\"%ls\"", val->string);
                
        } else if(val->type == VALUE_LIST) {
                fprintf(file, "[");
                value* arrval = val->list_first;
                while(arrval) {
                        fprintvalue(file, arrval);
                        if(arrval->next) { fprintf(file, " "); }
                        arrval = arrval->next;
                }
                fprintf(file, "]");
                
        } else {
                fprintf(file, "%ls", L"«unknown»");
        }
}


int main(int argc, char** argv)
{
        printf("sizeof(wchar_t) = %lu\n", sizeof(wchar_t));
        
        FILE* test = fopen("test.sqr", "r");
        if(test == NULL) {
                fprintf(stderr, "Couldn't open test.sqr\n");
                return 0;
        }
        
        fseek(test, 0L, SEEK_END);
        long int size = ftell(test)+2;
        fseek(test, 0L, SEEK_SET);
        
        wchar_t* program = (wchar_t*) malloc((size+1)*(sizeof(wchar_t)/sizeof(char)));
        program[size] = L'\0';
        program[size+1] = WEOF;
        
        char* program_raw = (char*) malloc((size+1)*sizeof(char));
        program_raw[size] = '\0';
        
        fread(program_raw, 1, size, test);
        swprintf(program, size, L"%s", program_raw);
        
        fclose(test);
        free(program_raw);
        program_raw = NULL;
        
        printf("Program: %ls \n", program);
        
        value* root_val = alloc_val();
        const wchar_t* programptr = (const wchar_t*) program;
        int result = parse_list(root_val, &programptr);
        
        if(!result) {
                fprintf(stderr, "parse failed\n");
        } else {
                fprintvalue(stdout, root_val);
        }
        
        return 0;
}