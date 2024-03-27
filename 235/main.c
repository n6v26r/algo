// __razv was here
// OJI 2009 - 8th grade
#include <stdio.h>

#define MAXM 40001

int n;

int p[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
int v[MAXM+69], size=1;

int main(){
  FILE *fin, *fout;
  fin = fopen("235.in", "r");
  fscanf(fin, "%d", &n);
  int p3=0;
  int p5=0;
  int total = 0;
  for(int i=0; i<n; i++){
    int val;
    fscanf(fin, "%d", &val);
    if(!(val%3)){
      while(!(val%3)) val/=3;
      if(val==1){
        p3++;
        total++;
        v[size++] = p5-p3;
      }
    }else if(!(val%5)){
      while(!(val%5)) val/=5;
      if(val==1){ 
        p5++;
        total++;
        v[size++] = p5-p3;
      }
    }
  }
  fclose(fin);

  int secv = 0;
  for(int i=0; i<size; i++){
    for(int j=0; p[j]+i<size; j++){
      if(v[i+p[j]]==v[i]) secv++;
    }
  }

  fout = fopen("235.out", "w");
  fprintf(fout, "%d\n%d\n", total, secv);
  fclose(fout);
  return 0;
}
