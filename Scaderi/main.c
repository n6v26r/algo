#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

long long pascal[MAXSIZE+1][MAXSIZE+1];
int S[MAXSIZE+1];
int sir[MAXSIZE+1];

void genPascal(int size){
  pascal[0][0] = 1;
  for(int j=1; j<size; j++){
    pascal[j][0] = 1;
    for(int i=1; i<j; i++){
      pascal[j][i] = pascal[j-1][i]+pascal[j-1][i-1];
    }
    pascal[j][j] = 1;
  }
}

long long Process(int *v, int size){
  int sign = 1;
  long long result = 0;
  for(int i=0; i<size; i++){
    result += sign*v[i]*pascal[size-1][i];
    sign = sign*-1;
  }
  return result;
}

int main(){
  genPascal(51);
  
  int t;
  int n, s, p;
  FILE *fin, *fout;
  fin = fopen("scaderi.in", "r");
  fout = fopen("scaderi.out", "w");
  for(int i=0; i<MAXSIZE; i++){
    fscanf(fin, "%d", &S[i]);
  }
  fscanf(fin, "%d", &t);
  for(int i=0; i<t; i++){
    fscanf(fin, "%d %d %d", &n, &s, &p); s--;
    for(int i=0; i<n; i++){
      sir[i] = S[s];
      s=(s+p)%MAXSIZE;
    }
    fprintf(fout, "%lld\n", Process(sir, n));
  }
  fclose(fin);
  fclose(fout);
   
  return EXIT_SUCCESS;
}
