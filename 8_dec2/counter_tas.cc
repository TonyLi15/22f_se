#include "lock.h"
uint Counter = 0;
std::atomic<int> global_atomic(Counter);
std::atomic<int> Mutex;

bool my_lock_core(uint *memory_location, int expected, int desired) {
    return __sync_bool_compare_and_swap(memory_location, expected,desired);
}

void my_lock(void) {
  uint* current = &Counter;
  while (true) {
    bool ok = my_lock_core(current, Counter, Counter+1);
    if (ok == true) break;
    Mutex.store(LockBit);
  }
}

void my_unlock() { 
  Mutex.store(UnlockBit); 
}

void *worker(void *arg) {
  for (uint i = 0; i < NbLoop; i++) {
    my_lock();
    //Counter++;
    my_unlock();
  }
  return NULL;
}

int
main(void)
{
  pthread_t thread[NbThread];
  if ((pthread_mutex_init(&Lock, NULL)) == -1) ERR;

  for (uint i = 0; i < NbThread; i++) {
    pthread_create(&thread[i], NULL, worker, NULL);
  }
  for (uint i = 0; i < NbThread; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("Counter: %u (Ref. %u)\n", Counter, NbThread * NbLoop);

  return 0;
}
