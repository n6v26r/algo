// OJI 2023 - 8th grade
#include <stdio.h>

#define MAXN 200001
#define MAXM 100001
#define MAXBORNA 1000002


typedef struct{
  int a;
  int b;
  int val;
}section;

int p, n, m;
int road[2*MAXBORNA];
section taxedSections[MAXM];

void swap(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("hibrid.in", "r");
  fscanf(fin, "%d%d%d", &p, &m, &n);
  for(int i=0; i<m; i++){
    fscanf(fin, "%d%d%d", &taxedSections[i].a, &taxedSections[i].b, &taxedSections[i].val);
  }
  int last; fscanf(fin, "%d", &last);
  for(int i=1; i<n; i++){
    int val; fscanf(fin, "%d", &val); int cv = val;
    if(val<last) swap(&last, &val);
    road[MAXBORNA+last]++;
    road[MAXBORNA+val+1]--;
    last = cv;
  }
  fclose(fin);

  int sum = 0;
  for(int i=0; i<2*MAXBORNA; i++){
    sum+=road[i];
    road[i] = sum;
  }

  fout = fopen("hibrid.out", "w");
  if(p==1){
    int max=0; int maxpos = -2;
    for(int i=0; i<m; i++){
      int pos = taxedSections[i].a+MAXBORNA;
      if(road[pos]>max){
        max = road[pos]; maxpos = i;
      }
    }
    fprintf(fout, "%d\n", maxpos+1);
  }
  else{
    long long sum = 0;
    for(int i=0; i<m; i++){
      int pos = taxedSections[i].a+MAXBORNA;
      sum+=(long long)road[pos]*taxedSections[i].val;
    }
    fprintf(fout, "%lld\n", sum);
  }
  fclose(fout);
  return 0;
}
