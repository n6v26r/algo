// ONI 2018 9th grade
// https://kilonova.ro/problems/1522
#include <algorithm>
#include <stdio.h>

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-(a))

using namespace std;

typedef struct{
  int a;
  int b;
}_pair;

_pair v[100001];

bool comp(_pair a, _pair b){
  if(a.a<b.a) return true;
  return false;
}

int main(){
  int n, k, t;
  FILE *fin, *fout;
  fin = fopen("plaja.in", "r");
  fscanf(fin, "%d%d%d", &n, &k, &t);
  for(int i=0; i<k; i++){
    int a, b;
    fscanf(fin, "%d%d", &a, &b);
    v[i] = {a, b};
  }
  fclose(fin);

  sort(v, v+k, comp);

  long long maxval = (long long)v[0].b+(long long)t*v[0].a-t;

  _pair last = v[0];
  for(int i=1; i<k; i++){
    int s = 0;
    int a = v[i].b;
    int b = last.b;
    if(a>b) swap(a, b);
    int dif = v[i].a-last.a-1;
    int d = dif+1;
    while(d-s>1){
      int m = (d+s)/2;
      if((long long)t*m+a-(long long)t*(dif-m)-b>t) d = m;
      else s = m;
    }
    maxval = MAX(maxval, (long long)s*t+a);
    maxval = MAX(maxval, (long long)b+(dif-s)*t);
    last = v[i];
  }

  maxval = MAX(maxval, (long long)v[k-1].b+((long long)n-v[k-1].a)*t);

  fout = fopen("plaja.out", "w");
  fprintf(fout, "%lld\n", maxval);
  fclose(fout);
  return 0;
}
