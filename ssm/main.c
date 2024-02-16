#include <stdio.h>
#include <ctype.h>
 
void readInt(int* n, FILE *fin){
  char c = fgetc(fin);
  *n = 0;
  int semn = 1;
  while(!isdigit(c)){
    if(c=='-')
      semn*=-1;
    c=fgetc(fin);
  }
  while(isdigit(c)){
    (*n)=(*n)*10+semn*(c-'0');
    c=fgetc(fin);
  }
}
 
int main(){
  int n;
  FILE *fin, *fout;
  fin=fopen("ssm.in", "r");
  fscanf(fin, "%d", &n);
  int val;
  int sum =0;
  int start =0;
  int end =0 ;
  int max=0;
  int ms=0, me=0;
  for(int i=0; i<n; i++){
    readInt(&val, fin);
    if(!i) max = val;
    if(0<=sum)
      sum+=val, end++;
    else
      sum = val, end = start = i;
 
    if(sum>max)
      max = sum, ms= start, me = end;
  }
  fclose(fin);
 
  fout=fopen("ssm.out", "w");
  fprintf(fout, "%d %d %d\n", max, ms+1, me+1);
  fclose(fout);
  return 0;
}
