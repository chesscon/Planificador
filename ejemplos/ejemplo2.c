/* uso de la funcion waitpid() */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[]) {
  pid_t pid1, pid2;
  int status1, status2;
 
  pid1=fork();
  
  if ( pid1 == 0 ) { /* hijo */
    printf("Soy el primer hijo (%d, hijo de %d)\n",  getpid(), getppid());
  } else { /*  padre */
    pid2=fork();
    
    if ( pid2 == 0 ) { /* segundo hijo  */
      printf("Soy el segundo hijo (%d, hijo de %d)\n",  getpid(), getppid());
    } else { /* padre */
      /* Esperamos al primer hijo */
      waitpid(pid1, &status1, 0);
      /* Esperamos al segundo hijo */
      waitpid(pid2, &status2, 0);
      printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
    }
  }
  return 0;
}