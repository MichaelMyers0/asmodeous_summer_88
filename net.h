#ifndef NET_H
#define NET_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
/*const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;*/
/*s.sin6_family = AF_INET;*/
/*s.sin6_port = htons()*/
/*s.sin6_addr = in6addr_any*/
/*fill all thos fields manually*/
enum {client_port = 5000};
enum {server_port = 6000};
enum {buffer_cap = 1024};
enum {sleep_t = 10};
enum {log = 5};

create_socket(fd, domain, type);
bind_socket(fd, addr, slen);
connect_to_a_server(fd, addr, slen);
accept_connection(fd, sfd, addr, slen);
reuse_port(fd);
close_socket(fd);
make_socket_listening(fd, log);
#endif
