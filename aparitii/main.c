#include <stdio.h>
#include <ctype.h>

void readInt(int *n, FILE *fin){
  *n = 0;
  char c = fgetc(fin);
  while(!isdigit(c)) {
    c = fgetc(fin);
  }
  while(isdigit(c)){
    *n = (*n) * 10 + c - '0';
    c = fgetc(fin);
  }
}

int main(){
  int n;
  int num = 0;
  FILE *fin, *fout;
  fin = fopen("aparitii.in", "r");
  fscanf(fin, "%d", &n);
  
  for(int i=0; i<2*n-1; i++){
    int val;
    readInt(&val, fin);
    num = num ^ val;
  }
  fclose(fin);

  fout = fopen("aparitii.out", "w");
  fprintf(fout, "%d\n", num);
  fclose(fout);
  return 0;
}
