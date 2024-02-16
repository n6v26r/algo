#include <stdio.h>

#define MAXSIZE 1001

int f[10];
int baban[MAXSIZE];
int sol[MAXSIZE];

int getBigger(int n){
  for(int i=n+1; i<10; i++)
    if(f[i]>0) return i;
  return -1;
}

void getNumber(int size1, int size2){
  if(size2>size1){
    int i = 0;
    for(int j=1; j<10; j++) if(f[j]){f[j]--; sol[i++]=j;break;}
    for(int j=0; j<10; j++){
      while(f[j]>0){f[j]--; sol[i++]=j;}
    }
    return;
  }

  int i = 0;
  while(f[baban[i]]>0){
    sol[i] = baban[i];
    f[baban[i]]--;
    i++;
  }
  int next = getBigger(baban[i]);
  if(next!=-1){
    sol[i] = next;
    f[next]--;
  }
  else{
    int prev;
    do{
      i--;
      f[baban[i]]++;
      prev = getBigger(baban[i]);
      if(prev!=-1) sol[i] = prev, f[prev]--;
    }while(prev==-1);
  }
  i++;
  for(int j=0; j<10; j++){
    while(f[j]>0){f[j]--; sol[i++]=j;}
  }
}

int main(){
  int a, b, c, c1, c2, c3;
  FILE *fin, *fout;
  fin = fopen("tcif.in", "r");
  fscanf(fin, "%d%d%d%d%d%d\n", &a, &b, &c, &c1, &c2, &c3);
  f[c1]=a;
  f[c2]=b;
  f[c3]=c;
  char ch = fgetc(fin);
  int i = 0;
  while(ch!='\n'){
    baban[i++] = ch-'0';
    ch = fgetc(fin);
  }
  fclose(fin);

  getNumber(i, a+b+c);

  fout = fopen("tcif.out", "w");
  for(int i=0; i<a+b+c; i++)
    fputc(sol[i]+'0', fout);
  fputc('\n', fout);
  fclose(fout);
  return 0;
}
