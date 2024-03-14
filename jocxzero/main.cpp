// ONI 2018 8th grade
// https://www.pbinfo.ro/probleme/2505/jocxzero
#include <iostream>

#define MAXM 10002
#define MAXN 102

typedef struct{
  int a;
  int b;
}intPair;

int p, n, m, k;

int mat[MAXN][MAXM];

intPair save[MAXM];

typedef struct {
  int sumlin[MAXN][MAXM];
  int sumcol[MAXN][MAXM];
  int sumdig1[MAXN][MAXM];
  int sumdig2[MAXN][MAXM];
}dp;

dp x;
dp y;

intPair get(int limit){
  int sumx = 0, sumy = 0;
  for(int i=0; i<n; i++){
    sumx+=x.sumlin[i][limit-1]+x.sumdig1[i][limit-1]+x.sumdig2[i][limit-1];
    sumy+=y.sumlin[i][limit-1]+y.sumdig1[i][limit-1]+y.sumdig2[i][limit-1];
  }
  for(int j=0; j<limit-1; j++){
    sumx+=x.sumcol[n-1][j]+x.sumdig1[n-1][j]+x.sumdig2[0][j];
    sumy+=y.sumcol[n-1][j]+y.sumdig1[n-1][j]+y.sumdig2[0][j];
  }
  sumx += x.sumcol[n-1][limit-1];
  sumy += y.sumcol[n-1][limit-1];

  return (intPair){sumx, sumy};
}

int main(){
  FILE *fin, *fout;
  fin = fopen("jocxzero.in", "r");
  fscanf(fin, "%d%d%d%d\n", &p, &n, &m, &k);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      char c = fgetc(fin);
      mat[i][j] = (c=='X'?1:0);
      x.sumlin[i][j] = (j>0 && mat[i][j]?x.sumlin[i][j-1]+mat[i][j]:mat[i][j]);
      x.sumcol[i][j] = (i>0 && mat[i][j]?x.sumcol[i-1][j]+mat[i][j]:mat[i][j]);
      x.sumdig1[i][j] = (i>0 && j>0 && mat[i][j]?x.sumdig1[i-1][j-1]+mat[i][j]:mat[i][j]);

      y.sumlin[i][j] = (j>0 && !mat[i][j]?y.sumlin[i][j-1]+!mat[i][j]:!mat[i][j]);
      y.sumcol[i][j] = (i>0 && !mat[i][j]?y.sumcol[i-1][j]+!mat[i][j]:!mat[i][j]);
      y.sumdig1[i][j] = (i>0 && j>0 && !mat[i][j]?y.sumdig1[i-1][j-1]+!mat[i][j]:!mat[i][j]);
    }
    fgetc(fin);
  }

  for(int i=n-1; i>=0; i--){
    for(int j=0; j<m; j++){
      x.sumdig2[i][j] = (i<n-1 && j>0 && mat[i][j]? x.sumdig2[i+1][j-1]+mat[i][j] : mat[i][j]);
      y.sumdig2[i][j] = (i<n-1 && j>0 && !mat[i][j]? y.sumdig2[i+1][j-1]+!mat[i][j] : !mat[i][j]);
    }
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      x.sumlin[i][j] = (x.sumlin[i][j]>=k)+(j>0?x.sumlin[i][j-1]:0);
      x.sumcol[i][j] = (x.sumcol[i][j]>=k)+(i>0?x.sumcol[i-1][j]:0);
      x.sumdig1[i][j] = (x.sumdig1[i][j]>=k)+(j>0 && i>0?x.sumdig1[i-1][j-1]:0);

      y.sumlin[i][j] = (y.sumlin[i][j]>=k)+(j>0?y.sumlin[i][j-1]:0);
      y.sumcol[i][j] = (y.sumcol[i][j]>=k)+(i>0?y.sumcol[i-1][j]:0);
      y.sumdig1[i][j] = (y.sumdig1[i][j]>=k)+(j>0 && i>0?y.sumdig1[i-1][j-1]:0);
    }
  }

  for(int i=n-1; i>=0; i--){
    for(int j=0; j<m; j++){
      x.sumdig2[i][j] = (x.sumdig2[i][j]>=k)+(i<n-1 && j>0? x.sumdig2[i+1][j-1]:0);
      y.sumdig2[i][j] = (y.sumdig2[i][j]>=k)+(i<n-1 && j>0? y.sumdig2[i+1][j-1]:0);
    }
  }

  fout = fopen("jocxzero.out", "w");
  if(p==1){
    intPair p = get(m);
    fprintf(fout, "%d %d\n", p.a, p.b);
  }
  else{
    for(int i=1; i<=m; i++){
      save[i] = get(i);
    }
    int q;
    fscanf(fin, "%d\n", &q);
    for(int i=0; i<q; i++){
      char c = fgetc(fin);
      int k; fscanf(fin, "%d\n", &k);
      int s = 1;
      int d = m;

      while(d-s>1){
        int m = (s+d)/2;
        if(c=='X'){
          if(save[m].a>k) d = m;
          else s = m;
        }
        else{
          if(save[m].b>k) d = m;
          else s = m;
        }
      }
      if( (c=='X' && save[s].a==k ) || (c=='0' && save[s].b==k)) {
        int upper = s;
        s = 0;
        d = m-1;
        while(d-s>1){
          int m = (s+d)/2;
          if(c=='X'){
            if(save[m].a<k) s = m;
            else d = m;
          }
          else{
            if(save[m].b<k) s = m;
            else d = m;
          }
        }
        fprintf(fout, "%d\n", upper-d+1);
      }
      else fprintf(fout, "0\n");
    }
  }
  fclose(fout);
  fclose(fin);
  return 0;
}
