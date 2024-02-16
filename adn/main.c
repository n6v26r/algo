#include <stdio.h>

#define MAXN 5000001

int n;
int v[MAXN];

int main(){
  for(int i=2; i<MAXN; i++){
    if(v[i]==0){
      for(int d=i; d<MAXN; d+=i){
        if(!v[d]) v[d] = 1;
        v[d] *= i;
      }
    }
  }
  v[1] = 1;
  FILE *fin, *fout;
  fin = fopen("adn.in", "r");
  fscanf(fin, "%d", &n);
  int sum = 0;
  for(int i=1; i<=n; i++){
    sum += n/v[i];
    // printf("%d\n", v[i]);
  }
  fclose(fin);

  fout = fopen("adn.out", "w");
  fprintf(fout, "%d\n", sum);
  fclose(fout);
  return 0;
}
