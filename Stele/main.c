#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSIZE 1000

int p[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
            65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
            16777216, 33554432, 67108864};
int t, n;

typedef struct{
  int size;
  char cifre[MAXSIZE];
}baban;

void inverse(baban *a){
  int i = 0;
  int j = (*a).size-1;
  while(i<j){
    int aux = (*a).cifre[i];
    (*a).cifre[i] = (*a).cifre[j];
    (*a).cifre[j] = aux;

    i++;
    j--;
  }
}

void addint(baban *a, int b){
  int i = 0;
  while(b>0){
    b+=(*a).cifre[i];
    (*a).cifre[i] = b%10;
    b/=10;

    i++;
  }
  if(i>(*a).size)
    (*a).size = i;
}

void add(baban *a, baban b){
  int i = 0;
  int sum = 0;
  while(i<(*a).size || i<b.size){
    sum += (*a).cifre[i] + b.cifre[i];
    (*a).cifre[i] = sum%10;
    sum/=10;

    i++;
  }
  if(sum>0){
    (*a).cifre[i] += sum;
    i++;
  }

  (*a).size = i;
}

void multiply(baban *a, int b){
  int i = 0;
  int sum = 0;
  while(i<(*a).size){
    sum += (*a).cifre[i]*b;
    (*a).cifre[i] = sum%10;

    sum/=10;
    i++;
  }
  while(sum>0){
    (*a).cifre[i] = sum%10;
    sum/=10;
    i++;
  }
  (*a).size = i;
}

baban null = {0, {}};

baban _new;
baban number;
baban total;
baban s;

int main(){
  FILE *fin, *fout;
  fin = fopen("stele.in", "r");
  fscanf(fin, "%d%d", &t, &n); fgetc(fin);
  if(t==2){
    total = (baban){1, {0}};
    for(int i = 0; i<n; i++){
      char c = fgetc(fin);
      _new = null;
      number = null;
      while(isdigit(c)){_new.cifre[_new.size++] = c-'0'; c = fgetc(fin);}
      inverse(&_new);
      while(c!='\n' && c!=EOF){
        if(p[c-'a'] != (1<<(c-'a'))) return -1;
        if(_new.size != 0){
          multiply(&_new, p[c-'a']);
        }
        else{
            _new = (baban){1, {0}};
          addint(&_new, p[c-'a']);
        }
        add(&number, _new);
        c = fgetc(fin);
        _new = null;
        while(isdigit(c)){_new.cifre[_new.size++] = c-'0'; c = fgetc(fin);}
        inverse(&_new);
      }
        add(&total, number);
    }
  }
  fclose(fin);

  fout = fopen("stele.out", "w");
  if(t==2){
    for(int i=total.size-1; i>=0; i--){
      fprintf(fout, "%d", total.cifre[i]);
    }fprintf(fout, "\n");
  }
  else{
    for(int j=25; n>0 && j>=0; j--){
      int i = p[j];
      if(i>n) continue;
      baban fit = {1, {0}};
      while(i<=n){
        add(&fit, (baban){1, {1}}); n-=i;
      }
      inverse(&fit);
      s.cifre[s.size++] = 'a'+j;
      if(fit.size>1 || fit.size==1 && fit.cifre[0]>1)
        for(int i=0; i<fit.size; i++) s.cifre[s.size++] = fit.cifre[i]+'0';
    }
    inverse(&s);
    s.cifre[s.size] = '\0';
    fprintf(fout, "%s\n", s.cifre);
  }
  fclose(fout);
}
