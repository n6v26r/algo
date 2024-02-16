#include <stdio.h>
#include <stdlib.h>

#define MAXCOORD 1001
#define MAXN 100001
#define MOD 1000003

typedef struct{
  int x;
  int y;
}point;

int Xsame[MAXCOORD];
int Ysame[MAXCOORD];
int comb[MAXN];

int n, p;
point v[MAXN];

int main(){
  comb[1]=comb[0] = 0;
  comb[2] = 1;
  for(int i=3; i<MAXN; i++){
    comb[i] = ((unsigned long long)(i-1)*i/2)%MOD;
    printf("%d\n", comb[i]);
  }
  FILE *fin, *fout;
  fin = fopen("triunghiuri2.in", "r");
  fscanf(fin, "%d%d", &p, &n);
  int max = 0;
  for(int i=0; i<n; i++){
    fscanf(fin, "%d %d", &v[i].x, &v[i].y);
    Xsame[v[i].x]++; if(Xsame[v[i].x]>max)max = Xsame[v[i].x];
    Ysame[v[i].y]++;
  }
  fclose(fin);

  int tri = 0;
  for(int i=0; i<MAXCOORD; i++){
    int val = Ysame[i];
    tri = (tri + ((unsigned long long)comb[val])*((unsigned long long)n-val)%MOD)%MOD;
  }

  int dif = 0;
  for(int i=0; i<n; i++){
    int valx = Xsame[v[i].x]-1;
    int valy = Ysame[v[i].y]-1;
    dif = (dif + ((unsigned long long)valx*valy))%MOD;
  }

  fout = fopen("triunghiuri2.out", "w");
  if(p==1)
    fprintf(fout, "%d\n", max);
  else
    fprintf(fout, "%d\n", (tri<dif?(MOD+(tri-dif))%MOD:(tri-dif)%MOD));
  fclose(fout);
  return 0;
}
