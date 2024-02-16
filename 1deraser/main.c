#include <stdio.h>
#include <string.h>

#define MAXSIZE 200000

int t, n, k;

char v[MAXSIZE+1];

int main(){
  scanf("%d", &t);
  for(int i=0; i<t; i++){
    scanf("%d %d\n", &n, &k);
    int steps = 0;
    for(int i=0; i<n; i++){
      char c = fgetc(stdin);
      if(c=='B')v[i]=1;
      else v[i]=0;
    }
    for(int i=k-1; i-k+1<n; i++){
      if(v[i-k+1]==1){ // has to fill
        i+=k-1;
        steps++;
      }
    }
    printf("%d\n", steps);
  }
  return 0;
}
