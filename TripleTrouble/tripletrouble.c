#include <ctype.h>
#include <stdio.h>

#define BUFSIZE (128 * 1024)
#define MAXN 100000

char rbuf[BUFSIZE], wbuf[BUFSIZE];

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

void readInt(int *n, FILE* fin){
  *n = 0;
  char c = fgetc(fin);
  while(!isdigit(c)) c = fgetc(fin);
  while(isdigit(c)){
    *n = (*n)*10+c-'0';
    c=fgetc(fin);
  }
  ungetc(c, fin);
}

int main(){
  FILE *fin, *fout;
  fin = fopen("tripletrouble.in", "r");
  setvbuf(fin, rbuf, _IOFBF, BUFSIZE);
  fscanf(fin, "%d %d %d", &n[0], &n[1], &n[2]);
  for(int j=0; j<3; j++){
    for (int i=0; i<n[j]; i++){
      readInt(&v[j][i], fin);
    }
    _qsort(v[j], 0,  n[j]-1);
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
  setvbuf(fout, wbuf, _IOFBF, BUFSIZE);
  fprintf(fout, "%lld\n", total);
  fclose(fout);
  return 0;  
}
