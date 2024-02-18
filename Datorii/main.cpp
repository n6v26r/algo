#include <iostream>
#include <stdio.h>

#define MAXSIZE 15000

int v[MAXSIZE+2];
int AIB[MAXSIZE+2];
int n;

int Compute(int pos){
  int i;
  int sum = 0;
  for(i=pos; i>0; i-=(i&-i)){
    sum += AIB[i];
  }
  return sum;
}

void Add(int start, int val){
  int i;
  for(i=start; i<=n; i+=(i&-i)){
    AIB[i] += val;
  }
}

int main(){
  int m;
  FILE *fin, *fout;
  fin = fopen("datorii.in", "r");
  fout = fopen("datorii.out", "w");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=1; i<=n; i++){
    fscanf(fin, "%d", &v[i]);
    Add(i, v[i]);
  }

  for(int i=0; i<m; i++){
    int c, a, b;
    fscanf(fin, "%d %d %d", &c, &a, &b);
    switch(c){
    case 0:
      Add(a, -b);
      break;
    case 1:
      fprintf(fout, "%d\n", Compute(b)-Compute(a-1));
      break;
    default:
      printf("Cheating!!!! You are a cheater!!!\n");
      break;
    }
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
