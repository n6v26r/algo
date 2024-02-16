#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n, z;

int main(){
  FILE *fin, *fout;
  fin = fopen("plimbare.in", "r");
  fscanf(fin, "%d\n%d\n", &n, &z);
  fclose(fin);
  
  fout = fopen("plimbare.out", "w");
  if(!(z&1)){fprintf(fout, "0\n"); return 0;}
  bool inverse = 0;
  for(int i=0; i<n; i++){
    int bit = ((z>>(n-1-i))&1);
    if(!bit) {
      if(!inverse){fprintf(fout, "%d +\n", n-1-i); inverse = true;}
      else fprintf(fout, "%d -\n", n-1-i);
    }
    else{
      if(inverse){fprintf(fout, "%d -\n", n-1-i); inverse = false;}
      else{fprintf(fout, "%d +\n", n-1-i);}
    }
  }
  fclose(fout);
  return 0;
}
