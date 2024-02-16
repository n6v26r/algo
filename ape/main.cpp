#include <stdio.h>

#define ABS(x) ((x)>0?(x):-(x))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

typedef struct{
  int x;
  int y;
}point;

int n;
point pos;

point min;
point max;

int main(){
  FILE *fin, *fout;
  fin = fopen("ape.in", "r"); 
  fscanf(fin, "%d\n", &n);
  point ant = {0, 0};
  int arie = 0;
  for(int i=0; i<n; i++){
    char c = fgetc(fin);
    switch(c){
      case 'N':
        pos.y++;
        break;
      case 'V':
        pos.x--;
        break;
      case 'S':
        pos.y--;
        break;
      default:
        pos.x++;
        break;
    }
    // printf("%d %d\n", pos.x, pos.y); 
    arie += (pos.x*ant.y)-(pos.y*ant.x);
    ant = pos;
    
    max.x = MAX(max.x, pos.x);
    max.y = MAX(max.y, pos.y);
    min.x = MIN(min.x, pos.x);
    min.y = MIN(min.y, pos.y);
    
  }
  fclose(fin);

  arie /= 2;

  fout = fopen("ape.out", "w");
  fprintf(fout, "%d %d %d %d\n", max.x-min.x-1, max.y-min.y-1, (arie<0), ABS(arie)-n/2+1);
  fclose(fout);
}
