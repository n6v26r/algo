#include <stdio.h>
#include <ctype.h>

#define MAXN 1000000
#define abs(a) (((a)>=0)?(a):(-(a)))

typedef struct{
  int x;
  int y;
}point;

int n;

int vx[MAXN+1];
int vy[MAXN+1];

void swap(int* a, int* b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

int pivot(int *v, int a, int b){
  int pi = v[a];
  int i = a, j = b;
  while(1){
    while(v[i]<pi)
      i++;
    while(v[j]>pi)
      j--;

    if(i>=j) return j;
    swap(&v[i], &v[j]);

    i++;
    j--;
  }
  return j;
}

int quickSelect(int *v, int a, int b, int k){
  if(a<b){
    int pi = pivot(v, a, b);
    if(k<=pi)
      return quickSelect(v, a, pi, k);
    else  
      return quickSelect(v, pi+1, b, k);
  }
  return v[a];
}

void readInt(int* n, FILE *fin){
  *n = 0;
  char c = fgetc(fin);
  while(isspace(c)) c = fgetc(fin);
  int semn = 1;
  if(c=='-') semn = -1, c=fgetc(fin);
  while(!isspace(c)){
    (*n) = (*n)*10+semn*(c-'0');
    c = fgetc(fin);
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("antitir.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    point p;
    readInt(&p.x, fin);
    readInt(&p.y, fin);
    vx[i] = p.x;
    vy[i] = p.y;
  }
  fclose(fin);
  
  int xmed = quickSelect(vx, 0, n-1, n/2);
  int ymed = quickSelect(vy, 0, n-1, n/2);

  fout = fopen("antitir.out", "w");
  long long total = 0;
  for(int i=0; i<n; i++){
    total += (long long)abs(xmed-vx[i])+abs(ymed-vy[i]);
  }
  fprintf(fout,"%lld\n",total);
  fclose(fout);
  return 0;
}
