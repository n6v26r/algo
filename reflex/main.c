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
  fin = fopen("reflex.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  fclose(fin);
  printf("%d ", cmmdc(n-1, m-1));
  long long collisions = (long long)(n-1)*(m-1)/cmmdc(n-1, m-1)+1;
  int v = (n-1)/cmmdc(n-1, m-1);
  int h = (m-1)/cmmdc(n-1, m-1);

  int exit = 0;

  if(v%2){
    exit = 2 + h%2;
  }
  else exit = 4;

  fout = fopen("reflex.out", "w");
  fprintf(fout, "%lld %d\n%d %d\n", collisions, exit, h-1, v-1);
  fclose(fout);
  return 0;
}
