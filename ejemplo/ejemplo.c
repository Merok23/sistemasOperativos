#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Se necesita un argumento\n");
    exit(-1);
  }

  close(1);
  int fd = open("hola.txt", O_CREAT | O_RDWR, 0644);
  printf("Archivo abierto en %d\n", fd); //por que no printea esto?

  // Notar que argv+1 es lo mismo que
  // {argv[1], argv[2], ..., argv[argc-1], NULL}
  execvp(argv[1], argv+1);

  printf("Terminando: %d\n", getpid());
}
