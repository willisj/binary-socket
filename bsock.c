
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

int sockfd, newsockfd;

int bsock_listenTCP(int portno)
{
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		error("ERROR opening socket");
		return CONNECT_FAIL;
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	      sizeof(serv_addr)) < 0) {
	      fprintf( stderr, "%s: ERROR on binding", __func__);
	      return CONNECT_FAIL;
	}

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, 
		 (struct sockaddr *) &cli_addr, 
		 &clilen);

	if (newsockfd < 0) 
	  error("ERROR on accept");


	return CONNECT_SUCCESS;
}

int bsock_connectTCP(const char * ip, int portno)
{
	struct sockaddr_in serv_addr;
	struct hostent *server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		fprintf( stderr, "ERROR opening socket");

	server = gethostbyname(ip);
	if (server == NULL) {
		fprintf( stderr, "ERROR, no such host\n");
		return -1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		fprintf( stderr, "ERROR connecting");

	return CONNECT_SUCCESS;
}


int bsock_readTCP( uint8_t *bytes, uint32_t size)
{
	int n;
	n = read(newsockfd, bytes, size);
	if (n < 0) fprintf(stderr, "ERROR reading from socket");
	return n;
}

int bsock_writeTCP( uint8_t *bytes, uint32_t size)
{
     int n;
     n = write(sockfd, bytes, size);
     if (n < 0) fprintf(stderr, "ERROR writing to socket");
	return CONNECT_SUCCESS;
}


void bsock_closeTCP()
{
     close(newsockfd);
     close(sockfd);
}

