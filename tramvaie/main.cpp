#include <stdio.h>

#define MAXN 1000010

int t;
int euler[MAXN];

int main(){
  for(int i=1; i<MAXN-1; i++){
    euler[i] = i;
  }
  for(int i=2; i<MAXN; i++){
    if(euler[i]==i){
      euler[i]--;
      for(int d = i*2; d<MAXN-1; d+=i){
        euler[d] = euler[d]/i*(i-1);
      }
    }
  }
  FILE *fin, *fout;
  fin = fopen("tramvaie.in", "r");
  fout = fopen("tramvaie.out", "w");
  fscanf(fin, "%d", &t);
  for(int i=0; i<t; i++){
    int val; fscanf(fin, "%d", &val);
    fprintf(fout, "%d ", euler[val]);
  }
  fprintf(fout, "\n");
  fclose(fin);

  fclose(fout);
  return 0;
}
