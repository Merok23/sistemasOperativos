#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>

// ./bin/ejemplo.exe echo hola imprime hola 
int main(int argc, char* argv[]) {
	// Notar que argv+1 es lo mismo que
	// {argv[1], argv[2], ..., argv[argc-1], NULL}
	execvp(argv[1], argv+1);

	printf("Terminando: %d\n", getpid()); //No sigue el programa despues
}
