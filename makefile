CC=cc
CCFLAGS=-Wall -Wextra
net.o:net.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
db.o:db.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@	
client:client.c net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@
dbd:dbd.c net.o db.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@	


