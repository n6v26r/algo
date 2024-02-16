#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 10
#define MAXM 10
#define MAXLEN 40

int t, n;

int exclude[MAXN][MAXM][MAXN][MAXM];
int price[MAXN][MAXM];
char string[MAXLEN]; int slen;

typedef struct{
  char name[MAXLEN];
  int namelen;
  int price;
} med;

typedef struct{
  int i;
  int j;
}pair;

med list[MAXN][MAXM];
med names[MAXN*MAXM+1];
int size[MAXN];

void addNewMed(int i, int j, char *str, int slen, int price){
  string[slen] = '\0';
  strcpy(list[i][j].name, string); list[i][j].namelen = slen;
  list[i][j].price = price;
  price = 0;
  slen = 0;
  j++;
}

int compMed(const void *a, const void *b){
  med _a = *((const med*)a);
  med _b = *((const med*)b);

  return _a.price-_b.price;
}

pair search(char* str){
  for(int i=0; i<n; i++){
    for(int j=0; j<size[i]; j++){
      if(strcmp(list[i][j].name, str)==0) return (pair){i, j};
    }
  }
  return (pair){-1, -1};
}


pair sel[MAXN];

int verify(int i, int j){
  for(int pos = i-1; pos>=0; pos--){
    if(exclude[i][j][sel[pos].i][sel[pos].j]==1) {
      return 0;
    }
  }
  return 1;
}

int min = __INT_MAX__;
void findMin(int i, int j, int sum){
  if(i>=n){
    if(sum<min) min = sum;
    findMin(i-1, sel[i-1].j+1, sum-list[i-1][sel[i-1].j].price);
  }
  else{
    if(sum>min || (j>=size[i] && i>0)) findMin(i-1, sel[i-1].j+1, sum-list[i-1][sel[i-1].j].price);
    else if (j>=size[i] && i==0) return;
    else if(verify(i, j)){
      sel[i] = (pair){i, j};
      findMin(i+1, 0, sum+list[i][j].price);
    }
    else
      findMin(i, j+1, sum);
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("farma.in", "r");
  fscanf(fin, "%d%d\n", &t, &n); fgetc(fin);
  int total = 0;
  for(int i=0; i<n; i++){
    char c = fgetc(fin); while(c==' ') c = fgetc(fin);
    while(isalpha(c)){c=fgetc(fin);}
    while(c==' ' || c==':') c = fgetc(fin);
    slen = 0;
    int j = 0;
    int price = 0;
    while(c!='\n'){
      if(c==','){
        addNewMed(i, j, string, slen, price);
        slen = price = 0;
        j++;
        total++;
      }
      else if(c==' ') {fscanf(fin, "%d", &price);c = fgetc(fin); continue;}
      else string[slen++] = c;

      c = fgetc(fin);
    }
    total++;
    addNewMed(i, j, string, slen, price);
    qsort(list[i], j+1, sizeof(med), compMed);
    size[i] = j+1;
  }

  int q;
  fscanf(fin, "%d", &q); fgetc(fin);
  for(int i=0; i<q; i++){
    slen = 0;
    pair p1, p2;
    char c = fgetc(fin);
    while(c!='/'){string[slen++] = c; c=fgetc(fin);}
    string[slen] = '\0';
    p1 = search(string);
    slen = 0;

    c = fgetc(fin);
    while(c!='\n'){string[slen++] = c; c=fgetc(fin);}
    string[slen] = '\0';
    p2 = search(string);
    exclude[p1.i][p1.j][p2.i][p2.j] = 1;
    exclude[p2.i][p2.j][p1.i][p1.j] = 1;
  }
  fclose(fin);

  findMin(0, 0, 0);

  fout = fopen("farma.out", "w");
  if(t==2)
    fprintf(fout, "%d\n", min);
  else{
    for(int i=0; i<n; i++){
      fprintf(fout, "%d\n", size[i]);
    }
  }
  fclose(fout);
}
