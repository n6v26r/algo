#include <stdio.h>
#include <stdlib.h>

long long n;
int k;

int getOnes(long long n){
  int ones = 0;
  while(n>0){
    ones++;
    n=n&(n-1);
  }
  return ones;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("suc.in", "r");
  fscanf(fin, "%lld\n%d\n", &n, &k);
  fclose(fin);

  fout = fopen("suc.out", "w");
  int ones = getOnes(n);
  if(ones<=k){
    fprintf(fout, "0\n");
    return 0;
  }

  int zerosPast = 0;
  int activeOnes = 0;
  int onesCleared = 0;
  long long sum = 0;
  for(int i=0; ; i++){
    int bit = ((n>>i)&1);
    if(!bit){
      onesCleared+=activeOnes-1;
      sum+=((long long)1<<zerosPast);
      zerosPast+=activeOnes;
      activeOnes=1;
      if(ones-onesCleared<=k){
        break;
      }
    }
    else activeOnes++;
  }
  fprintf(fout, "%lld\n", sum);
  fclose(fout);
}
