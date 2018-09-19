/* Uso de la funcion fork() */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
 
int main(int argc, char *argv[]){
  pid_t pid;

  pid=fork();

  if ( pid == 0 ) { /* hijo */
    printf("Soy el hijo (%d, hijo de %d)\n", getpid(),
    getppid());
  } else { /* padre */
    printf("Soy el padre (%d, hijo de %d)\n", getpid(),
    getppid());
  }
 
  return 0;
}
