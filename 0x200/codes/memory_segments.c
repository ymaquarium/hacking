#include <stdio.h>

int global_var;
int global_initialized_var = 5;

void function(){
  int stack_var = 5;
  printf("functionのstack_varは、アドレスの0x%08xにあります。\n", &stack_var);
}

int main(){
  int stack_var;
  static int static_initialized_var = 5;
  static int static_var;
  int *heap_var_ptr;

  heap_var_ptr = (int *) malloc(4);

  //inside data_segment
  printf("global_initialized_varはアドレス0x%08xにあります\n", &global_initialized_var);
  printf("static_initialized_varはアドレス0x%08xにあります\n", &static_initialized_var);

  //inside bss_segment
  printf("static_varはアドレス0x%08xにあります\n", &static_var);
  printf("global_varはアドレス0x%08xにあります\n", &global_var);

  //inside heap_segment
  printf("heap_var_ptrはアドレス0x%08xを指しています\n", heap_var_ptr);

  //inside stack_segment
  printf("stack_varはアドレス0x%08xにあります\n", &stack_var);
  function();
}
