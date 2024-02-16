#include <iostream>
using namespace std;

#define MAXN 5001
#define SEC (60*60*4)

int mark[SEC+1];

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("elfi.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    int val, val2;
    fscanf(fin, "%d %d", &val, &val2);
    int m = 2*val+val2;
    for(int d=m; d<=SEC; d+=m+1){
      mark[d]++;
    }
  }
  fclose(fin);

  int m = 0;
  for(int i=0; i<=SEC; i++)
    if(mark[i]>m)m=mark[i];

  fout = fopen("elfi.out", "w");
  fprintf(fout, "%d\n", m);
  fclose(fout);
  return 0;
}
