#include "net.h"
#include "db.h"
static char in_buf[buffer_cap];
main(argc, argv)
int argc;
char** argv;
{
	int sfd, iter, fd, pos = 0;
	struct sockaddr_in6 s;
	const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
	socklen_t slen;
	char buf[buffer_cap];
	ssize_t cnt;
	s.sin6_family = AF_INET6;
	s.sin6_port = htons(server_port);
	s.sin6_addr = in6addr_any;
	if (argc < 3)
	{
		fprintf(stderr, "ERROR: Provide arguments\n");
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
			strcpy(in_buf, buf);
			*(in_buf + cnt) = 0;
			data_base_connect(*(argv + 2));
			pos = data_base_find(in_buf);
			close(fd);
			*buf = 0;				/*you might push an empty name*/
		}
	}
	data_base_close();
	printf("POS = %d\n%s\n", pos, in_buf + pos + 1);
	reuse_port(sfd);
	close_socket(sfd);
	_exit(0);
}
