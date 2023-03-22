#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

int main(int argc, char* argv[]) {
  int fds[2];
  int msg = 42;

  int r = pipe(fds);
  if (r < 0) {
    perror("Error en pipe");
    exit(-1);
  }

  printf("Lectura: %d, Escritura: %d\n", fds[0], fds[1]);//siempre el primero es lectura,
                                                        // el segundo escritura.
  
  //read(fds[0], &msg, sizeof(msg)); // Si descomentas esto, se queda esperando el mensaje "bloqueado"

  // Escribo en el pipe
  write(fds[1], &msg, sizeof(msg));

  int recibido = 0;
  read(fds[0], &recibido, sizeof(recibido));
  printf("Recibi: %d\n", recibido);

  close(fds[0]);
  close(fds[1]);
}


