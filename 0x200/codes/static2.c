#include <stdio.h>

void function(){
  int var = 5;
  static int static_var = 5;

  printf("\t[function内] var @ %p = %d\n", &var, var);
  printf("\t[function内] static_var @ %p = %d\n", &static_var, static_var);
  var++;
  static_var++;
}

int main(){
  int i;
  static int static_var = 1337;

  for(i=0; i<5; i++){
    printf("[main内] static_var @ %p = %d\n", &static_var, static_var);
    function();
  }
}
