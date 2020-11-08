#include "arpa/inet.h"

void count_end_sign(const char * const buf, size_t len, int *count);
void read_from_server(int fd, int port);
int connect_socket(int fd, int port, struct sockaddr_in *sv_addr);
void set_server_addr(struct sockaddr_in *sv_addr, int port);
int create_socket();
void *socket_main(void *arg);
