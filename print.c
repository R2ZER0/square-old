/* print.c */

#include "print.h"

void fprintvalue(FILE* file, value* val) {
        if(val->type == VALUE_NULL) {
                fprintf(file, "null");
                
        } else if(val->type == VALUE_STRING) {
                fprintf(file, "\"%ls\"", val->string);
                
        } else if(val->type == VALUE_SYMBOL) {
                fprintf(file, "%ls", val->string);
                
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