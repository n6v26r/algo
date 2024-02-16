#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

int apple[MAXSIZE*MAXSIZE+77][2], a;
int obs[MAXSIZE*MAXSIZE+77][2], o;
int n, m, z, p;

int main(){
  FILE *fin, *fout;
  fin = fopen("map.in", "r");
  fscanf(fin, "%d %d", &p, &z);
  fgetc(fin);
  char c = fgetc(fin); 
  int lin=0;
  int col=0;
  while(c!=EOF){
    while(c!='\n'){
      switch(c){
        case '#':
          obs[o][0] = lin;
          obs[o++][1] = col;
          break;
        case '.':
          apple[a][0] = lin;
          apple[a++][1] = col;
        default:
          break;
      }
      col++;
      c=fgetc(fin);
    }
    lin++;
    col = 0;
    c=fgetc(fin);
  }
  fclose(fin);

  fout = fopen("snake.in", "w");
  fprintf(fout, "%d\n%d %d\n%d\n", p, lin, z, o);
  for(int i=0; i<o; i++){
    fprintf(fout, "%d %d\n", obs[i][0]+1, obs[i][1]+1);
  }
  fprintf(fout, "%d\n", a);
  for(int i=0; i<a; i++){
    fprintf(fout, "%d %d\n", apple[i][0]+1, apple[i][1]+1);
  }
  fclose(fout);
}
