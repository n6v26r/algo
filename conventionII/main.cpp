// this crappy piece of code is provided to u 
// by __razv

// http://usaco.org/index.php?page=viewproblem2&cpid=859
// full score :)

#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

#define MAXN 100777

struct cow{
  int order;
  int timeArr;
  int timeSpend;
  bool operator <(const cow &mooo) const {
    return mooo.order<order;
  };
};

int n;
cow mooos[MAXN];
priority_queue<cow> q;

bool CompCow(const cow a, const cow b){
  if(a.timeArr!=b.timeArr)
    return a.timeArr<b.timeArr;

  return a.timeSpend<b.timeSpend;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("convention2.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d%d", &mooos[i].timeArr, &mooos[i].timeSpend); mooos[i].order = i;
  }
  fclose(fin);

  sort(mooos, mooos+n, CompCow);

  int t = 0;
  int i=0;

  int maxWaiting = 0;
  while(i<n){
    while(i<n || !q.empty()){
      while(i<n && mooos[i].timeArr<=t){
        q.push(mooos[i]);
        i++;
      }
      if(q.empty()){
        t = mooos[i].timeArr+mooos[i].timeSpend;
        i++;
        continue;
      }
      cow moo = q.top();
      int waiting = t - moo.timeArr;
      if(waiting>maxWaiting)maxWaiting = waiting;
      t += moo.timeSpend;  
      q.pop();
    }
  }

  fout = fopen("convention2.out", "w");
  fprintf(fout, "%d\n", maxWaiting);
  fclose(fout);
  return 0;
}
