#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

#define ERROR 0
#define SUCCESS 1

void print_err(const char *message) {
  printf("ERROR: %s\n", message);
}

int
main(int argc, char *argv[])
{
  int rc, round;

  // Invalid amount of args
  if(argc != 2){ 
    print_err("Too many arguments.\n");
    exit(ERROR);
  }

  // Parsing args
  round = atoi(argv[1]);
  if (round < 1) 
  {
    print_err("Number of rounds must be greater than 0.\n");
    exit(ERROR);
  }

  // Open semaphores 
  int Child = get_sem_name();
  if (sem_open(Child,  0) == 0) // valor inicial del sem 0 para que deba esperar sem_up(Child) del padre
  {
    print_err("Couldn't open semaphores.\n");
    exit(ERROR);
  } 

  int Parent = get_sem_name();
  if (sem_open(Parent, 1) == 0 ) // 1 para que se ejecute primero
  {
    print_err("Couldn't open semaphores.\n");
    exit(ERROR);
  } 

  while (round > 0){

    rc = fork();
    if (rc < 0) {
      print_err("fork\n");
      exit(ERROR);
    }

    // Child, debe imprimir "pong"
    if (rc == 0) {
      if (!sem_down(Child))  //espera a que sem asociado al hijo este habilitado
        exit(ERROR); 

      printf("\tpong\n");

      if (!sem_up(Parent))  //habilita sem asociado al padre
        exit(ERROR);

      exit(SUCCESS);
    }
  
    // Parent, imprime "ping"
    else {
      if (!sem_down(Parent))  //espera a que sem asociado al padre este habilitado
        exit(ERROR);

      printf("ping\n");

      if (!sem_up(Child)) //habilita sem asociado a hijo
        exit(ERROR);
      
      wait(NULL);
    }

    --round;
  }

  // Close semaphores
  if (sem_close(Child) == 0 || sem_close(Parent) == 0) 
  {
    print_err("Couldn't close semaphores.\n");
    exit(ERROR);
  } 

  exit(SUCCESS);
}
