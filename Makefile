all : src/*.c src/*.h
	gcc src/*.c -o bin/client.out -lpthread

debug : src/*.c src/*.h
	gcc src/*.c -o bin/client.out -lpthread -g

clean :
	rm -f bin/*.o bin/*.out
