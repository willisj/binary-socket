
#include "bsock.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int rcvFd;
uint8_t role = ROLE_UNDEFINED;

int bsock_listenTCP(int portno)
{	
	int serverFd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	rcvFd = socket(AF_INET, SOCK_STREAM, 0);

	if (rcvFd < 0){
		error("ERROR opening socket\n");
		return CONNECT_FAIL;
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(rcvFd, (struct sockaddr *) &serv_addr,
	      sizeof(serv_addr)) < 0) {
	      fprintf( stderr, "%s: ERROR on binding\n", __func__);
	      return CONNECT_FAIL;
	}

	listen(rcvFd,5);
	clilen = sizeof(cli_addr);

	rcvFd = accept(rcvFd, 
		 (struct sockaddr *) &cli_addr, 
		 &clilen);

	if (rcvFd < 0) 
	  error("ERROR on accept");

	close(serverFd);
	role = ROLE_SERVER;
	return CONNECT_SUCCESS;
}

int bsock_connectTCP(const char * ip, int portno)
{
	struct sockaddr_in serv_addr;
	struct hostent *server;

	rcvFd = socket(AF_INET, SOCK_STREAM, 0);
	if (rcvFd < 0) 
		fprintf( stderr, "ERROR opening socket\n");

	server = gethostbyname(ip);
	if (server == NULL) {
		fprintf( stderr, "ERROR, no such host\n");
		return CONNECT_FAIL;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = htons(portno);
	if ( connect(rcvFd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		fprintf( stderr, "ERROR connecting\n");

	role = ROLE_CLIENT;
	return CONNECT_SUCCESS;
}

int bsock_readTCP( uint8_t *bytes, uint32_t size)
{
	int n;
	n = read(rcvFd, bytes, size);
	if (n < 0) fprintf(stderr, "ERROR reading from socket\n");

	return n;
}

int bsock_writeTCP( uint8_t *bytes, uint32_t size)
{
	int n;
	n = write(rcvFd, bytes, size);
	if (n < 0) fprintf(stderr, "ERROR writing to socket\n");

	return CONNECT_SUCCESS;
}


void bsock_closeTCP()
{
     close(rcvFd);
}

