#include <stdio.h>
#include <stdbool.h>

#define MAXN 100000
#define QSIZE 131072
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct{
  int a;
  int b;
}interval;

typedef struct{
  int v[QSIZE];
  int p;
  int u;
}q;

void push(q* queue, int val){
  queue->p = (queue->p+1)%QSIZE;
  queue->v[queue->p] = val;
}

void popBack(q* queue){
  queue->u = (queue->u+1)%QSIZE;
}

void popFront(q* queue){
  queue->p = (QSIZE+queue->p-1)%QSIZE;
}

int front(q* queue){
  return queue->v[queue->p];
}

int back(q* queue){
  return queue->v[(queue->u+1)%QSIZE];
}

bool empty(q* queue){
  return queue->p == queue->u;
}

int n;
interval v[MAXN+1];
q max_queue;
q min_queue;
q* maxq=&max_queue;
q* minq=&min_queue;

int main(){
  FILE *fin, *fout;
  fin = fopen("ssecvint.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d %d\n", &v[i].a, &v[i].b);
  }
  fclose(fin);
  
  int i=0;
  int last = 0;
  int max = 0;

  while(i<n){
    while(!empty(minq) && v[front(minq)].b>v[i].b) popFront(minq);
    while(!empty(maxq) && v[front(maxq)].a<v[i].a) popFront(maxq);
    push(minq, i);
    push(maxq, i);

    while(v[back(minq)].b<v[back(maxq)].a){ // multimea vida
      int i = back(minq);
      int j = back(maxq);
      if(i<j)
        popBack(minq);
      else
       popBack(maxq);

      last = MIN(i, j)+1;
    }

    if(i-last+1>max) max = i-last+1;

    i++;
  } 

  fout = fopen("ssecvint.out", "w");
  fprintf(fout, "%d\n", max);
  fclose(fout);
  return 0;
}
