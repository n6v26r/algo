#include <stdio.h>

int v[31];
int n, k;
int max = -__INT32_MAX__;
int min = __INT32_MAX__;

void optim(int x, int y, int sum, int p){
  if(x==n-1){
    if(y>0)
      return;
    sum+=p;
    if(sum>max)
      max=sum;
    if(sum<min)
      min=sum;
    return;
  }

  optim(x+1, y, sum+p, v[x+1]);
  if(y>0)
    optim(x+1, y-1, sum, p*v[x+1]);
}

int main(){
  FILE *fin, *fout;
  fin=fopen("optim.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);
  optim(0, k, 0, v[0]);

  fout=fopen("optim.out", "w");
  fprintf(fout, "%d %d\n", min, max);
  fclose(fout);
  return 0;
}
