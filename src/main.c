#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "pthread.h"

#include "socket-manager.h"

#define PORT_MAX 10
#define INPUT_MAX 64

void manage_ports (int *ports, int port_size) {
	int idx;
	pthread_t pids[PORT_MAX];
	for (idx = 0; idx < port_size; idx++) {
		pthread_create(&pids[idx], NULL, &socket_main, (void *)ports[idx]);
	}

	for (idx = 0; idx < port_size; idx++) pthread_join(pids[idx], NULL);
	printf("Multithreading Terminated\n");
}

int get_ports(int *ports) {
	int idx, port_cnt, port_size;
	char input[INPUT_MAX], *ptr;

	if (fgets(input, INPUT_MAX, stdin) < 0) {
		printf("Input fetch failed");
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
	int port_size, ports[PORT_MAX];
	port_size = get_ports(ports);
	manage_ports(ports, port_size);

	return 0;
}
