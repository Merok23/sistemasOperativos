#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  printf("Mi PID es: %d\n", getpid());
  int padre = getpid();

  for (int i = 0; i < 12; i++) {
    int r = fork();

    if (r < 0) {
      perror("Error en fork");
      exit(-1);
    }

    printf("[%d] Hola!\n", getpid());
  }

  printf("%i\n", getpid() - padre); // se crean 2^12 procesos, pero por alguna razon se queda trabajo el programa
  printf("Terminando\n");
  exit(0);
}


