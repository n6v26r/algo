#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 1000
#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))

typedef struct{
  int v[MAXSIZE+1];
  int u, p;
}q;

typedef struct{int a; int b;}pair;

int mat[MAXSIZE+1][MAXSIZE+1];
int n, m, p;

q maxq;
q minq;
q minv[MAXSIZE+1];
q maxv[MAXSIZE+1];

int top(q* a){
  return a->v[a->p];
}

int bottom(q* a){
  return a->v[a->u+1];
}

int empty(q* a){
  return a->u>=a->p;
}

void rf(q* a){
  a->p--;
}

void rb(q* a){
  a->u++;
}

void add(q* a, int val){
  a->p++;
  a->v[a->p] = val;
}

pair getbest(int lin, int col){
  if(lin>n || col>m){
    return (pair){__INT_MAX__, __INT_MAX__};
  }

  for(int i=0; i<lin; i++){
    for(int j=0; j<m; j++){
      int val = mat[i][j];
      while(!empty(&minv[j]) && mat[top(&minv[j])][j]>val) rf(&minv[j]);
      while(!empty(&maxv[j]) && mat[top(&maxv[j])][j]<val) rf(&maxv[j]);
      add(&minv[j], i);
      add(&maxv[j], i);
    }
  }

  int difmin = __INT_MAX__;
  int count = 0;
  for(int l=lin-1; l<n; l++){
    int i = 0;
    minq.u = minq.p = 0;
    maxq.p = maxq.u = 0;
    while(i<col){
      int minlin = bottom(&minv[i]);
      int maxlin = bottom(&maxv[i]);
      int valmin = mat[minlin][i];
      int valmax = mat[maxlin][i];
      while(!empty(&minq) && mat[bottom(&minv[top(&minq)])][top(&minq)]>valmin) rf(&minq);
      while(!empty(&maxq) && mat[bottom(&maxv[top(&maxq)])][top(&maxq)]<valmax) rf(&maxq);

      add(&minq, i);
      add(&maxq, i);

      i++;
    }

    int dif = abs(mat[bottom(&maxv[bottom(&maxq)])][bottom(&maxq)]-
                  mat[bottom(&minv[bottom(&minq)])][bottom(&minq)]);

    if(dif<difmin)
      difmin = dif, count = 1;
    else if(dif==difmin)
      count++;

    while(i<m){
      if(i-col==bottom(&minq))
        rb(&minq);
      if(i-col==bottom(&maxq))
        rb(&maxq);

      int minlin = bottom(&minv[i]);
      int maxlin = bottom(&maxv[i]);
      int valmin = mat[minlin][i];
      int valmax = mat[maxlin][i];
      while(!empty(&minq) && mat[bottom(&minv[top(&minq)])][top(&minq)]>valmin) rf(&minq);
      while(!empty(&maxq) && mat[bottom(&maxv[top(&maxq)])][top(&maxq)]<valmax) rf(&maxq);

      add(&minq, i);
      add(&maxq, i);

      int dif = abs(mat[bottom(&maxv[bottom(&maxq)])][bottom(&maxq)]-
        mat[bottom(&minv[bottom(&minq)])][bottom(&minq)]);

      if(dif<difmin)
        difmin = dif, count = 1;
      else if(dif==difmin)
        count++;

      i++;
    }

    for(int j=0; j<m; j++){
      if(l-lin+1 == bottom(&minv[j]))
        rb(&minv[j]);
      if(l-lin+1 == bottom(&maxv[j]))
        rb(&maxv[j]);

      int val = mat[l+1][j];
      while(!empty(&minv[j]) && mat[top(&minv[j])][j]>val) rf(&minv[j]);
      while(!empty(&maxv[j]) && mat[top(&maxv[j])][j]<val) rf(&maxv[j]);
      add(&minv[j], l+1);
      add(&maxv[j], l+1);
    }

  }
  return (pair){difmin, count};
}


void init(){
  for(int i=0; i<=MAXSIZE; i++){
    memset(minv[i].v, 127, sizeof(minv[i].v));
    memset(maxv[i].v, 0, sizeof(maxv[i].v));
    minv[i].u = minv[i].p = 0;
    maxv[i].p = maxv[i].u = 0;
  }
}

int main(){
  for(int i=0; i<=MAXSIZE; i++){
    memset(minv[i].v, 127, sizeof(minv[i].v));
  }
  FILE *fin, *fout;
  fin = fopen("struti.in", "r");
  fscanf(fin, "%d %d %d ", &n, &m ,&p);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      fscanf(fin, "%d ", &mat[i][j]);
    }
  }

  fout = fopen("struti.out", "w");
  while(p>0){
    int dx, dy;
    fscanf(fin, "%d %d\n", &dx, &dy);
    pair ans = {0, 0};
    pair ans2 = {__INT_MAX__, __INT_MAX__};
    ans = getbest(dx, dy);
    init();
    if(dx!=dy){
      ans2 = getbest(dy, dx);
      init();
    }

    if(ans.a>ans2.a){
      fprintf(fout, "%d %d\n", ans2.a, ans2.b);
    }
    else if(ans.a<ans2.a){
      fprintf(fout, "%d %d\n", ans.a, ans.b);
    }
    else
      fprintf(fout, "%d %d\n", ans.a, ans2.b+ans.b);

    p--;
  }
  fclose(fin);

  fclose(fout);
  return EXIT_SUCCESS;
}
