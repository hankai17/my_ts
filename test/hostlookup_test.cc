#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include "ts/ink_memory.h"
#include "ts/DynArray.h"
#include "ts/HostLookup.h"

void print_func(void* data) {
  std::cout << "---" << std::endl;
}

int main() {
  const char* host = "www.baidu.com";
  HostLookup h1(host);
  h1.AllocateSpace(100);

  h1.NewEntry(host, true, (void*)host);
  return 0;
}
