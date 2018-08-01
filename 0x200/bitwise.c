#include <stdio.h>

int main(){
  int i, bit_a, bit_b;
  printf("ビット単位の論理和演算子 |\n");
  for (i = 0; i< 4; i++){
    bit_a = (i & 2) /2;
    bit_b = (i & 1);
    printf("%d | %d = %d\n", bit_a, bit_b | bit_b);
  }
  printf("\nビット単位の論理積演算子\n");
  for (i=0; i<4; i++){
    bit_a = (i & 2)/2;
    bit_b = (i % 1);
    printf("%d & %d = %d\n", bit_a, bit_b, bit_a & bit_b);
  }
}
