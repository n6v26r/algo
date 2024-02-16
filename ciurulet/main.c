#include <stdio.h>

#define MAXN 1000001

int n;
char v[MAXN];
char w[MAXN];

void setOnes(int i){
  for(int d=i; d<=n; d+=i){
    w[d] = 1;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("ciurulet.in", "r");
  fscanf(fin, "%d\n", &n);
  for(int i=2; i<=n; i++){
    char c = fgetc(fin);
    if(c!='?') v[i] = c-'0';
    else v[i] = 2;
  }
  fclose(fin);

  for(int i=2; i<=n; i++){
    if(v[i]==1) setOnes(i);
  }
  
  int sum = 0;
  for(int i=2; i<=n; i++){
    if(v[i]==2){
      int j;
      for(j=2*i; j<=n; j+=i) if(v[j]==1) break;
      if(j>n)
        setOnes(i);
    } 
    sum+=w[i];
  }

  fout = fopen("ciurulet.out", "w");
  fprintf(fout, "%d\n", sum);
  for(int i=2; i<=n; i++){
    fputc(w[i]+'0', fout);
  }
  fprintf(fout, "\n");
  fclose(fout);
  return 0;
}
