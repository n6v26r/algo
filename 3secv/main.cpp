// Simulare OJI 2024 clasa a 9-a
// https://kilonova.ro/problems/1911
#include <stdio.h>
#define MAX(a, b) ((a)>(b)?(a):(b))

typedef struct{int nr; int ap;}frecv;

int t, n;

int main(){
  FILE *fin=stdin, *fout=stdout;
  //fin = fopen("3secv.in", "r");
  //fout = fopen("3secv.out", "w");
  fscanf(fin, "%d", &t);
  while(t>0){
    fscanf(fin, "%d", &n);
    int val; fscanf(fin, "%d", &val);
    frecv dif[3] = { {0, -1}, {0, -1}, {0, -1} };
    int s=0; int d=0;
    int maxlen = 0;
    while(s<n){
      while(d<n){
        if(val!=dif[0].nr && val!=dif[1].nr && val!=dif[2].nr && !(dif[0].ap==-1 || dif[1].ap==-1 || dif[2].ap==-1) ) break;
        for(int i=0; i<3; i++){if(dif[i].ap==-1 || dif[i].nr==val){dif[i].ap=d;dif[i].nr=val;break;}}
        maxlen = MAX(maxlen, d-s+1);
        d++;
        if(d<n) fscanf(fin, "%d", &val);
      }
      for(int i=0; i<3; i++){if(s==dif[i].ap){dif[i].ap=-1; break;}}
      s++;
    }
    fprintf(fout, "%d\n", maxlen);
    t--;
  }
  //fclose(fin);
  //fclose(fout);
  return 0;
}
