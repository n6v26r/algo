#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXN 20
#define MAXM 15

bool reduced[MAXM+1];
short medicine[MAXN+1];
int fullPrice[MAXM+1];
int priceMask[MAXM+1];
int v[MAXM+1];
int used;
int n, m;

int getmask(int *v, int size){
  int n=0;
  for(int i=0; i<size; i++){
    n+=(1<<v[i]); 
  }
  return n;
}

void add(int *a, int b){
  int newa = (*a)^b;
  (*a)=newa;
  if(newa!=((*a)|b)){
    (*a) += (1<<23);
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("reteta1.in", "r");
  fscanf(fin, "%d %d\n", &n, &m);
  for(int i=0; i<m; i++){
    int size, type;
    fscanf(fin, "%d %d\n", &type, &size);
    int new[MAXN+1];
    for(int j=0; j<size; j++){
      fscanf(fin, "%d", &new[j]);
      new[j]--;
      priceMask[i]+=(1<<new[j]);
    }
    v[i] = getmask(new, size);
    reduced[i] = type==2?true:false;
  }
  for(int i=0; i<n; i++){
    fscanf(fin, "%hd", &medicine[i]);
  }
  for(int i=0; i<m; i++){
    int mask = priceMask[i];
    int step=0;
    int price=0;
    while(mask>0){
      int lastDigit = mask&1;
      mask=(mask>>1);
      price += medicine[step]*lastDigit;
      step++;
    }
    fullPrice[i]=price;
  }
  fclose(fin);
  int max = (1<<m);
  float bestPrice = (float)INT_MAX;
  for(int i=0; i<max; i++){
    int num = i;
    
    int step = 0;
    float sum=0;
    used = 0;
    while(num>0){
      bool lastDigit = num&1;
      if(lastDigit){add(&used, v[step]);sum+=reduced[step]?(float)fullPrice[step]/2:fullPrice[step];}
      num=num>>1;
      step++;
    }
    if(used == (1<<n)-1){
      if(bestPrice>sum)
        bestPrice=sum;
    }
  }
  fout = fopen("reteta1.out", "w");
  fprintf(fout, "%.1f\n", bestPrice);
  fclose(fout);
}
