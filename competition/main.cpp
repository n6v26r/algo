// this crappy piece of code is provided to u 
// by __razv
#include <cctype>
#include <stdio.h>
 
using namespace std;

int def[10001];
int reset[10001];
int lap[10001];
int time[10001];

struct player{
  int id;
  int time;
  bool operator >(const player x) const{
    return time>x.time;
  };
};
 
int n, k;
 
player h[1<<14];
int uh;
 
void addtoheap(player ne)
{
  int child, parent;
  uh++;
  h[uh]=ne;
  child=uh;
  parent=child/2;
  while (parent>=1)
    if (h[parent].time > ne.time)
    {
      h[child]=h[parent];
      child=parent;
      parent=child/2;
    }
    else
      break;
  h[child]=ne;
}
 
void removefromheap()
{
  int parent, child;
  player ne;
  h[1]=h[uh];
  uh--;
  parent=1;
  ne=h[1];
  child=2*parent;
  while (child <= uh)
  {
    if (child<uh)
      if (h[child+1].time < h[child].time)
        child++;
    if (ne.time > h[child].time)
    {
      h[parent]=h[child];
      parent=child;
      child=2*parent;
    }
    else
      break;
  }
  h[parent]=ne;
}

void adjustheap()
{
  int parent, child;
  player ne;
  parent=1;
  ne=h[1];
  child=2*parent;
  while (child <= uh)
  {
    if (child<uh)
      if (h[child+1].time < h[child].time)
        child++;
    if (ne.time > h[child].time)
    {
      h[parent]=h[child];
      parent=child;
      child=2*parent;
    }
    else
      break;
  }
  h[parent]=ne;
}

void getInt(int *n, FILE *fin){
  *n = 0;
  char c = fgetc(fin);
  while(!isdigit(c))
    c = fgetc(fin);
 
  while(isdigit(c)){
    *n = (*n)*10+c-'0';
    c = fgetc(fin);
  }
}
 
int main(){
  FILE *fin, *fout;
  fin = fopen("competitie.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  for(int i=0; i<n; i++){
    player x;
    getInt(&x.time, fin);
    getInt(&reset[i], fin);
    x.id = i; 
    lap[i] = 0;
    def[i] = x.time;
    addtoheap(x);
  }
  fclose(fin);
 
  int time;
  int consec=1;
  int maxconsec = 0;
  while(uh>0 && maxconsec<n){
    if(time != h[1].time){
      consec = 1;
      time = h[1].time;
    }
    else consec++;
    if(consec>maxconsec) maxconsec = consec;
    if(lap[h[1].id]+1<k){
      lap[h[1].id]++;
      if(lap[h[1].id]%reset[h[1].id] > 0)
        h[1].time+=def[h[1].id]+lap[h[1].id]%reset[h[1].id];
      else
        h[1].time+=def[h[1].id];

      adjustheap();
    }
    else removefromheap();
  }
 
  fout = fopen("competitie.out", "w");
  fprintf(fout, "%d\n", maxconsec);
  fclose(fout);
}
