//ONI 2013 9th grade
//https://kilonova.ro/problems/1402

#include <stdio.h>
#define MAXN 5001

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))

int v[MAXN];

int spmin[MAXN];
int spmax[MAXN];

int dpmin[MAXN];
int dpmax[MAXN];

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("split.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    spmin[i] = (i>0?MIN(spmin[i-1], v[i]):v[i]);
    spmax[i] = (i>0?MAX(spmax[i-1], v[i]):v[i]);
  }
  for(int i=n-1; i>=0; i--){
    dpmin[i] = (i<n-1?MIN(dpmin[i+1], v[i]):v[i]);
    dpmax[i] = (i<n-1?MAX(dpmax[i+1], v[i]):v[i]);
  }
  fclose(fin);

  int maxsum = 0;

  int bestj, bestesti, bestestk;

  for(int j=3; j<n-2 ; j++){
    int minval = __INT_MAX__;
    int maxval = 0;
    int Ssumax = 0;
    int besti;
    for(int i=j-2; i>0; i--){
      minval = MIN(minval, v[i+1]);
      maxval = MAX(maxval, v[i+1]);

      if(Ssumax<=maxval-minval+spmax[i]-spmin[i]){
        Ssumax = maxval-minval+spmax[i]-spmin[i];
        besti = i;
      }
    }
    minval = __INT_MAX__;
    maxval = 0;
    int bestk;
    int Dsumax = 0;
    for(int k=j; k<n-1; k++){
      minval = MIN(minval, v[k]);
      maxval = MAX(maxval, v[k]);

      if(Dsumax<maxval-minval+dpmax[k+1]-dpmin[k+1]){
        Dsumax = maxval-minval+dpmax[k+1]-dpmin[k+1];
        bestk = k;
      }
    }

    if(maxsum<Ssumax+Dsumax){
      maxsum = Ssumax+Dsumax;
      bestj = j;
      bestesti = besti;
      bestestk = bestk;
    }
  }

  fout = fopen("split.out", "w");
  fprintf(fout, "%d\n%d %d %d\n", maxsum, bestesti+1, bestj, bestestk+1);
  fclose(fout);
  return 0;
}
