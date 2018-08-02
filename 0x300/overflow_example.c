#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  int value = 5;
  char buffer_one[8], buffer_two[8];

  strcpy(buffer_one, "one");
  strcpy(buffer_two, "two");

  printf("[前] buffer_twoは%pにあり、その値は\'%s\'です\n", buffer_two, buffer_two);
  printf("[前] buffer_oneは%pにあり、その値は\'%s\'です\n", buffer_one, buffer_one);
  printf("[前] valueは%pにあり、その値は%d(0x%08x)です\n", &value, value, value);

  printf("\n[STRCPY] %d バイトをbuffer_twoにコピーします\n\n", strlen(argv[1]));
  strcpy(buffer_two, argv[1]); //segmentation fault: 11

  printf("[後] buffer_twoは%pにあり、その値は\'%s\'です\n", buffer_two, buffer_two);
  printf("[後] buffer_oneは%pにあり、その値は\'%s\'です\n", buffer_one, buffer_one);
  printf("[後] valueは%pにあり、その値は%d(0x%08x)です\n", &value, value, value);
}
