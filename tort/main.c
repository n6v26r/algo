#include <stdio.h>

int n, m;

int cmmdc(int a, int b){
  while(b>0){
    int r = a%b;
    a = b;
    b = r; 
  }
  return a;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("tort.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  fclose(fin);

  int d = cmmdc(n, m);

  fout = fopen("tort.out", "w");
  fprintf(fout, "%d %d\n", n*m/d/d, d);
  fclose(fout);
  
  return 0;
}
