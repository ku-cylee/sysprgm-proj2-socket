CC = gcc
CFLAGS = -lpthread
MKDIR = mkdir -p bin
SRCS = src/*.c
OBJECTS = bin/*.o
TARGET = bin/2018320156_client

all : src/*.c src/*.h
	$(MKDIR)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

debug : src/*.c src/*.h
	$(MKDIR)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) -g

clean :
	rm -f $(OBJECTS) $(TARGET)
