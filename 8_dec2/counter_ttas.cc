#include "lock.h"
uint Counter = 0;
std::atomic<int> global_atomic(Counter);
std::atomic<int> Mutex;

bool my_lock_core() {
  auto lock = Mutex.load();
  if(lock == LockBit){
    usleep(1);
    return false;
  }
  return Mutex.compare_exchange_strong(lock, LockBit);
}

void my_lock(void) {
  while (true) {
    bool ok = my_lock_core();
    if (ok == true) break;
  }
}

void my_unlock() { 
  Mutex.store(UnlockBit); 
}

void *worker(void *arg) {
  for (uint i = 0; i < NbLoop; i++) {
    my_lock();
    Counter++;
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
