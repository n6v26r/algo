#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000000
#define min(a,b) ((a)>(b)? (b) : (a))

int n;
int v[MAXSIZE+1];
int total[MAXSIZE+1];

int main(){
  FILE *fin, *fout;
  fin=fopen("clasa1.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);
  int maxp=0, minp=0;
  for(int i=0; i<n; i++){
    int max = total[i-1];
    for(int j=min(minp, maxp); j<i; j++){
      if((j>0?total[j-1]:0)+abs(v[j]-v[i])>max)
        max = (j>0?total[j-1]:0)+abs(v[j]-v[i]);
    }
    total[i] = max;
    if(v[i]>v[maxp]) maxp=i;
    if(v[i]<v[minp]) minp=i;
  }
  fout=fopen("clasa1.out", "w");
  fprintf(fout, "%d\n", total[n-1]);
  fclose(fout);
}
