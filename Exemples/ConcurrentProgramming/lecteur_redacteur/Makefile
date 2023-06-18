BIN=rw_process rw_threads_mutex rw_threads_rwlock rw_threads_condition

CFLAGS=-Wall
LDFLAGS=-pthread -lrt

all: $(BIN)

rw_process: rw_process.c
	$(CC) -o rw_process rw_process.c $(CFLAGS) $(LDFLAGS)

rw_threads_mutex: rw_threads_mutex.c
	$(CC) -o rw_threads_mutex rw_threads_mutex.c $(CFLAGS) $(LDFLAGS)

rw_threads_rwlock: rw_threads_rwlock.c
	$(CC) -o rw_threads_rwlock rw_threads_rwlock.c $(CFLAGS) $(LDFLAGS)

rw_threads_condition: rw_threads_condition.c
	$(CC) -o rw_threads_condition rw_threads_condition.c $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(BIN)
