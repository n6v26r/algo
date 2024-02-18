#include <stdio.h>

int main(){
  FILE *fin, *fout;
  int a, b;
  short q;
  fin = fopen("mrgary.in", "r");
  fout = fopen("mrgary.out", "w");
  fscanf(fin, "%hd", &q);
  for(short i=0; i<q; i++){
    fscanf(fin, "%d %d", &a, &b);

    if(a==b) fprintf(fout, "Yena\n");
    else fprintf(fout, "Gary\n");
  } 
  fclose(fin);
  fclose(fout);
  return 0;
}
