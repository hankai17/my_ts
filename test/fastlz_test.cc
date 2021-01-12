#include <iostream>
#include <string.h>
#include "ts/fastlz.h"

int main() {
  char inbuf[1024 * 64] = {0};
  char output[1024 * 64 + 350 ] = {0};
  int blockSize = sizeof(inbuf);
  int ret = 0;
  int fz_ret = 0;
  int compress_sum = 0;
  
  FILE* fin = fopen("./1.log", "r");
  if (!fin) return -1;

  FILE* fout = fopen("./2.log", "w+");
  if (!fout) return -1;

  while((ret = fread(inbuf, sizeof(char), blockSize, fin))) {
    //fz_ret = fastlz_compress(inbuf, ret, output); // 1728116 
    //fz_ret = fastlz_compress_level(1, inbuf, ret, output); // 1761276
    fz_ret = fastlz_compress_level(2, inbuf, ret, output); // 1728065
    //std::cout << "ori size: " << ret << ", after compress size: " << fz_ret << std::endl;
    compress_sum += fz_ret;

    fwrite(output, 1, fz_ret, fout);

    memset(inbuf, 0x0, blockSize);
    fz_ret = fastlz_decompress(output, fz_ret, inbuf, blockSize);
    //fz_ret = fastlz_decompress(output, strlen(output), inbuf, blockSize);
    //std::cout << "decompress ret " << fz_ret << std::endl;
  }
  std::cout << "compress_sum: " << compress_sum << std::endl;
  fclose(fin); 
  fclose(fout); 
  return 0;
}

int main1() {
  char inbuf[1024 * 64] = {0};
  char output[1024 * 64 + 350 ] = {0};
  int blockSize = sizeof(inbuf);
  int ret = 0;
  int fz_ret = 0;
  
  FILE* fin = fopen("./1.log", "r");
  if (!fin) return -1;

  FILE* fout = fopen("./2.log", "w+");
  if (!fout) return -1;

  while((ret = fread(inbuf, sizeof(char), blockSize, fin))) {
    fz_ret = fastlz_compress(inbuf, ret, output);
    //std::cout << "ori size: " << ret << ", after compress size: " << fz_ret << std::endl;

    fwrite(output, 1, fz_ret, fout);

    memset(inbuf, 0x0, blockSize);
    fz_ret = fastlz_decompress(output, fz_ret, inbuf, blockSize);
    //fz_ret = fastlz_decompress(output, strlen(output), inbuf, blockSize);
    //std::cout << "decompress ret " << fz_ret << std::endl;
  }
  fclose(fin); 
  fclose(fout); 

  memset(inbuf, 0x0, blockSize);
  FILE* f1 = fopen("./2.log", "r");
  if (!f1) return -1;
  FILE* f2 = fopen("./3.log", "w+");
  if (!f2) return -1;
  while((ret = fread(inbuf, sizeof(char), blockSize, f1))) {
    fz_ret = fastlz_decompress(inbuf, ret, output, sizeof(output));
    std::cout << "ret: " << ret << ", decompress fz_ret: " << fz_ret << std::endl;
    fwrite(output, 1, fz_ret, f2);
  }
  fclose(f1);
  fclose(f2);
  return 0;
}
