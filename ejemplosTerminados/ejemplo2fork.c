#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>


int main(int argc, char* argv[]) {
  int* a = malloc(sizeof(int));
  int i = fork();

  *a = 5;

  if (i < 0) {
    printf("Error en fork! %d\n", i);
    exit(-1);
  }

  if (i == 0) {
    printf("[hijo] mi pid es: %d\n", getpid());
    printf("[hijo] a=%d\n", *a); //y, diria que aca imprime 5
    printf("[hijo] puntero a 'a' = %p\n", a);
  } else {
    *a = 6;
    printf("[padre] mi pid es: %d\n", getpid());
    printf("[padre] a=%d\n", *a); //y aca 6
    printf("[padre] puntero a 'a' = %p\n", a);
  }
  free(a);
  printf("Terminando\n");
  exit(0);
}

