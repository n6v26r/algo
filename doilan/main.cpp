// ONI 2017 8th grade
// __razv was here
#include <stdio.h>

#define MAXN 101

typedef struct baban{
  int v[MAXN];
  int sz;

  void reverse(){
    int i = sz-1;
    int j = 0;
    while(i>j){
      int a = v[i];
      v[i] = v[j];
      v[j] = a;
      i--;
      j++;
    }
  }

  __int128 div(__int128 val){
    reverse();

    __int128 t = 0;
    int i = 0;
    while(i<sz){
      t = t*10 + v[i];
      if(t/val>0){
        t = t%val;
      }
      i++;
    }
    fflush(stdout);

    reverse();
    return t;
  }
}baban;

int n;

int main(){
  FILE *fin, *fout;
  fin = fopen("doilan.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);
  
  baban mare; 
  mare.v[0] = 2;
  mare.sz = 1;

  __int128 pow = 4;
  int step = 1;
  while(step<=100){
    __int128 rest = mare.div(pow);
    if(rest==0){
      mare.v[mare.sz++] = 2;
    }
    else mare.v[mare.sz++] = 1;
    pow*=2;
    step++;
  }

  fout = fopen("doilan.out", "w");
  for(int i=mare.sz - (102-n); i>=0; i--){
    fprintf(fout, "%d", mare.v[i]);
  }
  fprintf(fout, "\n");
  fclose(fout);
}
