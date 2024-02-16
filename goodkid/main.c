#include <stdio.h>

int t, n, val[10];

int main(){
  scanf("%d", &t);
  for(int c=0; c<t; c++){
    scanf("%d", &n);
    int prod = 1;
    int min = __INT32_MAX__;
    int prod2 = 1;
    for(int i=0; i<n; i++){
      scanf("%d", &val[i]);
      prod*=val[i];
      if(val[i]<min){
        min=val[i];
      }
    }
    int flag = 0;
    for(int i=0; i<n; i++){
      if(val[i]==min && !flag){flag=1;}
      else prod2*=val[i];
    }
    printf("%d\n", prod+prod2);
  }
  fgetc(stdin);
  return 0;
}
