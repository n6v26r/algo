#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 300000
#define MAXVAL 100007

typedef struct{
  int i;
  int val;
}querry;

int n, m, k, l;
int v[MAXN+2];
int aib[MAXVAL+2];
int ans[MAXN+1];
querry q[MAXN+2];

void update(int i, int val){
  while(i<=MAXVAL){
    aib[i]+=val;
    i+=(i&-i);
  }
}

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&-i);
  }
  return sum;
}

bool querryCmp(querry a, querry b){
  return a.val<b.val;
}

int cautBin(int k){
  int s = 0;
  int d = MAXVAL+1;
  int m;
  while(d-s>1){
    m = (s+d)/2;
    if(get(m)<k)
      s = m;
    else d = m;
  }
  return d;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("kth.in", "r");
  fscanf(fin, "%d%d%d", &n, &k, &l);
  for(int i=1; i<=n; i++){
    int val;
    fscanf(fin, "%d", &val);
    v[i] = val+50001;
  }
  fscanf(fin, "%d", &m);
  for(int i=0; i<m; i++)
    fscanf(fin, "%d", &q[i].val), q[i].i = i;
  fclose(fin);

  sort(q, q+m, querryCmp);

  for(int i=1; i<=l; i++){
    update(v[i], 1);
  }

  int pos = 1;
  for(int i=0; i<m; i++){
    int next = q[i].val;
    while(pos<next){
      update(v[pos], -1);
      update(v[pos+l], 1);
      pos++;
    }

    ans[q[i].i] = cautBin(k)-50001;
  }

  fout = fopen("kth.out", "w");
  for(int i=0; i<m; i++){
    fprintf(fout, "%d\n", ans[i]);
  }
  fclose(fout);
  return 0;
}
