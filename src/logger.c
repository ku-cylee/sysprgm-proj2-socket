#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/timeb.h"

#include "logger.h"

FILE *open_log(int fd, int port) {
	char filename[32] = { 0 };
	sprintf(filename, "../logs/%d-%d.txt", port, fd);
	return fopen(filename, "a");
}

void write_log(FILE *fp, int msg_size, char *buffer) {
	time_t now;
	time(&now);
	struct tm *t = (struct tm *)localtime(&now);

	struct timeb tbuf;
	ftime(&tbuf);

	fprintf(fp, "%02d:%02d:%02d.%03d|%d|%s\n", t->tm_hour, t->tm_min, t->tm_sec, tbuf.millitm, msg_size, buffer);
}

void close_log(FILE *fp) {
	fclose(fp);
}
