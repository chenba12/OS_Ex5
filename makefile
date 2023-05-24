CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -pthread

st_pipeline: main.o active_object.o queue.o utils.o pipe_line.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o st_pipeline
