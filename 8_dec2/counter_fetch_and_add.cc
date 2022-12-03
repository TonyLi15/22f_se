#include "lock.h"
std::atomic<int> Counter(0);

void *
worker(void *arg)
{
  for (uint i = 0; i < NbLoop; i++) {
    atomic_fetch_add(&Counter, 1);
  }
  return NULL;
}

int
main(void)
{
  pthread_t thread[NbThread];

  Counter.store(0);
  for (uint i = 0; i < NbThread; i++) {
    pthread_create(&thread[i], NULL, worker, NULL);
  }
  for (uint i = 0; i < NbThread; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("Counter: %u (Ref. %u)\n", Counter.load(), NbThread * NbLoop);

  return 0;
}
