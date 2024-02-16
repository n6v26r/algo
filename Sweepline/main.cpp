#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000001

typedef struct{
  int val;
  int ind;
}p;

int n;
p v[2*MAXN];
set <int> st;
int alone[MAXN];

bool cmp(p a, p b){
  return a.val < b.val;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("lifeguards.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    int a, b;
    fscanf(fin, "%d%d", &a, &b);
    v[i*2] = (p) {a, i};
    v[i*2+1] = (p) {b, i};
  }
  fclose(fin);

  sort(v, v+2*n, cmp);

  int last;
  int total=0;
  for(int i=0; i<2*n; i++){
    p c = v[i];
    if(st.size()==1){
      // printf("%d. [%d %d] | %d | %d\n", i, v[i].val, v[i].ind,
//             last, *(st.begin()));
      alone[*(st.begin())]+=c.val-last;
    }
    if(st.size()>0)total+=(c.val-last);
    if(st.find(c.ind)!=st.end()){
      st.erase(c.ind);
    }
    else{
      //printf("%d. INSERTING: %d\n",i, c.ind);
      st.insert(c.ind);
    }
    last = c.val;
  }

  int _min = INT32_MAX;
  for(int i=0; i<n; i++){
    //printf("%d ", alone[i]);
    if(alone[i]<_min)
      _min = alone[i];
  }
  fout = fopen("lifeguards.out", "w");
  fprintf(fout, "%d", total-_min);
  fclose(fout);
  return 0;
}
