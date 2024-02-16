#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAXN 50

typedef struct{
  int k;
  int points;
  int score;
  int ord;
}order;

int n;

order v[MAXN];

int comp(const void *a, const void* b){
  order _a = *((const order*)a);
  order _b = *((const order*)b);

  return _b.points-_a.points;
}

int comps(const void *a, const void* b){
  order _a = *((const order*)a);
  order _b = *((const order*)b);

  if(_a.score!=_b.score) return _b.score-_a.score;
  else return _b.points-_a.points;
}

int main(){
  //freopen("file.in", "r", stdin);
  //freopen("file.out", "w", stdout);
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    int val; scanf("%d", &val); v[val-1].k = i+1, v[val-1].ord = val;
  }
  for(int i=0; i<n; i++)
    scanf("%d", &v[i].points);

  qsort(v, n, sizeof(order), comp);
  for(int i=0; i<n; i++){
    v[i].score+=n-v[i].k+1;
    v[i].score+=n-i;
    //printf("%d %d %d\n", v[i].k, v[i].points, v[i].score);
  }
  qsort(v, n, sizeof(order), comps);
  for(int i=0; i<n; i++){
    printf("%d. Kod%02d (%d)\n", i+1, v[i].ord, v[i].score);
  }
  return 0;
}
