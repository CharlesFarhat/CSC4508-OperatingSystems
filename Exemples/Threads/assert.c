#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char**argv) {
  char *file=argv[1];
  struct stat buf;
  int rc = stat(file, &buf);
  assert(rc>=0);
  return EXIT_SUCCESS;
}
