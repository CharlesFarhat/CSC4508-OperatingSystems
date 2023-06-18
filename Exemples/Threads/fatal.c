#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define FATAL(errnum, ...) do {					\
    fprintf(stderr, "Error in %s:%d:\n", __FILE__, __LINE__);	\
    fprintf(stderr, __VA_ARGS__);				\
    fprintf(stderr, ": %s\n", strerror(errnum));		\
    abort();							\
  } while(0)

int main(int argc, char**argv) {
  char *file=argv[1];
  struct stat buf;
  int rc = stat(file, &buf);
  if(rc < 0) {
    FATAL(errno, "Cannot access file '%s'", file);
  }
  return EXIT_SUCCESS;
}
