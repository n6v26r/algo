#include <stdio.h>

#define MAXN 200000
#define MAX(a, b) ((a)>(b)?(a):(b))

int v[MAXN+1];
int stack[MAXN+1];
int sml[MAXN+1];
int sp = -1;

static inline void readInt(int *n, FILE *fin){
  char c=fgetc(fin);
  *n=0;
  while('0'<=c && c<='9')
    (*n)=(*n)*10+c-'0', c=fgetc(fin);
}

int main(){
  int n;
  FILE *fin, *fout;
  fin=fopen("maxp.in", "r");
  fscanf(fin, "%d\n", &n);
  for(int i=0; i<n; i++){
    readInt(&v[i], fin);
    while(sp > -1 && v[stack[sp]] < v[i]){
      sml[i] += MAX(1, sml[stack[sp]]+1);
      sp--;
    }
    stack[++sp] = i;
  }
  fclose(fin);

  sp = -1;

  int max = 0;
  int max_count = 0;
  int ant;

  for(int i=n-1; i>=0; i--){
    ant = sml[i];
    sml[i] = 0;
    while(sp > -1 && v[stack[sp]] < v[i]){
      sml[i] += MAX(1, sml[stack[sp]]+1);
      sp--;
    }
    stack[++sp] = i;

    if((ant+1)*(sml[i]+1) > max){
      max = (ant+1) * (sml[i]+1);
      max_count = 1;
    }
    else if ((ant+1)*(sml[i]+1) == max)
      max_count++;
  }

  fout=fopen("maxp.out", "w");
  fprintf(fout, "%d\n%d\n", max, max_count);
  fclose(fout);
  return 0;
}
