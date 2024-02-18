#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define MAXN 100000

int v[3][MAXN+1]; 
int n[3];

void swap(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

int pivot(int *v, int a, int b){
  int pi = a;
  int i=a, j=b;
  while(1){
    while(v[i]<v[pi]) i++;
    while(v[j]>v[pi]) j--;

    if(i>=j)
      return j;

    swap(&v[i], &v[j]);
  
    i++;
    j--;
  }
}

void _qsort(int *v, int a, int b){
  if(a<b){
    int pi = pivot(v, a, b);
    _qsort(v, a, pi);
    _qsort(v, pi+1, b);
  }
}

int cautbin(int *v, int size, int val, int start){
  int s = start; int d = size;
  int m;
  while(d-s>1){
    m = (s+d)/2;
    if(v[m]>val)
      d = m;
    else 
      s = m;
  }
    return s;
}

int compInt(int a, int b){
  return a-b;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("tripletrouble.in", "r");
  fscanf(fin, "%d %d %d", &n[0], &n[1], &n[2]);
  for(int j=0; j<3; j++){
    for (int i=0; i<n[j]; i++){
      fscanf(fin, "%d", &v[j][i]);
    }
    //_qsort(v[j], 0,  n[j]-1);
    sort(&v[j][0], &v[j][n[j]]);
  }
  fclose(fin);
    
  int index[3] = {-1, 0, -1};
  long long total = 0;
  for(;index[1]<n[1];index[1]++){
    index[0] = cautbin(v[0], n[0], v[1][index[1]], index[0]);
    index[2] = cautbin(v[2], n[2], v[1][index[1]], index[2]);
    total += (long long)(index[0]+1)*(long long)(index[2]+1);
  }
  
  fout = fopen("tripletrouble.out", "w");
  //printf("%lld\n", total);
  fprintf(fout, "%lld\n", total);
  fclose(fout);
  return 0;  
}
