// ONI 2022 baraj gimnaziu
// __razv was here
/// WARN: very messy code

#include <stdio.h>
#include <string.h>
#define MAXN 111111

int p;

int v[MAXN]; int n;
int cif[MAXN][10];
int blocks[MAXN];

int solve[MAXN]; int m;

void inverse(int *v, int sz){
  int i = sz-1;
  int j = 0;
  while(i>j){
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;

    i--;
    j++;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("bug.in", "r");
  fscanf(fin, "%d\n", &p);
  int i = 0;
  char c = fgetc(fin);
  while(c!='\n' && c!=EOF){
    v[i] = c-'0';
    for(int j=0; j<10; j++)cif[i][j] += (i>0?cif[i-1][j]:0);

    cif[i][v[i]]++;
    i++;
    c = fgetc(fin);
  }
  n = i;
  fclose(fin);

  int grupe = 0;
  int last = n-1;
  int lastCif = 0;
  for(int i = n-1; i>=0; i--){
    int j;
    for(j=1; j<=10; j++){
      int ap = cif[last][j%10] - (i>0?cif[i-1][j%10]:0);
      if(ap<1) break;
    }
    if(j>10 || (i==0 && j==10)){
      if(i==0){
        lastCif = 1;
        solve[m++] = 1;
      }
      blocks[grupe] = i;
      grupe++;
      last = i-1;
    }
    else if(i==0){
      lastCif = j;
      solve[m++] = j;
    }
  }

  inverse(blocks, grupe);

  blocks[grupe] = n;

  for(int i=0; i<grupe; i++){
    int lastPos = -1;
    for(int j=blocks[i]; j<blocks[i+1]; j++){
      if(v[j] == lastCif){
        lastPos = j; break;
      }
    }
    int j = 0;
    for(j=0; j<10; j++){
      if(cif[blocks[i+1]-1][j]-cif[lastPos][j]<1) break;
    }
    solve[m++] = j%10;
    lastCif = j%10;
  }

  fout = fopen("bug.out", "w");
  if(p==1)
    fprintf(fout, "%d\n", grupe+1);
  else{
    int i = 0; while(solve[i]==0) i++;
    for(; i<m; i++) fprintf(fout, "%d", solve[i]);
    fprintf(fout, "\n");
  }
  fclose(fout);
}
