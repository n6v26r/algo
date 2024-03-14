#include <iostream>
#include <algorithm>
#define MAXN 200001

using namespace std;

double v[MAXN];
int n, k;

int get(double len){
  int cnt = 0;
  for(int i=0; i<n; i++){
    cnt++;
    double _end = v[i]+len;
    double start = v[i];
    while(i<n && start+v[i+1]-v[i]<_end){
      start += v[i+1]-v[i];
      i++;
    }
  }
  return cnt;
}

bool comp(double a, double b){
  return (a<b);
}

int main(){
  FILE *fin, *fout;
  fin = fopen("2d.in", "r");
  fscanf(fin, "%d%d", &n, &k); double y;
  for(int i=0; i<n; i++){
    fscanf(fin, "%lf%lf", &v[i], &y);
  }
  fclose(fin);

  sort(v, v+n, comp);

  double s = 0.999;
  double d = 2000001;
  while(d-s>0.001f){
    double m = (s+d)/2;
    if(get(m)>k) s = m;
    else d = m;
  }

  fout = fopen("2d.out", "w");
  fprintf(fout, "%.3lf\n", d);
  fclose(fout);
}
