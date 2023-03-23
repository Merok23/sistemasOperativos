#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  int fds[2];

  pipe(fds);

  printf("Lectura: %d, Escritura: %d\n", fds[0], fds[1]);

  int msg = 42;
  int escritos = 0;
  int r = 0;
  while (1) {
    r = write(fds[1], &msg, sizeof(msg));
    if (r >= 0 ) {
      printf("Esto es r: %i\n", r);
      printf("Total escrito: %d\n", escritos);
      escritos += sizeof(msg);
    } else {
      printf("write fallo con %d\n", r);
      printf("errno was: %d\n", errno);
      perror("perror en write");
      break;
    }
  };

  close(fds[0]);
  close(fds[1]);
}




