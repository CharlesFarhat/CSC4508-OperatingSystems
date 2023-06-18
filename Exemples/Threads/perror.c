#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main(int argc, char**argv) {
  char *file=argv[1];
  struct stat buf;
  int rc = stat(file, &buf);
  if(rc < 0) {
    perror("Error while accessing file");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
