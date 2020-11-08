#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

#include "socket-manager.h"
#include "logger.h"

#define ENDSIGN_LEN 5
#define BUFFER_SIZE 512
#define SERVER_ADDR "192.168.56.101"

void count_end_sign(const char * const buf, size_t len, int *count) {
	int idx;
	for (idx = 0; idx < len && *count < ENDSIGN_LEN; idx++) {
		if (buf[idx] == '@') (*count)++;
		else *count = 0;
	}
}

int read_iter(int fd, int *endsign_cnt, FILE *logger) {
	size_t msg_size;
	char buffer[BUFFER_SIZE];

	memset(buffer, 0x00, sizeof(buffer));
	msg_size = read(fd, buffer, BUFFER_SIZE);
	if (msg_size <= 0) return -1;

	count_end_sign(buffer, msg_size, endsign_cnt);
	if (*endsign_cnt >= ENDSIGN_LEN) return -1;

	write_log(logger, msg_size, buffer);
	return 0;
}

void read_from_server(int fd, int port) {
	int endsign_cnt = 0;
	FILE *fp = open_log(fd, port);
	if (fp == NULL) return;

	while (read_iter(fd, &endsign_cnt, fp) == 0);
	close_log(fp);
}

int connect_socket(int fd, int port, struct sockaddr_in *sv_addr) {
	int res = connect(fd, (struct sockaddr *)sv_addr, sizeof(*sv_addr));
	if (res < 0) fprintf(stderr, "failed to connect through port %d\n", port);
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
	if (fd < 0) fprintf(stderr, "failed to create stream socket\n");
	return fd;
}

void *socket_main(void *arg) {
	int port = (int)arg;
	struct sockaddr_in sv_addr;

	int client_fd = create_socket();
	if (client_fd < 0) return ;

	set_server_addr(&sv_addr, port);

	int connection = connect_socket(client_fd, port, &sv_addr);
	if (connection == 0) read_from_server(client_fd, port);

	close(client_fd);
}
