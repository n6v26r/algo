#include <stdio.h>
#include <stack>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 1001

int str[MAXSIZE];

int p;

int ans1;
int ans2;

int getNum(int *idx){
  *idx ++;
  int num = 0;
  while(isdigit(str[*idx])){
    num = num * 10 + str[*idx]-'0';
    *idx++;
  }

  return num;
}

int eval(a, int idx){
  switch(str[idx]){
    case '(':
      return a + eval(0, idx+1);
      break;
    case ')':
      return a*getNum(&idx);
      break;
    default:
      if(isdigit(str[idx]))
      break;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("valoare.in", "r");
  fscanf(fin, "%d\n", &p);
  char c = fgetc(fin);
  int idx = 0;
  while(c!='\n'){
    str[idx++] = c;
    c = fgetc(fin);
  }
  fclose(fin);

  fout = fopen("valoare.out", "w");
  fprintf(fout, "%d\n", );
  fclose(fout);
  return 0;
}
