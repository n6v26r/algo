#include <stdio.h>

int n, m;

int main(){
  FILE *fin, *fout;
  fin = fopen("tortO.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  fclose(fin);

  fout = fopen("tortO.out", "w");
  fclose(fout);
  return 0;
}
