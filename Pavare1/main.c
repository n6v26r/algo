#include <stdio.h>
int p, n;

int v[100001];

int min = __INT_MAX__;

void recurse(int n, int last, int k){
  if(last==0) return;
  v[k-1] = last;
  if(n-last-1>=(last+1)*last/2)
    recurse(n-last-1, last+1, k+1);
  else if(n-last>=(last)*(last-1)/2)
    recurse(n-last, last, k+1);
  else if(n-last+1>=(last-1)*(last-2)/2)
    recurse(n-last+1, last-1, k+1);

  if(n==0 && (last==1)){
    if(k<min) min = k;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("pavare.in", "r");
  fscanf(fin, "%d%d", &p, &n);
  fclose(fin);

  n-=1;
  v[0] = 1;
  recurse(n, 1, 1);

  fout = fopen("pavare.out", "w");
  if(p==1) fprintf(fout, "%d", min);
  else for(int i=min-1; i>=0; i--) fprintf(fout, "%d ", v[i]);
  fprintf(fout, "\n");
  fclose(fout);
  return 0;
}
