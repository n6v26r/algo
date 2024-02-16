#include <stdio.h>

int main(){
  for(int i=0; i<1000; i++){
    if(i%7) continue;
    int n = i;
    while(n>0){
      if(n%10!=1 && n%10!=2 && n%10 != 4)
        break;
      n/=10;
    }
    if(n==0) printf("%d ", i);
  }
  return 0;
}
