#include <string.h>
#include <stdio.h>
#include "bsock.h"

int main(int argc, char * argv[]){
	char buffer[255];
	char *message = "server message";
	size_t sz = strlen( message ) + 1; // +1 for null char

	if( CONNECT_FAIL ==  bsock_listenTCP(5340) )
		return 0;

	while( 1 ){
		if( bsock_readTCP( buffer, 255) > 0 )
			printf("%s\n", buffer);
		if(  bsock_writeTCP( message, sz ) > 0 )
			printf("Sent packet\n");
		sleep(1);
	}

	bsock_closeTCP();

	return 0;
}
