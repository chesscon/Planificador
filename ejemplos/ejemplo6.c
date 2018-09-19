#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
 
int main(int argc, char *argv[]) {

  char *programas[] = {
      "../sumaAleatorios 100000 ../output/salida01.txt",
      "../sumaAleatorios 1000 ../output/salida02.txt",
      "../sumaAleatorios 50000 ../output/salida03.txt",
      "../sumaAleatorios 8000 ../output/salida04.txt",
      "../sumaAleatorios 10000 ../output/salida05.txt"
  };

  char *args[] = {"sh", "-c",
    "../sumaAleatorios 10000 ../output/salida10.txt", NULL};
 
  //execv("/bin/sh", args);

  int N = 5;
  pid_t *pids = malloc(sizeof(pid_t)*N);
  int *status = malloc(sizeof(int)*N);

  pid_t pidActual;
 
  int numProcesos = 0;

  while (numProcesos < N) {
    //numProcesos++;
    pidActual = fork();
  
    if ( pidActual == 0 ) { /* hijo */
      printf("Soy el hijo %d (%d, hijo de %d)\n", numProcesos+1, getpid(), getppid());
      args[2] = programas[numProcesos];
      execv("/bin/sh", args);
      printf("Esto ya no deberia imprimirse\n");
      printf("Se ha producido un error al ejecutar execv.\n");
      //exit(0);
    } else { /*  padre */
      // registra el proceso creado:
      pids[numProcesos++] = pidActual;
    }    
  }
  for(int i=0; i < numProcesos; i++) {
    pidActual = wait( &(status[i]));
    printf("Termino de ejecutar el proceso: %d \n", pidActual);
  }

  printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
  printf("se ejecutaron todos los procsos hijos:\n");

  
  //printf("Se ha producido un error al ejecutar execv.\n");
 
  return 0;
}