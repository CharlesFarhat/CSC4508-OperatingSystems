/************/
/* copy.c */
/************/
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define USAGE "USAGE: copy src dest\n"
#define WRITE_ERROR "write error (no space left on device ?)\n"

int source, dest;
int buf;
int nb_read, nb_written;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    write(STDERR_FILENO, USAGE, strlen(USAGE));
    return EXIT_FAILURE;
  }
  source = open(argv[1], O_RDONLY);
  if (source < 0) {
    perror(argv[1]);
    return EXIT_FAILURE;
  }
  dest = open(argv[2],
              O_WRONLY|O_CREAT|O_TRUNC,
              S_IRWXU|S_IRWXG|S_IRWXO);
  if (dest < 0) {
    perror(argv[2]);
    return EXIT_FAILURE;
  }
  while ((nb_read = read(source, (void*)&buf, sizeof(buf))) > 0) {
    nb_written = write(dest, (void*)&buf, nb_read);
    if (nb_written <= 0) {
      if (nb_written == 0) {
        write(STDERR_FILENO, WRITE_ERROR, strlen(WRITE_ERROR));
      }
      else {
        perror("write");
      }
      return EXIT_FAILURE;
    }
  }
  if (nb_read < 0) {
    perror("read");
    return EXIT_FAILURE;
  }
  if (close(source) < 0) {
    perror(argv[1]);
    return EXIT_FAILURE;
  }
  if (close(dest) < 0) {
    perror(argv[2]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
