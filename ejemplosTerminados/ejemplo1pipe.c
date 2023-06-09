#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  int fds[2];
  int msg = 42;

  pipe(fds);
  int i = fork();

  if (i == 0) {
    printf("[hijo] mi pid es: %d\n", getpid());
    // El hijo no va a escribir
    close(fds[1]);

    int recv = 0;
    sleep(2);

    read(fds[0], &recv, sizeof(recv));
    printf("[hijo] lei: %d\n", recv);

    close(fds[0]);
  } else {
    printf("[padre] mi pid es: %d\n", getpid());
    // El padre no va a leer
    close(fds[0]);

    // Esperamos dos segundos, el hijo no debería seguir
    write(fds[1], &msg, sizeof(msg));

    close(fds[1]);
  }
  exit(0);
}

