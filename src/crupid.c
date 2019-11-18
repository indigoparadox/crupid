
#include "crupid.h"
#include "parser.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <fcgi_stdio.h>

#define BUFFER_SZ 4096
#define CHUNK_SZ 512

struct tagbstring test_k = bsStatic( "test" );
struct tagbstring test_v = bsStatic( "This is a test var." );

struct tagbstring title_k = bsStatic( "title" );
struct tagbstring title_v = bsStatic( "This is a title var." );

int main( int argc, char** argv ) {
   FILE* f_template = NULL;
   bstring buffer = NULL;
   struct parser_var* vars = NULL;
   struct parser_var* iter = NULL;
   int bres = 0;

   buffer = bfromcstr( "" );

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
      btrunc( buffer, 0 );
      bres = breada( buffer, (bNread)fread, f_template );
      assert( BSTR_OK == bres );

      parser_set_var( &test_k, &test_v, &vars );
      parser_set_var( &title_k, &title_v, &vars );
      parser_template( buffer, vars );

      /* Clean up vars for next request. */
      iter = vars;
      while( NULL != vars ) {
         iter = vars;
         vars = vars->next;
         assert( NULL != iter->key );
         assert( NULL != iter->value );
         bdestroy( iter->key );
         bdestroy( iter->value );
         free( iter );
      }

      fclose( f_template );

      FCGI_printf( "%s", bdata( buffer ) );
   }

   free( buffer );

   return 0;
}

