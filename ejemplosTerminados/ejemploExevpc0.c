#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>
// imprime hello world
int main(int argc, char* argv[]) {
	char *args[] = {"echo", "hello world!", NULL};
	execvp("echo", args);

	printf("Terminando: %d\n", getpid());//Nunca se ejecuta, execp corta en el medio
}
