/*  Uso de la funcion exec con sh*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char *argv[]) {
  char *args[] = {"sh", "-c",
    "../sumaAleatorios 1000 ../output/salida10.txt", NULL};
 
  execv("/bin/sh", args);
 
  printf("Se ha producido un error al ejecutar execv.\n");
 
  return 0;
}