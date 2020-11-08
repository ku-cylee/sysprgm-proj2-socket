#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define PORT_MAX 10
#define INPUT_MAX 64

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
	int idx, port_size, ports[PORT_MAX];
	port_size = get_ports(ports);

	for (idx = 0; idx < port_size; idx++) printf("%d ", ports[idx]);
	printf("\n");

	return 0;
}
