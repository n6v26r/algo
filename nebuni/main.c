// ONI 2016 baraj gimnaziu
// __razv was here
#include <stdio.h>

#define MAXN 2000001

char prim[MAXN];
int sec[MAXN];

int n, m;

int main(){
  FILE *fin, *fout;
  fin = fopen("nebuni.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int lin, col;
    fscanf(fin, "%d%d", &lin, &col); 
    lin--; col--;
    sec[lin+col] = 1;
    prim[n-1+col-lin] = 1;
  }
  fclose(fin);

  long long sum = 0;
  for(int i=0; i<2*n-1; i++){
    if(prim[i])
      sum+=(i+1<=n)?i+1:2*n-i-1;
    if(sec[i])
      sum+=(i+1<=n)?i+1:2*n-i-1;
    sec[i] += (i>1?sec[i-2]:0);
  }
  
  for(int i=0; i<2*n-1; i++){
    if(prim[i]){
      int pos = (i<n-1)?2*n-2-i:i;
      int dif = pos-n+1;
      sum-=sec[2*n-2-dif]-sec[dif-2];
    }
  }

  fout = fopen("nebuni.out", "w");
  fprintf(fout, "%lld\n", (long long)n*n-sum);
  fclose(fout);
}
