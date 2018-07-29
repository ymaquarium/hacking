#include <stdio.h>

int main(){
  char string[20];
  int A = -73;
  unsigned int B = -31337;

  strcpy(string, "sample");

  printf("[A] d %d, x %x, 符号なしd %u\n", A, A, A);
  printf("[B] d %d, x %x, 符号なしd %u\n", B, B, B);
  printf("[Bのフィールド幅指定] 3: '%3d', 10:'%10d', '%08d'\n", B, B, B);
  printf("[文字列] %s アドレス %08x\n", string, string);

  printf("変数Aのアドレス:%08x\n", &A);
}
