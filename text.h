/* text.h */
#ifndef _TEXT_H_
#define _TEXT_H_

#include <stdint.h>

enum text_flags {
        TEXT_COMPACT = 1,
        TEXT_DUPCHECK = 2
};

typedef struct text text;
struct text {
        struct textnode* node;
        uint32_t size;
        uint32_t length;
        char* utf8string;
};

void text_initheap(void* heap, uint32_t size);
text* text_new(uint32_t size, uint16_t flags);
text* text_createz(const char* utf8str);
text* text_clone(text* txt);
uint32_t text_strlen(text* txt);

#endif /* _TEXT_H_ */