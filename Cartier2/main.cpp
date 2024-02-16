#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;

#define MAXN 1000001
#define MAX(a, b) ((a>b)?(a):(b))
#define MIN(a, b) ((a<b)?(a):(b))

int n;

int ciur[MAXN];

int a[MAXN];
int b[MAXN];

int da[100000];
int db[100000];

int maxh;
int maxhcount;

int maxsecv;

int slen;

void readInt(int *n, FILE* fin){
  *n = 0;
  char c = fgetc(fin);
  while(!isdigit(c)) c = fgetc(fin);
  while(isdigit(c)){
    (*n)=(*n)*10+c-'0';
    c = fgetc(fin);
  }
}

int main(){
  memset(a, -1, sizeof(a));
  memset(da, 127, sizeof(da));
  memset(db, -1, sizeof(db));
  for(int i=1; i*i<=MAXN; i++){
    for(int j = i*i; j<MAXN; j+=i){
      ciur[j] = i;
    }
  }
  FILE *fin, *fout;
  fin = fopen("cartier2.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    int val; readInt(&val, fin);
    int d = ciur[val];
    int h = val/d;
    int len = d;
    if(h>maxh) maxh = h, maxhcount=1;
    else if(h==maxh) maxhcount++;

    slen+=len;

    if(a[h]==-1) a[h] = i;
    b[h] = i;

    //printf("%d %d %d\n", val, a[val], b[val]);
  }
  fclose(fin);

  memset(ciur, 0, sizeof(ciur));
  int p = 0;
  for(int i=2; i<MAXN; i++){
    if(!ciur[i]){
      for(int j=i; j<MAXN; j+=i){
        ciur[j] = 1;
        if(a[j]>-1){
          da[p] = MIN(da[p], a[j]);
          db[p] = MAX(db[p], b[j]);
        }
      }
      if(da[p]<MAXN && da[p]>-1){
        if(db[p]-da[p]+1>maxsecv) maxsecv = db[p]-da[p]+1;
      }
      p++;
    }
  }


  fout = fopen("cartier2.out", "w");
  fprintf(fout, "%d\n%d\n%d\n", maxhcount, slen, maxsecv);
  fclose(fout);
  return 0;
}
