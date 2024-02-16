#include <stdio.h>
#include <string.h>

#define MAXN 101

int n;
int p10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
int v[MAXN];
char baban[MAXN*9]; int size;
char max[MAXN*9]; int maxsize;

int main(){
  FILE *fin, *fout;
  fin = fopen("mare.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }
  fclose(fin);

  for(int i=0; i<n; i++){
    size = 0;
    for(int j=i; j<n; j++){
      int copy = v[j];
      int p = 0;
      while(p10[p+1]<=copy)p++;
      while(p>=0){
        baban[size++] = copy/p10[p];
        copy%=p10[p];
        p--;
      }
      int i = size-1;
      int j = 0;
      while(i>j && baban[i]==baban[j])
        i--, j++;
      if(i<=j){
        if(size>maxsize ||(size==maxsize && memcmp(baban, max, size)==1)){
          maxsize = size;
          memcpy(max, baban, size);
        }
      }
    }
  }

  fout = fopen("mare.out", "w");
  for(int i=0; i<maxsize; i++)
    fprintf(fout, "%d", max[i]);
  fprintf(fout, "\n");
  fclose(fout);
  return 0;
}
