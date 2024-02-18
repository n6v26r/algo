#include <stdio.h>

int main(){
  FILE *fin, *fout;
  fin = fopen("file.in", "r");
  fclose(fin);

  fout= fopen("file.out", "w");
  fclose(fout);
  return 0;
}
