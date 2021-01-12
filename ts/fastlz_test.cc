#include "ts/fastlz.h"
#include "ts/ink_file.h"

int move_file(const char* infilename, const char* outfilenam, size_t offset, size_t size)
{
    FILE *fin = fopen(infilename,"r");
    if(!fin)
        return -1;
    FILE *fout = fopen(outfilenam,"w");
    if(!fout)
    {
        fclose(fin);
        return -1;
    }
    char  buf[1024*64]={0};
    int  blockSize = sizeof(buf);
    int writelen = 0;
    if(offset != 0) {
#ifdef HAVE_FSEEKO
        if( fseeko(fin, offset, SEEK_SET) < 0) return -1;
#else
        if( fseek(fin, (long) offset, SEEK_SET) < 0) return -1;
#endif
    }

    while( size >0 )
    {
        if(size< blockSize)
            blockSize = size;

        fread( buf, sizeof(char), blockSize, fin );
        writelen = fwrite( buf, sizeof(char), blockSize, fout );
        size = size - blockSize;
        if(writelen != blockSize)
        {
            fclose(fin);
            fclose(fout);
            unlink(outfilenam);
            return -1;
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}


int main() {
    int fastlz_compress(const void *input, int length, void *output);
  return 0;
}
