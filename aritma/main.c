// ONI 2015 8th grade
// __razv
#include <stdio.h>

int f[(1<<20)];

int v[1001], size = 0;

int n, m;

int main(){
  FILE *fin, *fout;
  fin = fopen("aritma.in", "r");
  fscanf(fin, "%d%d\n", &n, &m);
  for(int i=0; i<n; i++){
    v[0] = 0; size = 1;
    char c = fgetc(fin);
    // TESTE SCRISE CU NESIMTIRE, FARA ENDL PE ULTIMA LINIE
    while(c!='\n' && c!=EOF){
      int bit = (c=='+'?1:0);
      int newsize = size;
      for(int i=0; i<size; i++){
        v[i] = v[i]*2+bit;
        if(c=='*'){v[newsize++] = v[i]+1;}
      }
      size = newsize;
      c = fgetc(fin);
    }
    for(int i=0; i<size; i++){
      f[v[i]] = 1;
    }
  }
  fclose(fin);

  fout = fopen("aritma.out", "w");
  int total = 0;
  for(int i=0; i<(1<<20); i++){
    total += f[i];
  }
  fprintf(fout, "%d", total);
  fclose(fout);
  return 0;
}
