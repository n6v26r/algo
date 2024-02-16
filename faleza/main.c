// this crappy piece of code is provided to u
// by __razv
#include <stdio.h>
#include <stdlib.h>
int v[2][100001];
int main(){
  int i, n;
  FILE *fin, *fout;
  fin=fopen("faleza.in", "r");
  fscanf(fin, "%d\n", &n);
  for(int j=0; j<2; j++)
    for(i=0; i<n; i++){
      fscanf(fin, "%d ", &v[j][i]);
    }
  fclose(fin);
  char sus=1;
  char jos=1;
  int contor=0;
  for(i=0; i<n; i++){
    contor++;
    if(!v[0][i] && !v[1][i]){
      v[0][i]=sus;
      v[1][i]=jos;
    }
    else{
      if((v[0][i] && sus) || (v[1][i] && jos)){
        contor--;
      }
      else{
        if(!sus)
          v[1][i]=1;
        if(!jos)
          v[0][i]=1;
      }
    }
    sus=v[0][i];
    jos=v[1][i];
  }

  fout=fopen("faleza.out", "w");
  fprintf(fout, "%d\n", contor);
  fclose(fout);
  return 0;
}
