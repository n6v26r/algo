#include <stdio.h>
#include <unistd.h>

#define MAXCIUR 10000000

#define MAXN 390000000

int ciur[MAXCIUR];
int prime[MAXCIUR], primeCnt;

int d(int n){
  int d = 2;
  int j = 1;
  int div = 0;
  int dis = 0;
  while(d*d<=n){
    if(n%d==0) dis++;
    while(n%d==0){div++; n/=d;}
    d = prime[j++];
  }
  if(n>1) dis++, div++;
  if(dis==div) return div;
  return -1;
}

int main(){
  for(int i=2; i<MAXCIUR; i++){
    if(!ciur[i]){
      for(long long d=(long long)i*i; d<MAXCIUR; d+=i)
        ciur[d] = 1;
      // printf("%d\n", i); fflush(stdout);
      prime[primeCnt++] = i;
    }
  }
  fflush(stdout);
  FILE *fout;

  fout = fopen("gen.out", "w");
  for(int i=0; i<MAXN/200000; i++){
    int contor = 0;
    for(int j=200000*i; j<200000*(i+1); j++){
      if(d(j)==3){contor++;}
    }
    printf("%d. %d\n",i, contor);
    fprintf(fout, "%d, ", contor);
  }
  fclose(fout);
  return 0;
}
