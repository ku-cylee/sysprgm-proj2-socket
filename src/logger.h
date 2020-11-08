FILE *open_log(int fd, int port);
void write_log(FILE *fp, int msg_size, char *buffer);
void close_log(FILE *fp);
