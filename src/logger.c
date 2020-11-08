#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "time.h"
#include "sys/timeb.h"
#include "sys/stat.h"

#include "logger.h"

#define LOG_DIR "./logs"

FILE *open_log(int fd, int port) {
	if (mkdir(LOG_DIR, 0776) < 0 && errno != EEXIST) {
		fprintf(stderr, "failed to create log folder");
		return NULL;
	}

	char filename[32] = { 0 };
	sprintf(filename, "%s/%d-%d.txt", LOG_DIR, port, fd);
	return fopen(filename, "a");
}

void write_log(FILE *fp, int msg_size, char *buffer) {
	struct timeb tbuf;
	ftime(&tbuf);
	time_t now = tbuf.time;

	struct tm *t = (struct tm *)localtime(&now);

	fprintf(fp, "%02d:%02d:%02d.%03d|%d|%s\n", t->tm_hour, t->tm_min, t->tm_sec, tbuf.millitm, msg_size, buffer);
}

void close_log(FILE *fp) {
	fclose(fp);
}
