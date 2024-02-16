#include <stdio.h>

#define MAXN 20

int n, k;
int v[MAXN+1];

int main(){
  FILE *fin, *fout;
  fin = fopen("adunscad.in", "r");
  fscanf(fin, "%d%d", &k, &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  fout = fopen("adunscad.out", "w");
  char sol = 0;
  for(int i=0; i<=(1<<(n+1))-1; i++){
    int cp = i;
    int j = 0;
    int sum=0;
    while(j<n){
      sum+=(cp&(1<<(n-j))?v[j]:-v[j]);
      j++;
    }
    if(sum==k){
      int j = 0;
      while(j<n){
        if(j==0){
          if(!(cp&(1<<(n-j))))
            fprintf(fout, "-");
          fprintf(fout, "%d", v[j]);
        }
        else
          fprintf(fout, "%c%d", (cp&(1<<(n-j))?'+':'-'), v[j]);
        j++;
      }
      sol = 1;
      break;
    }
  }
  if(!sol) fprintf(fout, "0\n");
  fclose(fout);
  return 0;
}
