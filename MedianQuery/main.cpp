#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100007

typedef struct{
  int a;
  int b;
  int ord;
  int ans;
}query;

typedef struct{
  int i;
  int val;
}pair;

int n, m;
pair arr[MAXN]; // array
int v[MAXN]; //normalized array
query q[MAXN];
int blocks; // sqrt(n)

int aib[MAXN];

void update(int i, int val){
  while(i<=n){
    aib[i]+=val;
    i+=(i&-i);
  }
}

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&-i);
  }
  return sum;
}

int cbin(int pos){
  int s = 0;
  int d = n;
  while(d-s>1){
    int m = (s+d)/2;
    if(get(m)<pos)
      s = m;
    else
      d = m;
  }
  return d;
}

// pentru qsort

int compQueryInterval(const void* a, const void* b){
  query _a = *((const query*)a);
  query _b = *((const query*)b);

  if(_a.a/blocks!=_b.a/blocks)
    return _a.a-_b.a;

  return _a.b-_b.b;
}

int compareQueryOrder(const void *a, const void *b){
  query _a = *((const query*)a);
  query _b = *((const query*)b);

  return _a.ord-_b.ord;
}

int comparePair(const void* a, const void* b){
  pair _a = *((const pair*)a);
  pair _b = *((const pair*)b);

  return _a.val-_b.val;
}

void mo(){
  blocks = sqrt(n);

  qsort(q, m, sizeof(query), compQueryInterval);

  int left=0, right=0;

  for(int i=0; i<m; i++){
    int newLeft = q[i].a-1;
    int newRight = q[i].b-1;

    while(left<newLeft){
      update(v[left], -1);
      left++;
    }

    while(left>newLeft){
      update(v[left-1], 1);
      left--;
    }

    while(right<=newRight){
      update(v[right], 1);
      right++;
    }

    while(right>newRight+1){
      update(v[right-1], -1);
      right--;
    }
    q[i].ans = arr[cbin((right-left+1)/2)-1].val;
  }
}

int main(){
  FILE *fin, *fout;
  fin=fopen("median_query.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &arr[i].val);
    arr[i].i = i;
  }

  for(int i=0; i<m; i++){
    fscanf(fin, "%d%d", &q[i].a, &q[i].b);
    q[i].ord = i;
  }
  qsort(arr, n, sizeof(pair), comparePair);
  for(int i=0; i<n; i++){
    v[arr[i].i] = i+1;
  }
  fclose(fin);

  mo();

  qsort(q, m, sizeof(query), compareQueryOrder);

  fout = fopen("median_query.out", "w");
  for(int i=0; i<m; i++)
    fprintf(fout, "%d\n", q[i].ans);
  fclose(fout);
  return 0;
}
