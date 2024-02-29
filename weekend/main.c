#include <stdio.h>

#define MAXN 200001
#define EOL -1

int aib[MAXN];
int v[MAXN];
int n;

void update(int i, int val){
 while(i<=n){
    aib[i] += val;
    i+=i&-i;
  }
}

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=i&-i;
  }
  return sum;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("weekend.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=1; i<=n; i++){
    update(i, 1);
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  for(int i=n; i>=1; i--){
    int s = 1;
    int d = n+1;
    while(d-s>1){
      int m = (s+d)/2;
      if(get(m-1)>v[i]) d = m;
      else s = m;
    }
    update(s, -1);
    v[i] = s;
  }

  fout = fopen("weekend.out", "w");
  for(int i=1; i<=n; i++) fprintf(fout, "%d\n", v[i]);
  fclose(fout);
  return 0;
}
