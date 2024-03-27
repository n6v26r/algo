#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

#pragma GCC optimize("Ofast,unroll-loops")

#define MAXN 10001
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int n;

int val[MAXN];
int v[MAXN];

std::vector<int> mat[MAXN];
typedef struct{
  int a;
  int b;
}prop;

prop best[MAXN];

int sumA = 0;
int sumB = 0;

int sp[MAXN];

bool comp(prop a, prop b){
  if(a.a-a.b != b.a-b.b)
    return a.a-a.b > b.a-b.b;

  return a.a>b.a;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("jbb.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n;i++){
    fscanf(fin, "%d", &val[i]);
  }
  for(int i=0; i<n;i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  int j = 0;
  for(int i=0; i<n; i++){
    if(v[i]==-1) continue;
    int y = i;
    while(v[y]!=-1){
      mat[j].push_back(val[y]);
      int aux = v[y];
      v[y] = -1;
      y = aux-1;
    }

    if(mat[j].size()%2 == 0){
      int sum = 0;
      for(int i=0; i<mat[j].size(); i+=2) sum+=mat[j][i];
      int sum2 = 0;
      for(int i=1; i<mat[j].size(); i+=2) sum2+=mat[j][i];
      sumA += MAX(sum, sum2);
      sumB += MIN(sum, sum2);
    }
    j++;
  }

  int z = 0;
  for(int i=0; i<j; i++){
    if(mat[i].size()%2 == 0) continue;
    for(int j=0; j<mat[i].size(); j++){
      sp[j] = (j>1?sp[j-2]:0) + mat[i][j];
    }
    int sum = 0;
    int sum2 = 0;
    for(int j = 0; j<mat[i].size(); j++){
      sum = sp[j-1]+ (!(j%2)?sp[mat[i].size()-1]:sp[mat[i].size()-2]) - (j>1?sp[j-2]:0);
      sum2 = (j>1?sp[j-2]:0) + (!((j+1)%2)?sp[mat[i].size()-1]:sp[mat[i].size()-2]) - (j>0?sp[j-1]:0);

      if(abs(sum-sum2)>best[z].a-best[z].b) { best[z].a = MAX(sum, sum2); best[z].b = MIN(sum, sum2);}
      else if(abs(sum-sum2) == best[z].a-best[z].b && sum>best[z].a) {best[z].a = MAX(sum, sum2); best[z].b = MIN(sum, sum2);}
    }

    z++;
  }

  std::sort(best, best+z, comp);
  for(int i=0; i<z; i++){
    if(!(i%2))sumA += best[i].a;
    else sumA += best[i].b;
  }

  fout = fopen("jbb.out", "w");
  fprintf(fout, "%d\n", sumA);
  fclose(fout);
  return 0;
}
