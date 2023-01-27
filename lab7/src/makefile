CFLAGS=-I. -std=c11 -pthread

all: tcp udp server client

tcp: tcpclient tcpserver

udp: udpclient udpserver

tcpserver: tcpserver.c
	gcc tcpserver.c -o tcpserver.o

tcpclient: tcpclient.c
	gcc tcpclient.c -o tcpclient.o

udpserver: udpserver.c
	gcc udpserver.c -o udpserver.o

udpclient: udpclient.c
	gcc udpclient.c -o udpclient.o

server: server.c
	gcc -o server server.c $(CFLAGS)

client: client.c
	gcc -o client client.c $(CFLAGS)

clean:
	rm *.o	client server