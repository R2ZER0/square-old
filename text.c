/* text.c - UTF8 String handling */

#include <stdint.h>
#include "utf8.h"
#include "text.h"

struct textnode;
struct textnode {
        struct textnode* next;
        uint16_t refs;
        uint16_t flags;
        uint32_t size;
        char data[];
};

/* such hax */
struct textnode* textheap;

void text_initheap(void* heap, uint32_t size)
{
        textheap = heap;
        textheap->next = NULL;
        textheap->refs = 0;
        textheap->size = size;
        textheap->data[0] = '\0';
}

text* text_new(uint32_t size, uint16_t flags)
{
        if(flags & TEXT_COMPACT) {
                /* Place this into a compact buffer */
        }
        return NULL;
}


text* text_createz(const char* utf8str)
{
        return NULL;
}

text* text_clone(text* txt)
{
        return NULL;
}

uint32_t text_strlen(text* txt)
{
        return txt->length;
}