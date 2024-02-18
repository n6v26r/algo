#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 500
#define DIR 4

short mat[MAXSIZE+3][MAXSIZE+3];

char dirLin[DIR] = {-1, 0, 1, 0};
char dirCol[DIR] = {0, 1, 0, -1};

// FloodFill
void ff(short lin, short col, int fillValue){
  if(mat[lin][col]!=0) return;
  mat[lin][col] = (short)fillValue;
  for(char i=0; i<DIR; i++){
    ff(lin+dirLin[i], col+dirCol[i], fillValue);
  }
}

bool inlist(char a, char *v, char n){
  for(char i=0; i<n; i++){
    if(a == v[i])
      return true;
  }
  return false;
}

int main(){
  short n, m;
  FILE *fin, *fout;
  fin=fopen("tari.in", "r");
  fscanf(fin, "%hd %hd\n", &n, &m);

  for(short i=1; i<=n; i++){
    for(short j=1; j<=m; j++){
      mat[i][j] = fgetc(fin) - '0';
    }
    fgetc(fin);
  }
  fclose(fin);
  /// bordare
  for(short i=0; i<=n+1; i++){
    mat[i][0]=mat[i][m+1]=1;
  }
  for(short j=0; j<=m+1; j++){
    mat[0][j]=mat[n+1][j]=1;
  }
  /// FloodFill
  short countryCounter = 0;
  for(short i=1; i<=n; i++){
    for(short j=1; j<=m; j++){
      if(!mat[i][j]) countryCounter++;
      ff(i, j, -countryCounter);
    }
  }
  char maxnext = 0;

  for(short i=0; i<=n+1; i++){
    for(short j=0; j<=m+1; j++){
      if(mat[i][j]!=1) continue;
      char next = 0;
      char metbefore[] = {0, 0, 0, 0};
      for(char vecin=0; vecin<DIR; vecin++){
        if(mat[i+dirLin[vecin]][j+dirCol[vecin]]<0 && !inlist(mat[i+dirLin[vecin]][j+dirCol[vecin]], metbefore, vecin)) {next++; metbefore[vecin] = mat[i+dirLin[vecin]][j+dirCol[vecin]];}
        if(next>maxnext) maxnext = next;
      }
    }
  }

  fout = fopen("tari.out","w");
  fprintf(fout, "%d\n", countryCounter-maxnext+1);
  fclose(fout);
}
