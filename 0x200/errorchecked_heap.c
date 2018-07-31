#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *errorchecked_malloc(unsigned int);

int main(int argc, char *argv[]){
  char *char_ptr;
  int *int_ptr;
  int mem_size;

  if (argc < 2)
    mem_size = 50;
  else
    mem_size = atoi(argv[1]);
  printf("\t[+]ヒープから%dバイトを割り当て、先頭アドレスをchar_ptrに代入します\n", mem_size);
  char_ptr = (char *)errorchecked_malloc(mem_size);
  /*
  if (char_ptr == NULL){
    fprintf(stderr, "エラー。ヒープメモリの割り当てに失敗しました。\n");
    exit(-1);
  }
  */
  strcpy(char_ptr, "KORE HA HEAP NI COPY SAREMASU");
  printf("char_ptr(%p) --> '%s'\n", char_ptr, char_ptr);

  printf("\t[+]ヒープから12バイトを割り当て、先頭アドレスをint_ptrに代入します\n");
  int_ptr = (int *)errorchecked_malloc(12);
  /*
  if (int_ptr == NULL){
    fprintf(stderr, "エラー。ヒープメモリの割り当てに失敗しました\n");
    exit(-1);
  }
  */
  *int_ptr = 31337;
  printf("int_ptr (%p) --> %d\n", int_ptr, *int_ptr);

  printf("\t[-]char_ptrが指しているヒープメモリを解放します\n");
  free(char_ptr);

  printf("\t[+]ヒープから再び15バイトを割り当て、先頭アドレスをchar_ptrにします\n");
  char_ptr = (char *)errorchecked_malloc(15);
  /*
  if (char_ptr == NULL){
    fprintf(stderr, "エラー。ヒープメモリの割り当てに失敗しました。\n");
    exit(-1);
  }
  */
  strcpy(char_ptr, "NEW MEMORY");
  printf("char_ptr (%p) --> '%s'\n", char_ptr, char_ptr);

  printf("\t[-]int_ptrのヒープメモリを解放します\n");
  free(int_ptr);
  printf("\t[-]char_ptrのヒープメモリを解放します\n");
  free(char_ptr);
}

void *errorchecked_malloc(unsigned int size){
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL){
    fprintf(stderr, "エラー。ヒープメモリの割り当てに失敗しました。\n");
    exit(-1);
  }
  return ptr;
}
