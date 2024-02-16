#include <iostream>

using namespace std;

inline int getB(char c){
  switch(c){
    case 'm':
      return 1000;
      break;
    case 's':
      return 100;
      break;
    case 'z':
      return 10;
      break;
    case 'u':
      return 1;
      break;
    default:
      printf("Cheating");
      exit(-1);
      break;
  }
}

#define MAXN 1007

bool ans[MAXN];

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("comp.in", "r");
  fout = fopen("comp.out", "w");
  fscanf(fin, "%d\n", &n);
  int cnt = 0;
  for(int i=0; i<n; i++){
    int numar[2] = {0, 0};
    char comp;
    int idx = 0;
    char c = '@';
    int n = 0;
    while(c!='\n' && c!=EOF){
      int val;
      fscanf(fin, "%d", &val);
      c = fgetc(fin);
      n += val*getB(c);
      c = fgetc(fin);

      if(c=='<' || c=='>')numar[idx]+=n, n=0, comp = c, idx++;
      else if(c == '+')numar[idx]+=n, n = 0;
      else if(c=='\n' || c==EOF) numar[idx]+=n, n=0;
      else ungetc(c, fin);

      if(c=='<') cnt++;
    }
    if(comp=='>') ans[i] = numar[0]>numar[1];
    else ans[i] = numar[0]<numar[1];
  }

  fprintf(fout, "%d\n", cnt);
  for(int i=0; i<n; i++){
    fprintf(fout, "%d\n", ans[i]);
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
