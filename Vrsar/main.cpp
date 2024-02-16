#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#define MAXN 100000

typedef struct{
  int pos;
  int time;
  int down;
}hill;

int n, m;

hill v[MAXN+1];

int maxtime = 0;

int comp(hill a, hill b){
  int dista = a.pos;
  int playtimea = a.time>dista?a.time-dista:0;

  int distb = b.pos;
  int playtimeb = b.time>distb?b.time-distb:0;

  return playtimea>playtimeb;
}

int main(){
  //freopen("file.in", "r", stdin);
  //freopen("file.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i=0; i<n; i++){
   scanf("%d%d%d", &v[i].pos, &v[i].time, &v[i].down);
   if(v[i].time>maxtime) maxtime = v[i].time;
  }

  sort(v, v+n, comp);
  /*for(int i=0; i<n; i++){
    printf("%d %d\n", v[i].pos, v[i].time>v[i].pos?v[i].time-v[i].pos:0);
  }*/
  for(int i=0; i<m; i++){
    int j = 0;
    int total = 0;
    int play = 0;
    int pos; scanf("%d", &pos);
    while(total<maxtime){
      int maxplaytime = 0, bestime;
      while(v[j].time<=total) j++;
      int dist = abs(pos-v[j].pos);
      maxplaytime = v[j].time-total-dist;
      bestime = dist+maxplaytime+v[j].down;
      total+=bestime;
      play+=maxplaytime;
      pos = v[j].pos;
      //printf("m: %d (%d)\n", maxplaytime, total);
    }
    printf("%d ", play);
  }printf("\n");
  return 0;
}
