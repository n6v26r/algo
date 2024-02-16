#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000000

int v[MAXSIZE+1];
long long save[MAXSIZE+1];
int n;

int main(){
  FILE *fin, *fout;
  fin=fopen("clasa1.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0;i<n;i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);
  
  for(int i=1; i<n; i++){
    long long max = save[i-1];
    for(int j=0; j<i; j++){
      if(abs(v[i]-v[j])+(j>0?save[j-1]:0)>max){
        max = abs(v[i]-v[j])+(j>0?save[j-1]:0);
      }
    }  
    save[i]=max; 
  } 

  fout=fopen("clasa1.out", "w");
  fprintf(fout, "%lld\n", save[n-1]);
  fclose(fout);
  return EXIT_SUCCESS;
}
