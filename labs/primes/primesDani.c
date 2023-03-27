#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/syscall.h>
#include <sys/wait.h>

#include <errno.h>

#define READ 0
#define WRITE 1

void check_result(int i, char *e_message);

void recursive_primes(int left_fds_0);

void check_result(int i, char *e_message) {
  if (i < 0) {
    perror(e_message);
    exit(-1);
  }
}

void recursive_primes(int left_fds_0) {

  int number, r_primo, aux, fds[2], n_fork;

  aux = read(left_fds_0, &r_primo, sizeof(r_primo));

  if (aux == 0) {
    close(left_fds_0);
    exit(-1);
  }

  printf("primo %d\n", r_primo);

  aux = pipe(fds);
  check_result(aux, "Error en creación del pipe.\n");

  n_fork = fork();

  if (n_fork == 0) {

    close(left_fds_0);
    close(fds[WRITE]);

    recursive_primes(fds[READ]);
    close(fds[READ]);

  } else {

    close(fds[READ]);

    while (read(left_fds_0, &number, sizeof(number))) {
      if (number % r_primo != 0) {
        aux = write(fds[WRITE], &number, sizeof(number));
        check_result(aux, "Error en escritura.\n");
      }
    }
    close(fds[WRITE]);
    close(left_fds_0);

    wait(NULL);
  }
  exit(0);
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    perror("Cantidad de argumentos inválida.\n");
    exit(-1);
  }

  int max = atoi(argv[1]);
  int aux, n_fork, fds[2];

  aux = pipe(fds);
  check_result(aux, "Error en creación del pipe.\n");

  n_fork = fork();

  if (n_fork == 0) {

    close(fds[WRITE]);
    recursive_primes(fds[READ]);

  } else {

    close(fds[READ]);

    for (int i = 2; i <= max; i++) {
      aux = write(fds[WRITE], &i, sizeof(i));
      check_result(aux, "Error en escritura.\n");
    }

    close(fds[WRITE]);
    wait(NULL);
  }

  fclose(stdin);
  fclose(stdout);
  fclose(stderr);

  exit(0);
}