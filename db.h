#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
enum {buf_cap = 1024};
data_base_connect(name);
data_base_find(name);
data_base_close();
#endif
