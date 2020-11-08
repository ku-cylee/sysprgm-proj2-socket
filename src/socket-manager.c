#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "sys/timeb.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

#include "socket-manager.h"

#define BUFFER_SIZE 512
#define SERVER_ADDR "192.168.56.101"

int atsign_counting(const char * const buf, size_t len) {
	int i, n = 0;
	for (i = 0; i < len; i++) {
		if (buf[i] == '@') n++;
	}
	return n;
}

void read_from_server(int fd, int port) {
	int msg_size, atsign_count = 0;
	char filename[32] = { 0 }, buffer[BUFFER_SIZE] = { 0 };
	FILE *fp;

	printf("Connected to port #%d\n", port);
	sprintf(filename, "../logs/%d-%d.txt", port, fd);
	printf("Filename: %s\n", filename);

	fp = fopen(filename, "a");

	memset(buffer, 0x00, sizeof(buffer));
	while ((msg_size = read(fd, buffer, BUFFER_SIZE)) > 0) {
		atsign_count += atsign_counting(buffer, msg_size);
		if (atsign_count >= 5) break;
		
		time_t tnow;
		time(&tnow);
		struct tm *t = (struct tm *)localtime(&tnow);
		
		struct timeb timebuffer;
		ftime(&timebuffer);
		int ms = timebuffer.millitm;
		fprintf(fp, "%02d:%02d:%02d.%03d|%d|%s\n", t->tm_hour, t->tm_min, t->tm_sec, ms, msg_size, buffer);

		memset(buffer, 0x00, sizeof(buffer));
	}

	fclose(fp);
}

int connect_socket(int fd, struct sockaddr_in *sv_addr) {
	int res = connect(fd, (struct sockaddr *)sv_addr, sizeof(sv_addr));
	return res;
}

void set_server_addr(struct sockaddr_in *sv_addr, int port) {
	memset(sv_addr, 0, sizeof(*sv_addr));
	sv_addr->sin_family = AF_INET;
	sv_addr->sin_addr.s_addr = inet_addr(SERVER_ADDR);
	sv_addr->sin_port = htons(port);
}

int create_socket() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	return fd;
}

void *socket_main(void *arg) {
	int port = (int)arg;
	struct sockaddr_in sv_addr;

	int client_fd = create_socket();
	set_server_addr(&sv_addr, port);
	int connected = connect_socket(client_fd, &sv_addr);
	read_from_server(client_fd, port);
	close(client_fd);		
}
