BIN=exclusion_mutuelle_process exclusion_mutuelle_threads

CFLAGS=-Wall
LDFLAGS=-pthread -lrt

all: $(BIN)

exclusion_mutuelle_process: exclusion_mutuelle_process.c
	$(CC) -o exclusion_mutuelle_process exclusion_mutuelle_process.c $(CFLAGS) $(LDFLAGS)

exclusion_mutuelle_threads: exclusion_mutuelle_threads.c
	$(CC) -o exclusion_mutuelle_threads exclusion_mutuelle_threads.c $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(BIN)
