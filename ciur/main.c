#include <stdio.h>
#include <stdbool.h>

#define MAXN 2000000

int ciur[MAXN+1];

int main(){
  ciur[0]=ciur[1]=0;
  for(int i=2; i<=MAXN; i++){
    if(!ciur[i]){
      for(int d=i; d<=MAXN; d+=i)
        ciur[d]++;
    }
  }
  int n;
  FILE *fin, *fout;
  fin = fopen("ciur.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);

  fout = fopen("ciur.out", "w");
  fprintf(fout, "%d\n", ciur[n]);
  fclose(fout);
  return 0;
}
