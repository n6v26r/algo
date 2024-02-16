#include <stdio.h>
#include <string.h>

#define MAXN 100000

int n, q;
int v[MAXN+1];
int stack[MAXN+1], sp=-1; 
int s[MAXN+1]; 
int d[MAXN+1];

int main(){
  memset(s, -1, sizeof(s));
  memset(d, -1, sizeof(d));
  FILE *fin, *fout;
  fin = fopen("nrapp.in", "r");
  fscanf(fin, "%d", &n);
  fout = fopen("nrapp.out", "w");
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
  }

  for(int i=0; i<n; i++){
    while(sp>-1 && v[stack[sp]]>=v[i]){
      sp--;
    }

    if(sp>-1)s[i]=stack[sp];
    stack[++sp] = i;
  }

  sp = -1; // clear stack
  
  for(int i=n-1; i>=0; i--){
    while(sp>-1 && v[stack[sp]]>=v[i]){
      sp--;
    }
    if(sp>-1)d[i]=stack[sp];
    stack[++sp] = i;
  }

  fscanf(fin, "%d\n", &q);
  int y;
  char c;
  for(int i=0; i<q; i++){
    fscanf(fin, "%c %d\n", &c, &y);
    int ans;
    switch (c){
      case 'S':
        ans = s[y-1]+1;
        fprintf(fout, "%d\n", ans);
        break;
      case 'D':
        ans = d[y-1]+1;
        if(ans>0)
          fprintf(fout, "%d\n", ans);
        else
          fprintf(fout, "%d\n", n+1);
        break;
      default:
        break;
    }
  }
  fclose(fin);
  fclose(fout);
}
