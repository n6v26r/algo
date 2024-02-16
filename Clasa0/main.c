#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000000
#define next(a1, a2) (((a1)*q)+((a2)*p))

unsigned int a1, a2;
int p, q, n;
unsigned int v[MAXSIZE+1];

void swap(unsigned int* a, unsigned int* b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

int pivot(int a, int b){
  int pi = a;
  int i=a, j=b;
  while(i<j){
    while(v[i]<v[pi])
      i++;
    while(v[j]>v[pi])
      j--;

    if(i>=j) break;

    swap(&v[i], &v[j]);
    i++;
    j--;
  }
  return j;
}

unsigned int quickselect(int a, int b, int k){
  if(a==b)
    return v[k];
  int pi = pivot(a, b);
  if(k==pi) return v[k];
  else if(pi>k)
    return quickselect(a, pi, k);
  else
    return quickselect(pi+1, b, k);
}

int main(){
  FILE *fin, *fout;
  fin=fopen("clasa0.in", "r");
  fscanf(fin, "%d\n%u %u %d %d", &n, &a1, &a2, &p, &q);
  fclose(fin);

  v[0]=a1;
  v[1]=a2;
  for(int i=2; i<n; i++){
    unsigned int aux = next(a1, a2);
    a1 = a2;
    a2 = aux;

    v[i] = aux;
  }

  unsigned int med = quickselect(0, n-1, n/2);
  long long sm=0, bg=0;
  int registered=0;
  for(int i=0; i<n; i++){
    if(v[i]<=med)
      sm+=v[i];
    else{
      bg+=v[i];
      registered++;
    }
  }
  while(registered<n/2){
    bg+=med;
    sm-=med;
    registered++;
  }
  if(n%2==1){
    sm-=med;
  }
  fout=fopen("clasa0.out", "w");
  fprintf(fout, "%lld\n", bg-sm);
  fclose(fout);
  return EXIT_SUCCESS;
}
