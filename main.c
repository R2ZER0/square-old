/* main.c */

#include <stdlib.h>
#include <stdio.h>

#include "value.h"
#include "parse.h"
#include "print.h"

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