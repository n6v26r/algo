#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 6000
#define MAXLEN 20


char v[MAXSIZE+1][MAXLEN+1];
long long give[MAXSIZE+1];
long long get[MAXSIZE+1];
int n;
int size = 0;

void _strcpy(char *a, const char *b){
  int i;
  for(i=0; b[i]!='\0'; i++){
    a[i] = b[i];
  }
  a[i]='\0';
}

int _strcmp(char *a, char *b){
  for(int i=0; a[i]!='\0'||b[i]!='\0'; i++){
    if(a[i]<b[i])
      return -1;
    else if(b[i]<a[i])
      return 1;
  }
  return 0;
}

void writeLL(long long a, FILE *fout){
  long long p10 = 1;
  while(p10*10<=a)
    p10*=10;
  while(p10>0){
    int c = 0;
    while(a-p10>=0){
      a-=p10;
      c++;
    }
    fputc(c+'0', fout);
    p10/=10;
  }
}

int find(char* a){
  int s=-1, d=size;
  int m;
  while(d-s>1){
    m = (s+d)/2;
    if(_strcmp(v[m], a)<0)
      s = m;
    else
      d = m;
  }
  return d;
}

void addS(char *string, int index){
  for(int i = size; i>index; i--){
    _strcpy(v[i], v[i-1]);
    give[i] = give[i-1];
    get[i] = get[i-1];
  }
  _strcpy(v[index], string);
  give[index] = get[index] = 0;
  size++;
}

void addDatorie(char *a, char *b, int val){
  int apos = find(a);
  if(_strcmp(v[apos], a)!=0) addS(a, apos);
  int bpos = find(b);
  if(_strcmp(v[bpos], b)!=0) addS(b, bpos);
  if(bpos<=apos)
    apos = find(a);
  give[apos] += val;
  get[bpos] += val;
}

int main(){
  int p;
  FILE *fin, *fout;
  fin=fopen("datorii.in", "r");
  fscanf(fin, "%d%d\n", &p, &n);
  char *a = malloc(20);
  char *b = malloc(20);
  for(int i=0; i<n; i++){
    char c = fgetc(fin);
    int i = 0;
    while(c!='>'){
      a[i++] = c;
      c = fgetc(fin);
    }
    a[i-1] = '\0';

    c=fgetc(fin);
    c=fgetc(fin);
    i = 0;
    while(c!='\n'){
      b[i++] = c;
      c = fgetc(fin);
    }
    i--;
    int val = 0;
    int p10 = 1;
    while(i>0 && b[i]!=' '){
      val = val+p10*(b[i]-'0');
      p10*=10;
      i--;
    }
    b[i]='\0';
    addDatorie(a, b, val);
  }
  free(a);
  free(b);
  fclose(fin);

  fout=fopen("datorii.out", "w");
  if(p==1) fprintf(fout, "%d\n", size);
  else{
    for(int i=0; i<size; i++){
      int j=0;
      while(v[i][j]!='\0'){
        fputc(v[i][j], fout);
        j++;
      }
      fputc(' ', fout);
      writeLL(give[i], fout);
      fputc(' ', fout);
      writeLL(get[i], fout);
      fputc('\n', fout);
    }
  }
  fclose(fout);
  return 0;
}
