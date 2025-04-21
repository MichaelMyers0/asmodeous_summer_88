CC=cc
CCFLAGS=-Wall -Wextra
net.o:net.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
client:client.c net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@
iterative_server:iterative_server.c net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@


