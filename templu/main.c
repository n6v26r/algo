#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f[100];

int n, l;

char str[1000];

int compDig(const void* a, const void* b){
  int _a = *((const int*)a);
  int _b = *((const int*)b);

  int pa = 1; while(pa*10<=_a) pa*=10;
  int pb = 1; while(pb*10<=_b) pb*=10;

  while(pa>0 && pb>0){
    int cifa = _a/pa;
    int cifb = _b/pb;
    if(cifa<cifb) return -1;
    else if(cifa>cifb) return 1;

    _a%=pa;
    _b%=pb;
    pa/=10;
    pb/=10;
  }
  return 0;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("templu.in", "r");
  fscanf(fin, "%d%d", &n, &l);
  fclose(fin);

  int j = 2;
  int sum = n*l; f[0]=f[1]=sum;
  int total = sum*2;
  for(int i=1; i<l/2; i++){
    sum += l-2*i;
    f[j]=f[j+1] = sum; j+=2;
   
    total+=sum*2;
  }
  if(l%2==1) total +=sum+1, f[j++]=sum+1;

  f[j++] = total;

  qsort(f, j, sizeof(int), compDig);

  fout = fopen("templu.out", "w");
  for(int i=0; i<j; i++){
    fprintf(fout, "%d", f[i]);
    sprintf(str+strlen(str), "%d", f[i]);
  }  
  int max = 0;
  for(int i=0; i<strlen(str)-1; i++){
    int n = (str[i]-'0')*10+(str[i+1]-'0');
    if(n>max) max = n;
  }
  fprintf(fout, "\n%d\n", max);
  fclose(fout);
}
