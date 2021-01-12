#include <sys/types.h>
#include <unistd.h>
#include "ts/DynArray.h"

class Foo {
    public:
          int a;
};

int main() {
  Foo* f = new Foo();
  DynArray<Foo> arr = DynArray<Foo>(f);
  
  return 0;
}
