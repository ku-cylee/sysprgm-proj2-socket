#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

int atsign_counting(const char * const buf, size_t len);

void read_from_server(int fd, int port);

int connect_socket(int fd, int port, struct sockaddr_in *sv_addr);

void set_server_addr(struct sockaddr_in *sv_addr, int port);

int create_socket();

void *socket_main(void *arg);
