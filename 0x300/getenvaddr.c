#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, argv[]){
  char *ptr;

  if (argc < 3){
    printf("使用方法: %s<環境変数><対象プログラム名>\n", argv[0]);
    exit(0);
  }
  ptr = getenv(argv[1]);
  ptr += (strlen(argv[0]) - strlen(argv[2]))*2;
  printf("%s: %p\n", argv[1], ptr);
}
