#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *fin, *fout;
  fin=fopen("expand.in", "r");
  
  fclose(fin);

  fout=fopen("expand.out", "w");
  fclose(fout);
  return EXIT_SUCCESS;
}
