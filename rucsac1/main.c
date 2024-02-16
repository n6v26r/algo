#include <stdio.h>
#include <string.h>

#define MAXN 5001
#define MAXG 10001

#define MAX(a, b) ((a)>(b)?(a):(b))

typedef struct{
  int val;
  int greutate;
}item;

int n;
int greutate;

int mat[2][MAXG];

item v[MAXN];

int main(){
  FILE *fin, *fout; 
  fin = fopen("rucsac1.in", "r");
  fscanf(fin, "%d%d", &n, &greutate);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d", &v[i].greutate, &v[i].val);
  }
  fclose(fin);

  for(int i=0; i<n;  i++){
    for(int g=0; g<MAXG; g++){
      int a = 0, b = 0;
      if(v[i].greutate<=g){
        a = mat[0][g-v[i].greutate]+v[i].val;
      }
      b = mat[0][g];
      
      mat[1][g] = MAX(a, b);
    }
    memcpy(mat[0], mat[1], sizeof mat[1]);
    fflush(stdout);
  }

  fout = fopen("rucsac1.out", "w");
  fprintf(fout, "%d", mat[0][greutate]);
  fclose(fout);
  return 0;
}
