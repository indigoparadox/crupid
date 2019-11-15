
#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <sys/types.h>

#include "bstrlib/bstrlib.h"

struct parser_var {
   bstring key;
   bstring value;
   struct parser_var* next;
};

bstring parser_get_var( const bstring key, struct parser_var* vars );
void parser_set_var(
   const bstring key, const bstring value, struct parser_var** vars );
void parser_template( bstring buf, struct parser_var* vars );

#endif /* PARSER_H */

