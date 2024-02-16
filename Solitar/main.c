#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n;
struct{int start; int end;}v[MAXN+1];
int size=-1;

int frecv[MAXN+1];

int main(){
  FILE *fin, *fout;
  fin = fopen("solitar.in", "r");
  fscanf(fin, "%d", &n);
  int last = -2;
  for(int i=0; i<n; i++){
    int val;
    fscanf(fin, "%d", &val);
    if(val==last-1){
      v[size].start=val;
    }
    else{
      size++;
      v[size].end = v[size].start = val;
    }
    last = val;
  }
  fclose(fin);

  int totalMoves = 0;
  int remain = size+1;

  while(remain>1){
    for(int i=size; i>=0; i--){
      if(v[i].start==-1) continue;
      frecv[v[i].start]=1;
      if(frecv[v[i].end+1]==1){
        totalMoves++;
        remain--;
      }
      else{
        v[i].start = -1;
        if(i>0) totalMoves++;
      }

      if(remain==1)
        break;
    }
  }

  fout = fopen("solitar.out", "w");
  fprintf(fout, "%d\n", totalMoves);
  fclose(fout);
  return 0;
}
