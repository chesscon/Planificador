#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
 
int main(int argc, char *argv[]) {

  char *machinesFile = argv[1];
  char *tasksFile = argv[2];

  int totalRecursos = argv[3];

  FILE *fTasks, *fMachines; //Variables para manejo de archivos

  fTasks =fopen(tasks, "r"); //Abre para lectura
  fMachines=fopen(tasks, "r"); //Abre para lectura

  // Init lista de recursos disponibles
  char *machines[totalRecursos];
  int lista_recursos[totalRecursos];
  for(int i =0; i < totalRecursos; i++) {
    fscanf(fMachines, "%s", machines[i]);
    lista_recursos[i] = 0;
  }
  fclose(fMachines);


  char *programas[] = {
      "../sumaAleatorios 100000 ../output/salida01.txt",
      "../sumaAleatorios 1000 ../output/salida02.txt",
      "../sumaAleatorios 50000 ../output/salida03.txt",
      "../sumaAleatorios 8000 ../output/salida04.txt",
      "../sumaAleatorios 10000 ../output/salida05.txt"

      // "sh -c \"ssh c-1-1 ls prueba/\""
  };

  char *args[] = {"sh", "-c",
   // " ssh c-00-00 \"sumaAleatorios 10000 ../output/salida10.txt\""
    "../sumaAleatorios 10000 ../output/salida10.txt"
    , NULL};
 
  //execv("/bin/sh", args);

  int N = 5;
  pid_t *pids = malloc(sizeof(pid_t)*N);
  int *status = malloc(sizeof(int)*N);

  pid_t pidActual, recurso_disp;
 
  int numProcesos = 0;
  char tareaActual[200];

  while ( !feof(fTasks)) { 
//  while (numProcesos < N) {

    // Buscar un recurso disponible
    recurso_disp = -1;
    fgets(tareaActual, sizeof(tareaActual), fTasks)

    for(int i=0; i < totalRecursos; i++ ) {
      if (lista_recursos[i] == 0) {
        recurso_disp = i;
        break;
      }
    }

    if (recurso_dis < 0) {
      // Espera a que se libere un recurso:
      pid_t idTermino = wait(&status);

      // Una vez que un proceso termino, buscamos el recurso libre
      // Y lo liberamos:
      for(int i=0; i < totalRecursos; i++) {
        if (lista_recurso[i] == idTermino) {
         recurso_disp = i;
         lista_recurso[i] = 0;
        }
      }
    }

    pidActual = fork();
  
    if ( pidActual == 0 ) { /* hijo */
      printf("Soy el hijo %d (%d, hijo de %d)\n", numProcesos+1, getpid(), getppid());
      sprintf(args[2], "ssh %s \"%s\"", machines[recurso_disp], tareaActual);
      //args[2] = programas[numProcesos];

      // Ejecuta el programa usando recurso_dis
      execv("/bin/sh", args);
    
      printf("Esto ya no deberia imprimirse\n");
      printf("Se ha producido un error al ejecutar execv.\n");
      //exit(0);
    } else { /*  padre */
      // registra el proceso creado:
      pids[numProcesos++] = pidActual;

      // Registra recurso_dis ocupado por el proceso creado:
      lista_recurso[recurso_disp] = pidActual;
    }    
  }
  for(int i=0; i < numProcesos; i++) {
    pidActual = wait( &(status[i]));
    printf("Termino de ejecutar el proceso: %d \n", pidActual);
  }
  fclose(fTasks);

  printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
  printf("se ejecutaron todos los procsos hijos:\n");

  
  //printf("Se ha producido un error al ejecutar execv.\n");
 
  return 0;
}