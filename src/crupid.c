
#include "crupid.h"
#include "parser.h"

#include <fcgi_stdio.h>

#define BUFFER_SZ 4096

int main( int argc, char** argv ) {
   FILE* f_template = NULL;
   char buffer[BUFFER_SZ + 1] = { 0 };

   while( 0 >= FCGI_Accept() ) {

      f_template = fopen( "templates/index.html", "r" );
      if( NULL == f_template ) {
         FCGI_printf( "HTTP/1.0 404 Not Found\r\n" );
         FCGI_printf( "Content-type: text/html\r\n\r\n" );
         continue;
      }

      FCGI_printf( "HTTP/1.0 200 OK\r\n" );
      FCGI_printf( "Content-type: text/html\r\n\r\n" );
      while( 0 != fread( buffer, 1, BUFFER_SZ, f_template ) ) {
         FCGI_printf( "%s", buffer );
      }

      fclose( f_template );
   }

   return 0;
}

