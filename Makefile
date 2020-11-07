all : src/*.c
	gcc src/*.c -o bin/client.out -lpthread

clean :
	rm -f bin/*.o bin/*.out
