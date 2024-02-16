#include <stdio.h>

#define R 60
#define MIN(a, b) ((a)>(b)?(b):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))

int t, n, m;
long long c[R];
long long sp[R];

int fib[60] = {1, 1, 2, 3, 5, 8, 3, 1, 4, 5, 9, 4, 3, 7, 0, 7, 7, 4, 1, 5, 6, 1, 7, 8, 5, 3, 8, 1, 9, 0, 9, 9, 8, 7, 5, 2, 7, 9, 6, 5, 1, 6, 7, 3, 0, 3, 3, 6, 9, 5, 4, 9, 3, 2, 5, 7, 2, 9, 1, 0};

static inline int num(int i, int j){
  long long pos;
  if(!(i%2))
    pos = (long long)i*m+j;
  else pos = (long long)(i+1)*m-j-1;
  return fib[pos%R];
}

int main(){
  FILE *fin, *fout;
  fin = fopen("cartofi.in", "r");
  fscanf(fin, "%d%d%d", &t, &n, &m);


  int lin = MIN(n, R);
  int col = MIN(m, R);

  for(int i=0; i<lin; i++){
    int rep = (n)/lin+((n%lin)>=(i+1)?1:0);
    for(int j=0; j<col; j++){
      c[j] += (long long)num(i, j)*rep;
    }
  }

  fout = fopen("cartofi.out", "w");
  if(t==2){
    long long sum = 0;
    for(int i=0; i<lin; i++) sum+=c[i];
    sum*=(n/lin);
    int i=(n/lin)*lin;
    while(i<n) sum+=c[i%lin], i++;
    long long max = 0;
    if(sum>max)
      max = sum;

    while(i<MIN(n+lin, m)){
      sum+=c[i%R];
      sum-=c[(i-n)%R];
      if(sum>max) max = sum;
      i++;
    }
    fprintf(fout, "%lld\n", max);
  }
  if(t==3){ int q;
    long long sum = 0;
    for(int i=0; i<col; i++) sum+=c[i], sp[i] = (i>0?sp[i-1]:0) + c[i];
    printf("\n");
    fscanf(fin, "%d", &q);
    for(int i=0; i<q; i++){
      int a, b; fscanf(fin, "%d%d", &a, &b); a--; b--;
      if(a/col+((a+(a==0))%col?1:0)<b/col){
        fprintf(fout, "%lld\n", sp[col-1]-(a>0?sp[(a-1)%col]:0)+sum*(-(a/col+((a+(a==0))%col?1:0)-b/col))+sp[b%col]);
      }
      else{
        if((a-1)%col>b%col || (b-a+1)>=col)
          fprintf(fout, "%lld\n", sum+sp[b%col]-(a>0?sp[(a-1)%col]:0));
        else{
          fprintf(fout, "%lld\n", sp[b%col]-(a>0?sp[(a-1)%col]:0));
        }
      }
    }
  }
  fclose(fin);
  if(t==1){
    long long zeros = (long long)n*m/R*4;
    for(int i=0; i<(long long)n*m%R; i++) zeros+=!fib[i];
    fprintf(fout, "%lld\n", zeros);
  }
  fclose(fout);
  return 0;
}
