#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLEN 60

int n;
char k[MAXLEN+1];

int charToNumber(char c){
  return (isdigit(c)?(c-'0'):(c-'A'+10)); 
}

unsigned long long toB10(int base, char* num, int i){
  unsigned long long pow = 1;
  unsigned long long result = 0;
  i--;
  while(i>=0){
    result += charToNumber(num[i])*pow;
    pow*=base;
    i--;
  }
  return result;
}

int main(){
  int s=2, d=1, m;
  d=2000000001;
  FILE *fin, *fout;
  fin=fopen("ascunsa.in", "r");
  fscanf(fin, "%d\n", &n);
  int i=0;
  char c = fgetc(fin);
  while(c!='\n'){
    k[i++] = c;
    if(s<charToNumber(c)) s = charToNumber(c);
    c = fgetc(fin);
  }
  fclose(fin);
  s--;
  while(s<d-1){
    m = (s+d)/2;
    if(toB10(m, k, i)>(unsigned long long)n)
      d = m;
    else s = m;
  }

  fout = fopen("ascunsa.out", "w");
  fprintf(fout, "%lld %d\n", toB10(d, k, i), d);
  fclose(fout);
  return 0;
}
