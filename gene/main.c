#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 500
#define MIN(a, b) ((a)>(b)?(b):(a))

int c, n, m, k;

int sim(const char* a, const char* b){
  int r = 0;
  for(int i='a'; i<='z'; i++){
    r += MIN(a[i], b[i]);
  }
  return r;
}

void read(char *a, FILE *fin){
  char c = fgetc(fin);
  int i=0;
  while(c!='\n' && c!=EOF){
    a[i++]=c;
    c=fgetc(fin);
  }
  a[i]='\0';
}

void frecv(const char* a, char* f){
  for(int i=0; a[i]!='\0'; i++){
    f[a[i]]++;
  }
}

char gigel[128];
char other[MAXSIZE*MAXSIZE+2][128];
char f[128] = "";
char f1[128] = "";
int map[MAXSIZE+1][MAXSIZE+1];
int mat[MAXSIZE+1][MAXSIZE+1];
struct{int lin; int col;} coord;

int square(int i, int j, int lin, int col){
  return (mat[lin][col]-(j>0?mat[lin][j-1]:0)-(i>0?mat[i-1][col]:0)+((i>0 && j>0)?mat[i-1][j-1]:0));
}

bool hasSqare(int l){
  for(int i=0; i<n-l+1; i++){
    for(int j=0; j<m-l+1; j++){
      if(square(i, j, i+l-1, j+l-1)==l*l){
        coord.lin = i;
        coord.col = j;
        return true;
      }
    }
  }
  return false;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("gene.in", "r");
  fscanf(fin, "%d\n %d %d %d\n", &c, &n, &m, &k);
  read(gigel, fin);
  frecv(gigel, f);
  int max = 0;
  for(int i=0; i<n; i++){
   for(int j=0; j<m; j++){
      read(other[i*n+j], fin);
      memset(f1, 0, sizeof(f1));
      frecv(other[i*n+j], f1);
      map[i][j] = sim(f, f1);
      if(map[i][j]>max)
        max = map[i][j];

      mat[i][j] = (map[i][j]>k) + ((i>0)?mat[i-1][j]:0)+((j>0)?mat[i][j-1]:0)-((i>0 && j>0)?mat[i-1][j-1]:0);
    }
  }
  fclose(fin);

  fout = fopen("gene.out", "w");
  if(c==1){
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        if(map[i][j]==max)
          fprintf(fout, "%d %d %s\n", i+1, j+1, other[i*n+j]);
      }
    }
  }
  else{
    int s = 0, d = MIN(n, m)+1;
    int m;
    while(d-s>1){
      m = (s+d)/2;
      if(!hasSqare(m))
        d = m;
      else s = m;
    }
    fprintf(fout, "%d %d %d\n", coord.lin+1, coord.col+1, s);
  }
  fclose(fout);
  return EXIT_SUCCESS;
}
