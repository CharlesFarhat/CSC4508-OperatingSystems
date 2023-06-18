BIN=cohorte_process cohorte_threads

CFLAGS=-Wall
LDFLAGS=-pthread -lrt

all: $(BIN)

cohorte_process: cohorte_process.c
	$(CC) -o cohorte_process cohorte_process.c $(CFLAGS) $(LDFLAGS)

cohorte_threads: cohorte_threads.c
	$(CC) -o cohorte_threads cohorte_threads.c $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(BIN)
