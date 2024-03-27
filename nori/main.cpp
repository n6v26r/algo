// ONI 2016 baraj
#include <stdio.h>

#define MAXN 55
#define MAXB 300001
#define MAXSIZE 300

#define ABS(a) ((a)>0?(a):-(a))

typedef struct{
  int l;
  int c;
  int type;
  int t;
}cloud;

int p, t, lin, col, n;

cloud v[MAXN];
cloud full[MAXN]; int fullClouds = 0;

int mars[MAXB];
int main(){
  FILE *fin, *fout;
  fin = fopen("nori.in", "r");
  fscanf(fin, "%d%d%d%d%d\n", &p, &lin, &col, &n, &t);
  for(int i=0; i<n; i++){
    cloud nor;
    fscanf(fin, "%d%d%d%d\n", &nor.l, &nor.c, &nor.type, &nor.t);
    v[i] = nor;
    if(nor.l==1){
      if(lin>=nor.type && nor.c-1>=nor.type/2 && col-nor.c>=nor.type/2)
        full[fullClouds++] = nor;
    }
    else
      if(col>=nor.type && nor.l-1>=nor.type/2 && lin-nor.l>=nor.type/2)
        full[fullClouds++] = nor;
  }
  fclose(fin);

  if(p==1){
    for(int i=0; i<fullClouds; i++){
      long long time = full[i].t+full[i].type;
      while(time<MAXB){
        mars[time]++;
        if(full[i].l == 1){
          if(time+lin-full[i].type + 1 < MAXB)
            mars[time + lin - full[i].type + 1]--;
          time = time + lin - full[i].type + 2*full[i].type;
        }
        else{
          if(time+col-full[i].type + 1 < MAXB)
              mars[time + col - full[i].type + 1]--;
          time = time + col - full[i].type + 2*full[i].type;
        }
      }
    }
  }
  else{
    for(int i=0; i<n; i++){
      int time = v[i].t+1;
      while(1){
        int ctime;
        if(v[i].l==1)
          ctime = time + lin + v[i].type;
        else
          ctime = time + col + v[i].type;
        if(ctime>t) break;
        time = ctime;
      }
      bool dir = (v[i].l==1);
      while(time<t){
        if(dir) v[i].l++;
        else v[i].c++;
        time++;
      }
      if(dir) v[i].l-=v[i].type/2;
      else v[i].c -= v[i].type/2;
    }
  }

  fout = fopen("nori.out", "w");
  if(p==1){
    fprintf(fout, "%d ", fullClouds);
    for(int i=1; i<MAXB; i++){
      mars[i] += mars[i-1];
      if(mars[i]==fullClouds){fprintf(fout, "%d\n", i); break;}
    }
  }
  else{
    int ok = 0;
    int storm = 0;
    for(int i=1; i<=lin; i++){
      for(int j=1; j<=col; j++){
        int nor = 0;
        for(int y=0; y<n && nor<2; y++){
          int dist = ABS(v[y].l-i) + ABS(v[y].c-j);
          if(dist<=v[y].type/2) nor++;
        }
      if(nor>=2) storm++;
      else if(!nor) ok++;
      }
    }
    fprintf(fout, "%d %d\n", ok, storm);
  }
  fclose(fout);
  return 0;
}
