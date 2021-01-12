#include <iostream>

#include "ts/hugepages.h"

int main() {
  ats_hugepage_init(1); // 获取proc中的hugepage size
  std::cout << "huge enable: " << ats_hugepage_enabled() << std::endl;
  std::cout << "hugesize: " << ats_hugepage_size() << std::endl;

  void* ptr = ats_alloc_hugepage(128);
  ats_free_hugepage(ptr, 128);
  return 0;
}
