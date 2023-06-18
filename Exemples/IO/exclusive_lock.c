/***********/
/* exclusive_lock.c */
/***********/
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd;
  struct flock lock;

  fd = open("/tmp/ficTest",O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
  if (fd < 0) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  /* Exclusive lock on the 15th byte */
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 15;
  lock.l_len = 1;

  /* Because of the F_SETLKW parameter, we get stuck on the fcntl if */
  /* the lock cannot be acquired                                   */
  printf("attempt to acquire an exclusive lock by process %d...\n",
	 getpid());
  if (fcntl(fd, F_SETLKW, &lock) < 0){
    perror("Acquiring lock");
    exit(EXIT_FAILURE);
  }
  printf("... Exclusive lock acquired by process %d\n", getpid());

  /* Here we could do the processing that needed to be protected */
  /* by the lock                                                 */
  sleep(10);

  /* Release the lock */
  printf("Releasing the lock by process %d...\n", getpid());
  lock.l_type = F_UNLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 15;
  lock.l_len = 1;
  if (fcntl(fd, F_SETLK, &lock) < 0){
    perror("Releasing lock");
    exit(EXIT_FAILURE);
  }
  printf("...OK\n");

  return EXIT_SUCCESS;
}
