#include <stdio.h>
#include <stdlib.h>

int n;

int v(int i){
  if(i%2)
    return 2*n-i/2;
  return i/2+1;
}

int main(){
  FILE *fin, *fout;
  fin=fopen("oneton.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);
 
  int j=v(8)-1;
  int l=0;
  do{
    j = v(j)-1;
    l++;
  }while(j!=v(8)-1);

  fout=fopen("oneton.out", "w");
  fprintf(fout, "%d\n", l);
  fclose(fout);
  return EXIT_SUCCESS;
}
