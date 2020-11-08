#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "time.h"
#include "sys/timeb.h"
#include "sys/stat.h"

FILE *open_log(int fd, int port);

void write_log(FILE *fp, int msg_size, char *buffer);

void close_log(FILE *fp);
