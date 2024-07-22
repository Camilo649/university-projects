#include "types.h"
#include "spinlock.h"
#include "param.h"
#include "semaphore.h"
#include "riscv.h"
#include "defs.h"

static int sem_array_is_init(struct semaphore * Sarray){
    unsigned int i = 0u;

    while ((Sarray[i].ocuped == 0 || Sarray[i].ocuped == 1) && i < MAXSEM)
        ++i;
    
    return (i == MAXSEM);
}

static void sem_array_init(struct semaphore * Sarray){
    for (unsigned int i = 0u; i < MAXSEM; ++i)
        Sarray[i].ocuped = 0;
}

// inicializa el counter de sem en el valor pre-establecido
// similar a sem_init de la libreria de C
uint64 
sem_open (int sem, int value) {   

  if (sem < 0 || sem >= MAXSEM)   // parameter out of range
    return 0;  

  if (value < 0) // value of the semaphore cannot be negative
    return 0;

  if (!sem_array_is_init(sem_array))
    {
        sem_array_init(sem_array);
    }

  acquire(&sem_array[sem].lock);     // lock sem and do busy waiting until is enable 
  sem_array[sem].count = value;     // inicializate the count value
  sem_array[sem].ocuped = 1;
  release(&sem_array[sem].lock);
  return 1;
}

uint64
sem_close (int sem) {
  
  if (sem < 0 || sem >= MAXSEM) //parameter out of range
    return 0;                         

  acquire(&sem_array[sem].lock);
  sem_array[sem].ocuped = 0;          
  release(&sem_array[sem].lock);
  
  return 1;  
}

// incrementa el contador del sem en uno
// similar a sem_post de la libreria de C
uint64
sem_up (int sem) {
  
  if (sem < 0 || sem >= MAXSEM)   //parameter out of range
    return 0;                     // error code

  acquire (&sem_array[sem].lock); // lock sem and do busy waiting until is enable
  sem_array [sem].count++;     // increment sem counter
  wakeup (&sem_array [sem]);         // find the sleeping consumer and wake it up. If threres no sleeping proccess it doesn't do anything 
  release (&sem_array [sem].lock);   // dissable divice interrupts and do syncronization 
  return 1;
}

// decrementa en uno el contador de sem
// similar a sem_wait de la libreria de C
uint64
sem_down (int sem) {
  
  if (sem < 0 || sem >= MAXSEM)   // parameter out of range
    return 0;

  acquire (&sem_array[sem].lock);   // lock sem and do busy waiting until is enable
  while (sem_array [sem].count <= 0 )  // waits until the count is not zero 
    sleep (&sem_array [sem], &sem_array [sem].lock);

  sem_array [sem].count--;
  release (&sem_array [sem].lock);   // dissable device interrupts and do syncronization
  return 1;
}
