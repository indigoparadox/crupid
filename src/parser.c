
#include "parser.h"

#include "bstrlib/bstrlib.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

bstring parser_get_var( const bstring key, struct parser_var* vars ) {
   struct parser_var* iter = vars;

   while( NULL != iter ) {
      
      if( 0 == bstricmp( key, iter->key ) ) {
         return iter->value;
      }

      /* Move on. */
      iter = iter->next;
   }

   return NULL;
}

void parser_set_var(
   const bstring key, const bstring value, struct parser_var** vars
) {
   struct parser_var* iter = *vars;

   if( NULL == iter ) {
      *vars = calloc( 1, sizeof( struct parser_var ) );
      assert( NULL != *vars );
      iter = *vars;
   }

   /* Cycle through the list until we find an empty spot. */
   while( NULL != iter->next ) {
      iter = iter->next;
   }

   iter->next = calloc( 1, sizeof( struct parser_var ) );
   assert( NULL != iter->next );
   iter = iter->next;

   iter->key = bstrcpy( key );
   assert( NULL != iter->key );

   iter->value = bstrcpy( value );
   assert( NULL != iter->value );
}

void parser_template( bstring buf, struct parser_var* vars ) {
   
}

