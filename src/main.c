#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "pthread.h"

#include "socket-manager.h"

#define PORT_MAX 10
#define INPUT_MAX 64

void manage_sockets(int *ports, int port_size) {
	int idx;
	pthread_t pids[PORT_MAX];
	for (idx = 0; idx < port_size; idx++) {
		pthread_create(&pids[idx], NULL, &socket_main, (void *)ports[idx]);
	}

	for (idx = 0; idx < port_size; idx++) pthread_join(pids[idx], NULL);

	fprintf(stdout, "close\n");
}

void print_ports(int *ports, int port_size) {
	int idx;
	fprintf(stdout, "open:");
	for (idx = 0; idx < port_size; idx++) printf(" %d", ports[idx]);
	printf("\n");
}

int get_ports(int *ports) {
	int idx, port_size;
	char input[INPUT_MAX], *ptr;

	fprintf(stdout, "input: ");
	if (fgets(input, INPUT_MAX, stdin) < 0) {
		fprintf(stdout, "failed: reading ports");
		return -1;
	}

	ptr = strtok(input, " ");
	port_size = atoi(ptr);

	for (idx = 0, ptr = strtok(NULL, " ");
		 idx < port_size && ptr != NULL; idx++, ptr = strtok(NULL, " ")) {
		ports[idx] = atoi(ptr);
	}

	return port_size;
}

int main(int argc, char *argv[]) {
	while (1) {
		int port_size, ports[PORT_MAX];
		port_size = get_ports(ports);
		if (port_size < -1) continue;
		print_ports(ports, port_size);
		manage_sockets(ports, port_size);
	}

	return 0;
}
