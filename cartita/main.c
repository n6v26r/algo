// this crappy piece of code is provided to u
// by __razv

// ONI 2021 - BARAJ: https://www.pbinfo.ro/probleme/3759/cartita
#include <stdio.h>

#define MAXN 100001
#define MAXU 300001
#define MAXQ 200001

#define MIN(a, b) ((a)<(b)?(a):(b))

int rmq[30][MAXN];
int lg[MAXN];

int mp[MAXN];
int mn[MAXN];

int n, u, q;

int main(){

  for(int i=2; i<MAXN; i++)
    lg[i] = 1 + lg[i/2];

  FILE *fin, *fout;
  fin = fopen("cartita.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &rmq[0][i]);
  }
  fscanf(fin, "%d", &u);

  int sumx = 0;
  for(int i=0; i<u; i++){
    int pos, x, k; fscanf(fin, "%d%d%d", &pos, &x, &k); pos--;
    
    sumx += x;
   
    mn[pos-1] -= k;
    mp[pos+1] += k;
  }

  int sum = 0, sumtotal = 0;
  for(int i=n-1; i>=0; i--){
    sum += mn[i];
    sumtotal += sum;
    rmq[0][i] += sumtotal;
  }
  
  sum = sumtotal = 0;
  for(int i=0; i<n; i++){
    sum += mp[i];
    sumtotal += sum;
    rmq[0][i] += sumtotal + sumx;
  } 

  for(int i=1; i<=lg[n]; i++){
    for(int j=0; j+(1<<(i-1))<n; j++){
      rmq[i][j] = MIN( rmq[i-1][j], rmq[i-1][j+(1<<(i-1))] );
    }
  }
  
  fscanf(fin, "%d", &q);

  fout = fopen("cartita.out", "w");
  for(int p=0; p<q; p++){
    int i, j; fscanf(fin, "%d%d", &i, &j); i--; j--;
    fprintf(fout, "%d\n", MIN( rmq[lg[j-i+1]][i], rmq[lg[j-i+1]][j-(1<<(lg[j-i+1]))+1] ));
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
