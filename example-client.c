#include <string.h>
#include <stdio.h>
#include "bsock.h"

int main(int argc, char * argv[]){
	char * buffer = "This is a message";
	size_t sz = strlen(buffer) + 1; // +1 for null char

	if( CONNECT_SUCCESS ) bsock_connectTCP( "localhost", 5340);
	
	while ( 1 ){
		if(  bsock_writeTCP( buffer, sz ) > 0 )
			printf("Sent packet\n");
		sleep(1);
	}

	bsock_closeTCP();

	return 0;
}
