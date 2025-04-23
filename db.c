#include "db.h"

static int fd;
static char sbuf[buf_cap];

static data_base_read(buf);
static buf_split(buf, len);

static data_base_read(buf)
char* buf;
{
	ssize_t cnt;
	errno = 0;
	cnt = read(fd, buf, buf_cap);
	if (cnt == -1)
	{
		perror("data_base_read()\n");
		exit(1);
	}
	*(buf + cnt) = 0;
}

static buf_split(buf, len)
char* buf;
int len;
{
	int i;
	for (i = 0; i < len; i++)
	{
		if (*(buf + i) == '\n')
			*(buf + i) = 0;
	}
}

data_base_connect(name)
const char* name;
{
	errno = 0;
	fd = open(name, O_RDWR);
	if (fd == -1)
	{
		perror("data_base_connect()\n");
		exit(2);
	}
}

data_base_find(name)
const char* name;
{
	int pos, len;
	pos = 0;
	data_base_read(sbuf);
	len = strlen(sbuf);
	buf_split(sbuf, len);
	while (pos <= len)
	{
		if (0 == strcmp(sbuf + pos, name))
			return pos;
		pos += strlen(sbuf + pos) + 1;
	}
	return pos;
}

data_base_close()
{
	int res;
	errno = 0;
	res = close(fd);
	if (res == -1)
	{
		perror("data_base_close()\n");
		exit(3);
	}
}
