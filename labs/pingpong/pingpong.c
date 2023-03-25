#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <time.h>

void errorDeReadOrWrite(int errorRead, int errorWrite, int* fdsPipeHijo, int* fdsPipePadre);

void closePipes(int* fdsPipeHijo, int* fdsPipePadre);

void closePipes(int* fdsPipeHijo, int* fdsPipePadre){
  close(fdsPipeHijo[0]);
  close(fdsPipeHijo[1]);
  close(fdsPipePadre[0]);
  close(fdsPipePadre[1]);
  return;    
}


void errorDeReadOrWrite(int errorRead, int errorWrite, int* fdsPipeHijo, int* fdsPipePadre){
    if (errorRead < 0 || errorWrite < 0){
      closePipes(fdsPipeHijo, fdsPipePadre);
      if(errorRead < 0) printf("Hubo un error en el read. %i\n", errorRead);
      if(errorWrite < 0) printf("Hubo un error en el write. %i\n", errorWrite);
    }
}

int main() {
  int fdsPipePadre[2];
  int fdsPipeHijo[2];
  srandom(time(NULL));
  long int recibido = 0;
  int errorPipePadre = pipe(fdsPipePadre);
  int errorPipeHijo = pipe(fdsPipeHijo);
  if (errorPipeHijo < 0 || errorPipePadre < 0) {
    perror("Error en pipe");
    exit(-1);
  }
  
  printf("Hola, soy PID %i:\n", getpid());
  printf("  - primer pipe me devuelve: [%i, %i]\n", fdsPipeHijo[0], fdsPipeHijo[1]);
  printf("  - segundo pipe me devuelve: [%i, %i]\n", fdsPipePadre[0], fdsPipePadre[1]);

  int i = fork();

  if (i < 0) {
    printf("Error en fork! %d\n", i);
    closePipes(fdsPipeHijo, fdsPipePadre);
    exit(-1);
  }
  if (i == 0){
    int errorRead = read(fdsPipePadre[0], &recibido, sizeof(recibido));

    printf("\nDonde fork me devuelve %i:\n", i);
    printf("  - getpid me devuelve: %i\n", getpid());
    printf("  - getppid me devuelve: %i\n", getppid());
    printf("  - recibo valor %li via fd=%i:\n", recibido, fdsPipeHijo[0]);
    printf("  - reenvio valor en fd=%i y termino\n\n", fdsPipePadre[1]);
    int errorWrite = write(fdsPipeHijo[1], &recibido, sizeof(recibido));
    if (errorRead < 0 || errorWrite < 0){
      errorDeReadOrWrite(errorRead, errorWrite, fdsPipeHijo, fdsPipePadre);
      exit(-1);
    }

  }else{

    long int mensaje = random();
    printf("\nDonde fork me devuelve %i:\n", i);
    printf("  - getpid me devuelve: %i\n", getpid());
    printf("  - getppid me devuelve: %i\n", getppid());
    printf("  - random me devuelve: %li\n", mensaje);
    printf("  - envio valor %li a traves de fd=%i\n", mensaje, fdsPipeHijo[1]);
    int errorWrite = write(fdsPipePadre[1], &mensaje, sizeof(mensaje));
    int errorRead = read(fdsPipeHijo[0], &recibido, sizeof(recibido));
    if (errorRead < 0 || errorWrite < 0){
      errorDeReadOrWrite(errorRead, errorWrite, fdsPipeHijo, fdsPipePadre);
      exit(-1);
    }
    printf("Hola, de nuevo PID %i:\n", getpid());
    printf("  - recibi valor %li via fd=%i:\n", mensaje, fdsPipePadre[0]);
  }

  closePipes(fdsPipeHijo, fdsPipePadre);
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);

  exit(0);
}