#include <stdio.h>

#define MAXN 100000

char ciur[MAXN+1];
int prime[10001], size;

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("sprime.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);

  for(int i=2; i<=MAXN; i++){
    if(!ciur[i]){
      for(int d=i*2; d<=MAXN; d+=i)
        ciur[d] = 1;
      prime[size++] = i;
    }
  }

  ciur[0]=ciur[1] = 1;

  int total = 0;
  for(int i=0; i<size && prime[i]<n; i++){
    for(int j=i; j<size && prime[j]<n-prime[i]; j++){
      //printf("%d %d %d (%d)\n", prime[i], prime[j], n-prime[i]-prime[j], ciur[n-prime[i]-prime[j]]);
      if(!(prime[i]<=prime[j] && prime[j]<=n-prime[i]-prime[j])) continue;
      if(!ciur[n-prime[i]-prime[j]])
        total++;
    }
  }

  fout = fopen("sprime.out", "w");
  fprintf(fout, "%d\n", total);
  fclose(fout);
}
