#include <stdio.h>

int divn=1;
int divpatrat=1;

void div(long long n){
  long long d = 2;
  while(d*d<=n){
    int exp = 0;
    while(!(n%d)){exp++;n/=d;}
    divn*=(exp+1);
    divpatrat*=(2*exp+1);

    d++;
  }
  if(n>1) divn*=2, divpatrat*=3;
}

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("nenepatrat.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);

  div(n);

  fout = fopen("nenepatrat.out", "w");
  fprintf(fout, "%d\n", divpatrat/2+1 - divn);
  fclose(fout);
  return 0;
}
