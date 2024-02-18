#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100000
#define IPSIZE 39

char v[MAXSIZE+1][IPSIZE+1];
int n;

int compStr(const void* a, const void* b){
  char *_a = (char*)a;
  char *_b = (char*)b;

  return strcmp(_a, _b);
}

int main(){
  int p;
  FILE *fin, *fout;
  fin=fopen("controlnode.in", "r");
  fscanf(fin, "%d\n", &p);
  char c = fgetc(fin);
  int i=0;
  while(1){
    int j=0;
    if(c=='#') break;
    while(c!='\n'){
      v[i][j++] = c;
      c=fgetc(fin);
    }
    v[i][j] = '\0';
    i++;
    c=fgetc(fin);
  }
  n=i;
  fclose(fin);

  qsort(v, n, IPSIZE+1, compStr);

  //for(int i=0; i<n; i++){
   // printf("%s\n", v[i]);
  //}

  fout=fopen("controlnode.out", "w");
  if(p==2)
    for(int i=0; i<n; i++){
      fprintf(fout, "%s\n", v[i]);
    }
  else{
    int i=0;
    int dif = 0;
    while(i<n){
      *(v[i]+19) = '\0';
      //printf("i:%d\n", i);
      dif++;
      i++;
      while(i<n){
        *(v[i]+19) = '\0';
        if(!strcmp(v[i], v[i-1])){
          //printf("%s\n", v[i]);
          //printf("%s\n", v[i-1]);
          //printf("\n\n");
          i++;
        }
        else
          break;
      }
    }
    fprintf(fout, "%d\n", dif);
  }

  fclose(fout);
  return 0;
}
