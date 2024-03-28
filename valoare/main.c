// __razv was here
// ONI 2021 8th grade
// https://kilonova.ro/problems/1582?list_id=564
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXSIZE 1001

int p;
char str[MAXSIZE];
char cif[27];
int end;

long long sumNum = 0;

long long getNumber(long long *idx){
  long long n = 0;
  while(isdigit(str[*idx])){
    n = n * 10 + str[*idx]-'0';
    (*idx) ++;
  }
  sumNum += n;
  return n;
}

long long eval(long long a, long long b, long long idx){
  switch(str[idx]){
    case '(':;
      {
      long long sum = eval(0, 0, idx+1);
      return eval(a+b, sum, end);
      break;
      }
    case ')':
      {
      idx++;
      a = (a + b) * getNumber(&idx);
      end = idx;
      return a;
      break;
      }
    case '\0':
      {
      return a+b;
      break;
      }
    default:
      {
      if(isdigit(str[idx])){
        b = b*getNumber(&idx);
        return eval(a+b, 0, idx);
      }
      return eval(a+b, str[idx]-'A'+1, idx+1);
      break;
      }
  }
}

int main(){
  memset(str, '\0', sizeof(str));
  FILE *fin, *fout;
  fin = fopen("valoare.in", "r");
  fscanf(fin, "%d\n", &p);
  char c = fgetc(fin);
  int idx = 0;
  while(c!='\n' && c!=EOF){
    str[idx++] = c;
    if(isalpha(c))cif[c-'A'] = 1;
    c = fgetc(fin);
  }
  fclose(fin);


  fout = fopen("valoare.out", "w");
  if(p==1){
    int total = 0;
    for(int i=0; i<27; i++) total+=cif[i];
    fprintf(fout, "%d\n", total);
  }
  else if(p==2) {eval(0, 0, 0);fprintf(fout, "%lld\n", sumNum);}
  else fprintf(fout, "%lld\n", eval(0, 0, 0));
  fclose(fout);
}
