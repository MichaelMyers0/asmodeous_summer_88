CC=cc
CCFLAGS=-Wall -Wextra
net.o:net.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
client:client.c net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@
server:server.c net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@


