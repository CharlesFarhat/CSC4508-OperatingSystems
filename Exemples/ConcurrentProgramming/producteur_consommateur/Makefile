BIN=prod_cons_process prod_cons_threads

CFLAGS=-Wall
LDFLAGS=-pthread -lrt

all: $(BIN)

prod_cons_process: prod_cons_process.c
	$(CC) -o prod_cons_process prod_cons_process.c $(CFLAGS) $(LDFLAGS)

prod_cons_threads: prod_cons_threads.c
	$(CC) -o prod_cons_threads prod_cons_threads.c $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(BIN)
