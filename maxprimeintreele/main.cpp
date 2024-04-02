#include <stdio.h>

#define MAXN 10001
#define MAX(a, b) ((a)>(b)?(a):(b))

int t;

int euler(int n){
  int e = n;
  int d = 2;
  while(n>1){
    if(n%d==0){
      e = e/d*(d-1);
      while(n%d==0) n/=d;
    }
    d++;
    if(d*d>n) d = n;
  }
  return e;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("maxprimeintreele.in", "r");
  fout = fopen("maxprimeintreele.out", "w");
  double maxval = 0;
  int best = 0;
  char c = fgetc(fin);
  while(c!='\n' && c!=EOF){
    ungetc(c, fin);
    int val; fscanf(fin, "%d ", &val);
    int e = euler(val);
    if((double)val/e>maxval){maxval = (double)val/e; best = val;}
    c = fgetc(fin);
  }
  fprintf(fout, "%d\n", best);
  fclose(fin);
  fclose(fout);
  return 0;
}
