#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void memdump(char *fmt, char *data);

int main(int argc, char *argv[])
{
  if(argc == 1){
    printf("Example 1:\n");
    int a[2] = { 61810, 2025 };
    memdump("ii", (char*) a);
    
    printf("Example 2:\n");
    memdump("S", "a string");
    
    printf("Example 3:\n");
    char *s = "another";
    memdump("s", (char *) &s);

    struct sss {
      char *ptr;
      int num1;
      short num2;
      char byte;
      char bytes[8];
    } example;
    
    example.ptr = "hello";
    example.num1 = 1819438967;
    example.num2 = 100;
    example.byte = 'z';
    strcpy(example.bytes, "xyzzy");
    
    printf("Example 4:\n");
    memdump("pihcS", (char*) &example);
    
    printf("Example 5:\n");
    memdump("sccccc", (char*) &example);
  } else if(argc == 2){
    // format in argv[1], up to 512 bytes of data from standard input.
    char data[512];
    int n = 0;
    memset(data, '\0', sizeof(data));
    while(n < sizeof(data)){
      int nn = read(0, data + n, sizeof(data) - n);
      if(nn <= 0)
        break;
      n += nn;
    }
    memdump(argv[1], data);
  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }
  exit(0);
}

void
memdump(char *fmt, char *data)
{
  // figoure how to read it using fmt
  int index_fmt = 0;
  int i = 0;
  while ((char) fmt[index_fmt] != '\0'){
    if (fmt[index_fmt] == 'i') {
      uint32 value; 
      memmove(&value, data + i, sizeof(value));
      i += 4;
      printf("%u\n", value);
    } else if (fmt[index_fmt] == 'p') {
      uint64 value; 
      memmove(&value, data + i, sizeof(value));
      i += 8;
      printf("%lx\n", value);
    } else if (fmt[index_fmt] == 'h') {
      uint16 value;
      memmove(&value, data + i, sizeof(value));
      i += 2;
      printf("%u\n", value);
    } else if (fmt[index_fmt] == 'c') {
      uint8 value;
      memmove(&value, data + i, sizeof(value));
      printf("%c\n", (char) value);
      i += 1;
    } else if (fmt[index_fmt] == 's') {
      uint64 value;
      memmove(&value, data + i, sizeof(value));
      printf("%s\n", (char *) value);
      i += 8;
    } else if (fmt[index_fmt] == 'S') {
      printf("%s\n", (char *) data + i);
    } else {
      printf("Error unkown flag: %c\n", fmt[index_fmt]);
      return;
    }
    index_fmt++;
  }
  return;
}

