// OJI 2019 8th grade
// https://www.nerdarena.ro/problema/paralele
#include <stdio.h>
#include <ctype.h>

#define MAXN 40069

unsigned long long lin[MAXN];
unsigned long long col[MAXN];

int lastl[MAXN];
int lastc[MAXN];

unsigned long long sumc[MAXN];
unsigned long long suml[MAXN];

int t, n, m;

void readInt(int *n, FILE *fin){
  char c = fgetc(fin);
  while(!isdigit(c)) c = fgetc(fin);
  *n = 0;
  while(isdigit(c)){
    (*n) = (*n)*10+c-'0';
    c = fgetc(fin);
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("paralele.in", "r");
  fscanf(fin, "%d%d%d", &t, &n, &m);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      int val; readInt(&val, fin);
      if(val==1){
        lastl[i]++;
        lastc[j]++;
      }
      else{
        lin[i] += ((unsigned long long)lastl[i]*(lastl[i]-1))/2;
        col[j] += ((unsigned long long)lastc[j]*(lastc[j]-1))/2;
        lastl[i] = 0;
        lastc[j] = 0;
      }
    }
  }
  for(int i=0; i<n; i++) lin[i] += ((unsigned long long)lastl[i]*(lastl[i]-1))/2;
  for(int j=0; j<m; j++) col[j] += ((unsigned long long)lastc[j]*(lastc[j]-1))/2;
  fclose(fin);

  unsigned long long sum = 0;
  if(t==1) 
    for(int i=0; i<n; i++){
      suml[i]=(i>0?suml[i-1]:0)+lin[i];
      sum += lin[i]*(i>0?suml[i-1]:0);
    }
  else 
    for(int i=0; i<m; i++){
      sumc[i]=(i>0?sumc[i-1]:0)+col[i];
      sum += col[i]*(i>0?sumc[i-1]:0);
    }

  fout = fopen("paralele.out", "w");
  fprintf(fout, "%llu\n", sum);
  fclose(fout);
  return 0;
}
