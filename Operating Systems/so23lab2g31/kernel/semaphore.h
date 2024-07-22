struct semaphore {
  struct spinlock lock;
  int count;
  int ocuped; // is 1 if the sem is ocuped and is 0 if it's available 
};

struct semaphore sem_array [MAXSEM];
