#include <iostream>
using namespace std;

#define MAXN 3000001

int f[128];
bool used[128];

int sstack[30]; int sp = -1;
char v[MAXN];

int main(){
  FILE *fin = fopen("cmmstr.in", "r");
  FILE *fout = fopen("cmmstr.out", "w");
  int n = 0;
  char c = fgetc(fin);
  while(c!='\n' && c!=EOF){
    v[n++] = c;
    f[c]++;
    c = fgetc(fin);
  }
  for(int i=0; i<n; i++){
    if(used[v[i]]) continue;
    while(sp>=0 && v[sstack[sp]]>=v[i] && f[v[sstack[sp]]]>1){
      used[v[sstack[sp]]] = false;
      f[v[sstack[sp]]]--;
      sp--;
    }
    if(sp>=0) used[v[sstack[sp]]] = true;
    sstack[++sp] = i;
  }

  for(int i=0; i<=sp; i++){
    fprintf(fout, "%c", v[sstack[i]]);
  }
  fprintf(fout, "\n");
  fclose(fin);
  fclose(fout);
  return 0;
}
