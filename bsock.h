#include <stdint.h>

#define CONNECT_SUCCESS 1
#define CONNECT_FAIL 	0

int bsock_listenTCP(int portno);
int bsock_connectTCP(const char * ip, int portno);
int bsock_readTCP( uint8_t *bytes, uint32_t size);
int bsock_writeTCP( uint8_t *bytes, uint32_t size);
void bsock_closeTCP();
