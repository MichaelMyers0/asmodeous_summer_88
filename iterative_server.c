#include "net.h"

main(argc, argv)
int argc;
char** argv;
{
	int sfd, iter, fd;
	struct sockaddr_in6 s;
	const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
	socklen_t slen;
	char buf[buffer_cap];
	ssize_t cnt;
	s.sin6_family = AF_INET6;
	s.sin6_port = htons(server_port);
	s.sin6_addr = in6addr_any;
	if (argc < 2)
	{
		fprintf(stderr, "ERROR: Provide number of clients to server\n");
		exit(1);
	}
	create_socket(&sfd, AF_INET6, SOCK_STREAM);
	slen = sizeof(s);
	bind_socket(sfd, (const struct sockaddr*)&s, slen);
	make_socket_listening(sfd, log);
	sleep(sleep_t);
	for (iter = 0; iter < *(argv + 1)[0] - '0'; iter++)	
	{
		accept_connection(&fd, sfd, NULL, NULL);
		errno = 0;
		cnt = read(fd, buf, buffer_cap);
		if (cnt == -1)
		{
			perror("ERROR: server failed to read a message\n");
			break;
		}
		if (cnt)
		{
			*(buf + cnt) = 0;
			printf("%s\n", buf);
			*buf = 0;
			close(fd);
		}
	}
	reuse_port(sfd);
	close_socket(sfd);
	_exit(0);
}
