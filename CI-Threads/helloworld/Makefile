CFLAGS= -Wall -pthread -g

SOURCES = main.c

all: main.o
	gcc -o main main.o -lpthread


main.o: main.c
	$(CC)  -c main.c $(CFLAGS)


clean:
	rm -f main *.o