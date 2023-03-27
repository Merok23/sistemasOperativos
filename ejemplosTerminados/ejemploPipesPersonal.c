#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  int fds[2];
  int msg = 42;

  int r = pipe(fds);
  int i = fork();
  
  if (i < 0) {
    printf("Error en fork! %d\n", i);
    exit(-1);
  }

  if (r < 0) {
    perror("Error en pipe");
    exit(-1);
  }

  if(i == 0){
    read(fds[0], &msg, sizeof(msg)); // Si descomentas esto, se queda esperando el mensaje "bloqueado"
    if(msg == -1){
      close(fds[0]);
      close(fds[1]);
      printf("Soy el hijo, cerre el pipe\n");
      exit(0);
    }
    printf("volvi a leer lpm\n");
    read(fds[0], &msg, sizeof(msg)); // Si descomentas esto, se queda esperando el mensaje "bloqueado"
  }else{
    int matate = -1;
    write(fds[1], &matate, sizeof(int));
    close(fds[1]);
    close(fds[0]);
    printf("Soy el padre, termine\n");
  }
  close(fds[0]);
  close(fds[1]);
}