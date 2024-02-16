#include <stdio.h>

#define MAXN 1000001
int n, m;

unsigned char ciur[MAXN];

int main(){
  for(int i=2; i<MAXN; i++)
    if(!ciur[i])
      for(int d=i; d<MAXN; d+=i)
        ciur[d]++;

  FILE *fin, *fout;
  fin = fopen("divprimi.in", "r");
  fscanf(fin, "%d %d", &n, &m);
  fclose(fin);

  int div = 0;
  int total = 0;
  int mth=-1;
  while(total<m){
    int divCount = 0;
    for(int i=1; i<=n; i++){
      if(ciur[i]==div)
        divCount++;
      if(total+divCount==m){
        mth = i;
        break;
      }
    }
    div++;
    total+=divCount;
  }

  fout = fopen("divprimi.out", "w");
  fprintf(fout, "%d\n", mth);
  fclose(fout);
  return 0;
}
