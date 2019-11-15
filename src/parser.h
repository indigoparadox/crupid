
#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <sys/types.h>

struct parser_var {
   ssize_t key_sz;
   char* key;
   ssize_t value_sz;
   char* value;
   struct parser_var* next;
};

char* parser_get_var( char* k, ssize_t k_sz, struct parser_var* vars );
void parser_set_var(
   char* k, ssize_t k_sz, char* v, ssize_t v_sz, struct parser_var** vars
);
void parser_template( char** buf, ssize_t* buffer_sz, struct parser_var* vars );

#endif /* PARSER_H */

