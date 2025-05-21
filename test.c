#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>        // getcwd

#define BUFFER_SIZE 30

// int main() {

//     char buffer[BUFFER_SIZE];
//     if ( getcwd( buffer, BUFFER_SIZE ) == NULL ) {
//         fprintf( stderr, "Cannot get current working directory path\n" );
//         if ( errno == ERANGE ) {
//             fprintf( stderr, "Buffer size is too small.\n" );
//         }
//         exit( EXIT_FAILURE );
//     }

//     printf( "Current working directory: %s\n", buffer );
    
//     return EXIT_SUCCESS;
// }