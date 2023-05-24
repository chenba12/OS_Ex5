CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: active_object

active_object: active_object.o queue.o utils.o
	$(CC) $(CFLAGS) -o active_object active_object.o queue.o utils.o

active_object.o: active_object.c queue.h
	$(CC) $(CFLAGS) -c active_object.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f active_object active_object.o queue.o
