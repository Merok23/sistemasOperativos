#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {
  int fdsPipePadre[2]; // Padre significa que solo escribe el padre.
  int fdsPipeHijo[2];
  srandom(time(NULL));
  long int mensaje = random();
  long int recibido = 0;
  pipe(fdsPipeHijo);
  pipe(fdsPipePadre);
  printf("Hola, soy PID <%i>:\n", getpid());
  printf(" - primer pipe me devuelve: [%i, %i]\n", fdsPipeHijo[0], fdsPipeHijo[1]);
  printf(" - segundo pipe me devuelve: [%i, %i]\n", fdsPipePadre[0], fdsPipePadre[1]);

  int i = fork();

  if (i < 0) {
    printf("Error en fork! %d\n", i);
    exit(-1);
  }
  if (i == 0){
    read(fdsPipePadre[0], &recibido, sizeof(recibido));

    printf("\nDonde fork me devuelve 0:\n");
    printf(" - getpid me devuelve: %i\n", getpid());
    printf(" - getppid me devuelve: %i\n", getppid());
    //read
    printf(" - recibo valor %li via fd=%i:\n", recibido, fdsPipePadre[0]);
    //write
    printf(" - reenvio valor en fd=%i y termino\n\n", fdsPipeHijo[1]);
    write(fdsPipeHijo[1], &recibido, sizeof(recibido));

  }else{

    printf("\nDonde fork me devuelve %i:\n", i);
    printf(" - getpid me devuelve: %i\n", getpid());
    printf(" - getppid me devuelve: %i\n", getppid());
    printf(" - random me devuelve: %li\n", mensaje);
    //write
    printf(" - envio valor %li a traves de fd=%i\n", mensaje, fdsPipePadre[1]);
    write(fdsPipePadre[1], &mensaje, sizeof(mensaje));
    //wait
    read(fdsPipeHijo[0], &recibido, sizeof(recibido));
    printf("Hola, de nuevo %i:\n", getpid());
    printf(" - recibi valor %li via fd=%i:\n", mensaje, fdsPipeHijo[0]);
  }

  close(fdsPipeHijo[0]);
  close(fdsPipeHijo[1]);
  close(fdsPipePadre[0]);
  close(fdsPipePadre[1]);

  exit(0);
}