
#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

struct parser_var {
   size_t key_sz;
   char* key;
   size_t value_sz;
   char* value;
};

void parser_template( char* buffer, size_t buffer_sz, struct parser_var* v );

#endif /* PARSER_H */

