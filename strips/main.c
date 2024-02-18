#include <stdio.h>

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAXN 50001

typedef struct{
  int a;
  int b;
}seg;

int t, m, n, l;

seg v[2][MAXN];
int p[2];
int penalty[2];

int check(seg val, int l, int player){
  if(val.a<0 || val.b>m-1) return 0;
  if(p[!player]==0) return 1;
  int s = 0;
  int d = p[!player];
  while(d-s>1){
    int m = (s+d)/2;
    if(v[!player][m].a>val.a) d = m;
    else s = m;
  }
  if(v[!player][s].a>val.b+1) return 1;
  if(!(v[!player][s].b<val.a-1)) return 0;
  if(s+1<p[!player] && !(val.b<v[!player][s+1].a-1)) return 0; 

  return 1;
}

int cautbin(seg val, int player){
  int s = 0;
  int d = p[player];
  while(d-s>1){
    int m = (s+d)/2;
    if(v[player][m].a>val.a) d = m;
    else s = m;
  }
  return s;
}

int intersect(seg a, seg b){
  if(a.a<=b.a && a.b>=b.a) return 1;
  if(a.a<=b.b && a.b>=b.b) return 1;
  if(a.a==b.b+1 || a.b+1==b.a) return 1;
  return 0;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("strips.in", "r");
  fscanf(fin, "%d%d%d%d", &t, &m, &n, &l);
  int player = 0;
  for(int i=0; i<2*n; i++){
    int val; fscanf(fin, "%d", &val);
    seg s = {val, val+l-1};
    if(check(s, l, player)){
      int pos = cautbin(s, player);
      if(v[player][pos].a<v[player][pos].b){
        if(intersect(v[player][pos], s)){
          v[player][pos].b=MAX(v[player][pos].b, s.b);
          v[player][pos].a=MIN(v[player][pos].a, s.a);
          
          s = (seg){0, 0};
        }
      } 
      if(s.a<s.b && v[player][pos+1].a<v[player][pos+1].b){
        if(intersect(v[player][pos+1], s)){
          v[player][pos+1].b=MAX(v[player][pos+1].b, s.b);
          v[player][pos+1].a=MIN(v[player][pos+1].a, s.a);

          s = (seg){0, 0};
        }
      }
      if(pos+1<p[player] && intersect(v[player][pos], v[player][pos+1])){
        v[player][pos].b=MAX(v[player][pos].b, v[player][pos+1].b);
        v[player][pos].a=MIN(v[player][pos].a, v[player][pos+1].a);
        for(int i=pos+1; i<p[player]; i++) v[player][i] = v[player][i+1];
        p[player]--;
      }
      if(s.a<s.b){
        if(pos>=p[player]) pos--;
        if(!(v[player][pos].a<s.a)) pos--;
        for(int i=p[player]; i>pos+1; i--) v[player][i] = v[player][i-1];
        v[player][pos+1] = s;
        p[player]++;
      }
    }
    else penalty[player]++;
    player=!player;
  }
  fclose(fin);


  fout = fopen("strips.out", "w");
  if(t==1) fprintf(fout, "%d %d\n", penalty[0], penalty[1]);
  else{
    int max[2] = {0, 0};
    for(int player=0; player<2; player++){
      for(int i=0; i<p[player]; i++){
        int len = v[player][i].b - v[player][i].a+1;
        if(len>max[player]) max[player] = len;
      }
    }
    fprintf(fout, "%d %d\n", max[0], max[1]);
  }
  fclose(fout);
  return 0;
}