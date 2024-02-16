#include <stdio.h>	
#include <stdbool.h>	
#include <string.h>
	
#define MAXSIZE 700
	
typedef struct{
  short start;
  short end;
}Interval;
	
short mat[MAXSIZE+1][MAXSIZE+1];
	
Interval v[MAXSIZE+1];
Interval h[MAXSIZE+1];
	
bool isConvex = true;
	
Interval newInterval(short a, short b){
  Interval newInterval = {a, b};
  return newInterval;
}
	
short sqaresIn(Interval TopLeft, Interval BottomRight){	
  if(TopLeft.end < 0 || TopLeft.start < 0 || BottomRight.end < 0 || BottomRight.start < 0) return 0;
  return mat[BottomRight.start][BottomRight.end]-
         ((TopLeft.start>0)? mat[TopLeft.start-1][BottomRight.end] : 0)-
         ((TopLeft.end>0)? mat[BottomRight.start][TopLeft.end-1] : 0)+
         ((TopLeft.start>0 && TopLeft.end>0) ? mat[TopLeft.start-1][TopLeft.end-1] : 0);
}
	
int main() {	
  memset(h, -1, sizeof(h));
  memset(v, -1, sizeof(v));
 
  short n, m;	
  FILE *fin, *fout;
  fin = fopen("convex.in", "r");
  fscanf(fin, "%hd%hd\n", &n, &m);
  for(short i=0; i<n; i++){
    for(short j=0; j<m; j++){
      switch (fgetc(fin)) {
        case 'A':
          mat[i][j]=((i>0) ? mat[i-1][j] : 0)+((j>0) ? mat[i][j-1] : 0)-((i>0 && j>0) ? mat[i-1][j-1] : 0);
          break;
        case 'N':
          if(h[i].start==-1) h[i].start = j;
          if(h[i].end == -1 || h[i].end == j-1) h[i].end = j;
          else {isConvex = false; goto print;}
          
          if(v[j].start==-1) v[j].start = i;
          if(v[j].end == -1 || v[j].end == i-1) v[j].end = i;
          else {isConvex = false; goto print;}
 
          mat[i][j]=((i>0) ? mat[i-1][j] : 0)+((j>0) ? mat[i][j-1] : 0)-((i>0 && j>0) ? mat[i-1][j-1] : 0)+1;	
          break;
        default:
          printf("Cheating!\n");
          return 0;
          break;
      }
    }
    fgetc(fin);
  }
  fclose(fin);
 
  for(int i=0; i<n; i++){	
    if(isConvex)
      for(int j=0; j<m; j++){
        if(sqaresIn(newInterval(i, j), newInterval(i, j))<1) continue;
        Interval y = v[j];
        Interval x = h[i];
        short excluded = sqaresIn(newInterval(y.end+1, 0), newInterval(n-1, x.start-1))+
                         sqaresIn(newInterval(0, 0), newInterval(y.start-1, x.start-1))+
                         sqaresIn(newInterval(0, x.end+1), newInterval(y.start-1, m-1))+
                         sqaresIn(newInterval(y.end+1, x.end+1), newInterval(n-1, m-1));
        if(excluded>0){
          isConvex = false;
          break;
        }
      }
  }
	
  print:
	
  fout = fopen("convex.out", "w");
  fprintf(fout, "%d\n", isConvex);
  fclose(fout);
  return 0;
}
