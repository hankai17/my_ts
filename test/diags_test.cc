#include <iostream>
#include "ts/Diags.h"
#include "ts/BaseLogFile.h"

#define DEBUG_TAG "hugepages"

extern inkcoreapi Diags *diags;

int main() {
  BaseLogFile* f = new BaseLogFile("ts.log");
  diags = new Diags(DEBUG_TAG, DEBUG_TAG, f);
  diags->activate_taglist(DEBUG_TAG, DiagsTagType_Debug);

  std::cout << "on: " << diags->on() << std::endl;
  std::cout << "on: " << diags->on(DEBUG_TAG) << std::endl;

  diags->log("hugepages", DiagsLevel::DL_Diag, NULL, NULL, 99, "test test");
  diags->log("hugepages", DiagsLevel::DL_Diag, NULL, NULL, 999, "%s:%d", "hello", 100);
  //diags->dump();

  return 0;
}
