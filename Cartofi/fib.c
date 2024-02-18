#include <stdio.h>

int main(){
  long long a = 0;
  long long b = 1;
  int i = 0;
  while(b<100000000000000){
    long long aux = a;
    a = a+b;
    b = aux;
    printf("%d, ", a%10);
    i++;
  }
  return 0;
}