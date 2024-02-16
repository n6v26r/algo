#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
 
#define MAXN 6000
#define MAXV 60000
#define BUFSIZE (128 * 1024)

char rbuf[BUFSIZE], wbuf[BUFSIZE];
 
int v[MAXN+1];
int f[MAXV+1];

int compInt(const void *a, const void *b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  return _a-_b;
}

void readInt(int *n, FILE *fin){
  *n = 0;
  char c=fgetc(fin);
  while(!isdigit(c))
    c=fgetc(fin);
  while(isdigit(c))
    *n=(*n)*10+c-'0', c=fgetc(fin);
}
 
char triunghi(int a, int b, int c){
  return ((a+b>c) && (b+c)>a && (c+a)>b);
}
 
int main(){
  int n;
  FILE *fin, *fout;
  fin=fopen("nrtri2.in", "r");
  setvbuf( fin, rbuf, _IOFBF, BUFSIZE);
  fscanf(fin, "%d\n", &n);
  for(int i=0; i<n; i++){
    int val;
    readInt(&val, fin);
    v[i] = val;
  }
  fclose(fin);

  qsort(v, n, sizeof(int), compInt);

  for(int i=0; i<n; i++){
    for(int j=i+1; j<n && v[i]+v[j]<=MAXV; j++){
      f[v[i] + v[j]]++;
    }
  }
  for(int i=1; i<=MAXV; i++){
    f[i] += f[i-1];
  }

  long long tri = (long long)n*(n-1)*(n-2)/6;
  for(int i=0; i<n; i++){
    tri -= f[v[i]];
  }
    
  fout=fopen("nrtri2.out", "w");
  setvbuf(fout, wbuf, _IOFBF, BUFSIZE);
  fprintf(fout, "%lld\n", tri);
  fclose(fout);
  return 0;
}
