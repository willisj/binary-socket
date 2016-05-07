


all: examples

build_dirs:
	mkdir -p bin

bsock.o: bsock.c bsock.h
	gcc -c bsock.c 

examples: build_dirs bsock.o
	gcc -o bin/server example-server.c bsock.o
	gcc -o bin/client example-client.c bsock.o

clean:
	rm *.o&
	rm bin -r&
	@wait
