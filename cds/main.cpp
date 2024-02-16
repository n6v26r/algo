#include <iostream>
#include <queue>
using namespace std;

#define MAXN 10001

int n, k;
int v[MAXN];

priority_queue<int> q;

int time(int k){
  int i = 0;
  for(; i<k; i++) q.push(-v[i]);
  int total = 0;
  while(i<n){
    int last = -q.top(); q.pop();
    //printf(":%d ", last);
    total+=last;
    q.push(-v[i]);
    i++;
  }
  while(!q.empty()){
    int last = -q.top(); q.pop();
    if(q.size()>=k-1) total+=last;
    else if(total<last) total = last;
  }
  while(!q.empty()) q.pop();
  return total;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("cowdance.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  //printf("%d ", time(3));

  int s = 0;
  int d = n+1;
  while(d-s>1){
    int m = (s+d)/2;
    //printf("%d %d %d\n", s, m, d); fflush(stdout);
    if(time(m)>k) s = m;
    else d = m;
  }

  fout = fopen("cowdance.out", "w");
  fprintf(fout, "%d\n", d);
  fclose(fout);
  return 0;
}
