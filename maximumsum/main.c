#include <stdio.h>

#define MAXN 327
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int n;
int mat[MAXN][MAXN];

int zone(int i, int j, int l, int c){
  printf("=>%d %d ", mat[l][c], mat[i-1][j-1]);
  return mat[l][c] - (j>0?mat[l][j-1]:0) - (i>0?mat[i-1][c]:0) + (i>0 && j>0?mat[i-1][j-1]:0);
}

int main(){
  FILE *fin, *fout;
  fin = fopen("maximumsum.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fscanf(fin, "%d", &mat[i][j]);
      mat[i][j] += (i>0?mat[i-1][j]:0) + (j>0?mat[i][j-1]:0) - (i>0&&j>0?mat[i-1][j-1]:0);
    }
  }
  fclose(fin);
  
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      printf("%02d ", mat[i][j]);
    }
    printf("\n");
  } fflush(stdout);

  int sum = mat[n-1][n-1];
  int topl = 0, topc = 0;
  int btml = n-1, btmc = n-1;
  int max = sum;
  while(!(topl==btml && topc==btmc)){
    int t = zone(topl, topc, topl, btmc);
    int r = zone(topl, btmc, btml, btmc);
    int b = zone(btml, topc, btml, btmc);
    int l = zone(topl, topc, btml, topc);
    printf("%d:%d:%d:%d\n", t, r, b, l);
    int min = MIN(MIN(t, r), MIN(b, l));
    if(min==t) topl++;
    else if(min==r) btmc--;
    else if(min==b) btml--;
    else if(min==l) topc++;

    sum-=min;
    max = MAX(max, sum);
    printf("%d %d %d %d\n", topl, topc, btml, btmc); fflush(stdout);
    if(topl>1)
      break;
  }

  fout = fopen("maximumsum.out", "w");
  fprintf(fout, "%d\n", max);
  fclose(fout);
  return 0;
}
