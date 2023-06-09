#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>

void funcionRecursivaMagica(int pipeIzquierdo);

void funcionRecursivaMagica(int pipeIzquierdo){
    int primo = -1;
    int numero = -1;
    int errorWrite = -1;

    int errorPrimo = read(pipeIzquierdo, &primo, sizeof(int));
    if(errorPrimo <= 0){      //termine de leer del filtro izquierdo
        close(pipeIzquierdo); //y no hago nada mas(condicion de corte)
        exit(0);
    }
    
    printf("primo %i\n", primo);
    int pipeDerecho[2];
    int errorPipe = pipe(pipeDerecho);
    int numeroFork = fork();
    if (errorPipe < 0 || numeroFork < 0 || errorPrimo < 0){
        exit(-1);
    }
    
    if(numeroFork == 0){
        close(pipeDerecho[1]);
        close(pipeIzquierdo);
        funcionRecursivaMagica(pipeDerecho[0]);
        close(pipeDerecho[0]);
    }else{
        close(pipeDerecho[0]);
        while(read(pipeIzquierdo, &numero, sizeof(int))){
            if((numero % primo) != 0){
                errorWrite = write(pipeDerecho[1], &numero, sizeof(int));
                if(errorWrite < 0) printf("Se rompio todo \n");
            }
            if(numero == -1) printf("llegue aca\n");
        }
        close(pipeDerecho[1]);
        close(pipeIzquierdo);
        wait(NULL);
    }
    exit(0);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Cantidad de argumentos invalidos!\n");
        return -1;
    }
    int cantidadMaxima = atoi(argv[1]);

    int fdsPrimerPipe[2];
    int errorPipe =  pipe(fdsPrimerPipe);
    int numeroFork = fork();
    
    if (errorPipe < 0 || numeroFork < 0){
        return -1;
    }

    if (numeroFork == 0){
        close(fdsPrimerPipe[1]);
        funcionRecursivaMagica(fdsPrimerPipe[0]);
        printf("F\n");
    }else{
        for(int i = 2; i <= cantidadMaxima; i++){
            int errorWrite = write(fdsPrimerPipe[1], &i, sizeof(int));
            if(errorWrite < 0) printf("Se rompio todo \n");
        }
       close(fdsPrimerPipe[1]);
       wait(NULL);

    }
    close(fdsPrimerPipe[0]);
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    return 0;
}