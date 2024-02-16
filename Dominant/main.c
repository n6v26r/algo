#include <stdio.h>
#include <string.h>
#define MAXN 300001

int v[MAXN], p, n;
int d[2*MAXN];
int s[2*MAXN];

int main(){
  memset(s, -1, sizeof(s));
  memset(d, -1, sizeof(d));
  FILE *fin, *fout;
  fin = fopen("dominant.in", "r");
  fscanf(fin, "%d\n", &p);
  char val = fgetc(fin); val -= '0';
  if(val==0) v[0] = -1;
  else v[0] = 1;
  s[v[0]+MAXN] = d[v[0]+MAXN] = 0;

  val = fgetc(fin);
  int i = 1;
  while(val!='\n' && val!=EOF){
    val -= '0';
    if(val==0) v[i] = v[i-1]-1;
    else v[i] = v[i-1]+1;

    if(v[i]!=0 && s[v[i]+MAXN]==-1) s[v[i]+MAXN] = i;

    d[v[i]+MAXN] = i;

    i++;
    val = fgetc(fin);
  }
  fclose(fin);
  n = i;

  int max = 0, maxcnt = 0;
  for(int i=-n; i<n; i++){
    int x = s[i+MAXN-1]; if(i!=1 && x==-1) continue;
    int y = d[i+MAXN];
    if(y-x>max){max = y-x; maxcnt=1;}
    else if(y-x==max) maxcnt++;
  }

  fout = fopen("dominant.out", "w");
  if(p==1) fprintf(fout, "%d\n", max);
  else fprintf(fout, "%d\n", maxcnt);
  fclose(fout);
  return 0;
}

