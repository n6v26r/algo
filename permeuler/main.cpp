#include <stdio.h>
#include <string.h>

#define MAXN 10000003

int fa[20];
int fb[20];

char isPerm(int a, int b){
  memset(fa, 0, sizeof(fa));
  memset(fb, 0, sizeof(fb));
  while(a>0){
    fa[a%10]++;
    a/=10;
  }
  while(b>0){
    fb[b%10]++;
    b/=10;
  }
  for(int i=0; i<10; i++){
    if(fa[i]!=fb[i])
      return 0;
  }
  return 1;
}

int euler(int n){
  int e = n;
  int d = 2;
  while(n>1){
    if(n%d==0){
      e = e/d*(d-1);
      while(n%d==0) n/=d;
    }
    d++;
    if(d*d>n) d = n;
  }
  return e;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("permeuler.in", "r");
  double minval = MAXN+1;
  int best = 0;
  char c = fgetc(fin);

  while(c!='\n' && c!=EOF){
    ungetc(c, fin);
    int val; fscanf(fin, "%d ", &val);
    int e = euler(val);
    printf("%d %d\n", val, e);
    if( isPerm(val, e) && (double)val/e<minval){minval = (double)val/e; best = val;}
    c = fgetc(fin);
  }
  fclose(fin);

  fout = fopen("permeuler.out", "w");
  fprintf(fout, "%d\n", best);
  fclose(fout);
  return 0;
}
