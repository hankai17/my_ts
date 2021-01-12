#include <iostream>
#include "ts/EventNotify.h"
#include "ts/ink_thread.h"
#include "ts/ink_time.h"

EventNotify* en = nullptr;

void* test(void* a) {
    sleep(4);
    en->signal();
    return nullptr;
}

int main() {
  en = new EventNotify();
  //ink_thread tid = 
  ink_thread_create(test, NULL, 1);
  uint64_t before = ink_microseconds(MICRO_REAL);
  //en->wait();
  en->timedwait(2000);
  uint64_t after = ink_microseconds(MICRO_REAL);

  std::cout << "wait done, diff: " << after - before << std::endl;
  return 0;
}
