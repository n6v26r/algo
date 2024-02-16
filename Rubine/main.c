#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 2000000

int v[MAXSIZE+1];
char ciur[MAXSIZE+1];
int n, k, p;

int valid(int x, int a){
  return x!=-a && x!=-3;
}
void _ciur(){
  ciur[1]=ciur[0]=1;
  for(int i=2; i*i<MAXSIZE; i++){
    if(!ciur[i])
      for(int d=i*i; d<MAXSIZE; d+=i){
        ciur[d]=1;
      }
  }
}

void readInt(int *n, FILE *fin){
  (*n) = 0;
  char c = fgetc(fin);
  while(!isdigit(c)) c=fgetc(fin);
  while(isdigit(c)){
    (*n) = (*n)*10+c-'0';
    c = fgetc(fin);
  } 
}

int main()
{
  _ciur();
  FILE *fin, *fout;
  fin=fopen("rubine.in", "r");
  fscanf(fin, "%d%d%d", &n, &k, &p);
  for(int i=0; i<n; i++){
    readInt(&v[i], fin);
  }
  fclose(fin);

  int prime = 0;
  int sync = 0;

  for(int i=0; i<n; i++){
    if(!ciur[v[i]])
      prime++;
  }

  int a=0, b=0;
  long long sa=0, sb=0;
  int fa=0, fb=0;
  while(fa!=1 || fb!=1){
    if(!valid(v[a], 1)) fa = 1;
    if(!valid(v[b], 2)) fb = 1;
    if(fa==1 && fb==1) break;
    if(a==b){
      sync++;
      if(v[a]>=0 && ciur[v[a]]){
        sb += v[a]/2;
        sa += v[a]-v[a]/2;
      }
      v[a] = -3;
    }
    else{
      if(v[a]>=0 && ciur[v[a]]){
        sa+=v[a];
        v[a]=-1;
      }
      else if(v[a]>=0){v[a]=-1;}
      if(v[b]>=0 && ciur[v[b]]){
       sb+=v[b];
       v[b]=-2;
      }
      else if(v[b]>=0){v[b]=-2;}
    }
    a = (a+k)%n;
    b = (b+p)%n;
  }

  fout=fopen("rubine.out", "w");
  fprintf(fout, "%d\n%lld %lld\n%d\n", prime, sa, sb, sync);
  fclose(fout);
  return 0;
}
