/* parse.h */
#ifndef _PARSE_H_
#define _PARSE_H_

#include "value.h"

/* Parsing functions */
int parse_white(const wchar_t** code);
int parse_string(value* val, const wchar_t** code);
int parse_symbol(value* val, const wchar_t** code);
int parse_list(value* val, const wchar_t** code);
int parse_number(value* val, const wchar_t** code);
int parse_value(value* val, const wchar_t** code);

#endif /* _PARSE_H_ */