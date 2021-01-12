#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "ts/Tokenizer.h"
#include "ts/SimpleTokenizer.h"

/*
#define COPY_TOKS (1u << 0)
#define SHARE_TOKS (1u << 1)
#define ALLOW_EMPTY_TOKS (1u << 2)
#define ALLOW_SPACES (1u << 3)
*/

int main2() {
  const char *line = "*a****b****c*d*e**f";
  Tokenizer remap("*\t");
  unsigned count = remap.Initialize(const_cast<char *>(line), (COPY_TOKS | ALLOW_SPACES));
  //unsigned count = remap.Initialize(const_cast<char *>(line), (COPY_TOKS | ALLOW_EMPTY_TOKS));
  //unsigned count = remap.Initialize(const_cast<char *>(line), (COPY_TOKS | ALLOW_EMPTY_TOKS | ALLOW_SPACES));

  for (unsigned i = 0; i < count; ++i) {
      std::cout << "remap[i]: " << remap[i] << std::endl;
  }
  return 0;
}

int main1()
{
  const char *line = "map https://abc.com https://abc.com  @pparam=proxy.config.abc='ABC DEF' @plugin=conf_remap.so";
  //const char *toks[] = {"map", "https://abc.com", "https://abc.com", "@plugin=conf_remap.so", "@pparam=proxy.config.abc='ABC DEF'"};
  Tokenizer remap(" \t");

  unsigned count = remap.Initialize(const_cast<char *>(line), (COPY_TOKS | ALLOW_SPACES));

  std::cout << "count: " << count << std::endl;
  std::cout << "remap.count: " << remap.count() << std::endl;

  for (unsigned i = 0; i < count; ++i) {
      //std::cout << "remap[i]: " << remap[i] << ", toks[i]: " << toks[i] << std::endl;
      std::cout << "remap[i]: " << remap[i] << std::endl;
  }
  return 0;
}

int main() {
  const char* str = "one    two\\ and\\ three four:   five : six";
  std::cout << str << std::endl;
  SimpleTokenizer tok(str);

  /*
  int field = tok.getNumTokensRemaining();
  for (int i = 0; i < field; i++) {
    std::cout << "\"" << tok.getNext() << "\"" << std::endl;
  }
  */

  if (1) {
    std::cout << tok.getNext() << std::endl;
    std::cout << tok.getNext() << std::endl;
    std::cout << tok.getNext(':') << std::endl;
    std::cout << tok.peekAtRestOfString() << std::endl;
    std::cout << tok.getNext(':') << std::endl;
  }

  /*
  SimpleTokenizer tok(",  with null fields ,,,", ',',
                      CONSIDER_NULL_FIELDS | KEEP_WHITESPACE);
  std::cout << tok.getNext() << std::endl;
  std::cout << tok.getNext() << std::endl;
  std::cout << tok.getNumTokensRemaining() << std::endl;
  */
  return 0;
}
