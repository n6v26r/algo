#include <stdio.h>
#define MAXN 100001

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct{
  int a;
  int b;
  int sum;
}secv;

int n, k, w;

int rmq[17][MAXN];
int lg[MAXN];

int main(){
  for(int i=2; i<=MAXN; i++)
    lg[i] = 1 + lg[i/2];
  FILE *fin, *fout;
  fin = fopen("ksum2.in", "r");
  fscanf(fin, "%d%d%d", &n, &k, &w);
  for(int i=0; i<n; i++){
    int val; fscanf(fin, "%d", &val);
    rmq[0][i] = (i>0?rmq[0][i-1]+val:val);
  }
  fclose(fin);

  for(int i=1; i<=lg[n]; i++){
    for(int j=0; j+(1<<(i-1))<n; j++){
      rmq[i][j] = MAX(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
    }
  }
  int maxval = -__INT_MAX__-1;
  for(int y=0; y<n-k+1; y++){
    int i = y+k-1;
    int j = MIN(y+w-1, n-1);
    int len = j-i+1;
    maxval = MAX(maxval, MAX( rmq[lg[len]][i], rmq[lg[len]][j-(1<<lg[len])+1] ) - (i>0?rmq[0][y-1]:0));
  }

  fout = fopen("ksum2.out", "w");
  fprintf(fout, "%d", maxval);
  fclose(fout);
  return 0;
}
