
#include "crupid.h"
#include "parser.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <fcgi_stdio.h>

#define BUFFER_SZ 4096
#define CHUNK_SZ 512

int main( int argc, char** argv ) {
   FILE* f_template = NULL;
   char* buffer = NULL;
   char* new_buffer = NULL;
   ssize_t buffer_sz = BUFFER_SZ;
   ssize_t buffer_idx = 0;
   struct parser_var* vars = NULL;
   struct parser_var* iter = NULL;

   buffer = calloc( buffer_sz, 1 );
   assert( NULL != buffer );

   while( 0 >= FCGI_Accept() ) {

      f_template = fopen( "templates/index.html", "r" );
      if( NULL == f_template ) {
         FCGI_printf( "HTTP/1.0 404 Not Found\r\n" );
         FCGI_printf( "Content-type: text/html\r\n\r\n" );
         continue;
      }

      FCGI_printf( "HTTP/1.0 200 OK\r\n" );
      FCGI_printf( "Content-type: text/html\r\n\r\n" );

      /* TODO: Call hooks. */

      /* Read and process the template. */
      while( 0 < fread( &(buffer[buffer_idx]), 1, CHUNK_SZ, f_template ) ) {
         /* Safely try to realloc buffer if it's full (or will be soon). */
         if( buffer_idx + CHUNK_SZ >= buffer_sz ) {
            /* fprintf( stderr, "Buffer %d bytes; resizing to %d bytes.",
               buffer_sz, (buffer_sz * 2) ); */
            assert( buffer_sz < (buffer_sz * 2) );
            new_buffer = realloc( buffer, buffer_sz * 2 );
            assert( NULL != new_buffer );
            buffer = new_buffer;
            buffer_sz *= 2;
         }
      }

      parser_set_var( "test", 5, "Test string.", 13, &vars );
      parser_template( &buffer, &buffer_sz, vars );

      /* Clean up vars for next request. */
      iter = vars;
      while( NULL != vars ) {
         iter = vars;
         vars = vars->next;
         free( iter->key );
         free( iter->value );
         free( iter );
      }

      fclose( f_template );

      FCGI_printf( "%s", buffer );
   }

   free( buffer );

   return 0;
}

