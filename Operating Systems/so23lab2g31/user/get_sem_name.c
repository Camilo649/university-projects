#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/param.h"
#include "kernel/semaphore.h"
#include "user/user.h"

int get_sem_name(void){
    unsigned int i = 0u;
    
    while (sem_array[i].ocuped == 1 && i < MAXSEM)
        ++i;
    
    return (i == MAXSEM) ? -1 : i;
}
