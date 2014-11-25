/* value.h */
#ifndef _VALUE_H_
#define _VALUE_H_

#include <stddef.h>
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

#endif /* _VALUE_H_ */