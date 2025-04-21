#include "net.h"

main(argc, argv)
int argc;
char** argv;
{
	int cfd;
	struct sockaddr_in6 s, s2;
	const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
	socklen_t slen;
	ssize_t cnt;
	size_t len;
	s.sin6_family = AF_INET6;
	s.sin6_port = htons(client_port);
	s.sin6_addr = in6addr_any;
	if (argc < 2)
	{
		fprintf(stderr, "ERROR: Provide user name\n");
		exit(1);
	}
	create_socket(&cfd, AF_INET6, SOCK_STREAM);
	slen = sizeof(s);
	bind_socket(cfd, (const struct sockaddr*)&s, slen);
	s2.sin6_family = AF_INET6;
	s2.sin6_port = htons(server_port);
	s2.sin6_addr = in6addr_any;
	slen = sizeof(s2);
	connect_to_a_server(cfd, (const struct sockaddr*)&s2, slen);
	len = strlen(*(argv + 1));
	for (;;)
	{
		errno = 0;
		cnt = write(cfd, *(argv + 1), len);
		if (cnt == -1)
		{
			perror("client failed to write a message\n");
			break;
		}
		if (cnt)
			break;
	}
	reuse_port(cfd);
	close_socket(cfd);
	_exit(0);
}
