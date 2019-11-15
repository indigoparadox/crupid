
#include "parser.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

char* parser_get_var( char* k, ssize_t k_sz, struct parser_var* vars ) {
   struct parser_var* iter = vars;

   while( NULL != iter ) {
      
      if( 0 == strncmp( k, iter->key, iter->key_sz ) ) {
         return iter->value;
      }

      /* Move on. */
      iter = iter->next;
   }

   return NULL;
}

void parser_set_var(
   char* k, ssize_t k_sz, char* v, ssize_t v_sz, struct parser_var** vars
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

   iter->key_sz = k_sz;
   iter->key = calloc( 1, iter->key_sz );
   assert( NULL != iter->key );
   memcpy( iter->key, k, iter->key_sz );

   iter->value_sz = v_sz;
   iter->value = calloc( 1, iter->value_sz );
   assert( NULL != iter->value );
   memcpy( iter->value, v, iter->value_sz );
}

void parser_template( char** buf, ssize_t* buf_sz, struct parser_var* vars ) {
   
}

