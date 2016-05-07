
#include <stdio.h>
#include "bsock.h"

int main(int argc, char * argv[]){
	char buffer[255];

	if( CONNECT_SUCCESS ) bsock_listenTCP(5340);

	while( 1 ){
		if( bsock_readTCP( buffer, 255) > 0 )
			printf("%s\n", buffer);
	}

	bsock_closeTCP();

	return 0;
}
