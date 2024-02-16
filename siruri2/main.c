// this crappy piece of code is provided to u
// by __razv
#include <stdio.h>

#define MAXSIZE 502
#define MIN(a, b) ((a)<(b)?(a):(b))

char a[MAXSIZE]; int sizea;
char b[MAXSIZE]; int sizeb;

int lev[MAXSIZE][MAXSIZE];

void readString(char *s, int *size, FILE *fin){
  char c = fgetc(fin);
  int i = 1;
  while(c!='\n'){
    if('A'<=c && c<='Z') c += 32;
    s[i++] = c;
    c = fgetc(fin);
  }
  *size = i-1;
  s[i] = '\0';
}

int main(){
  FILE *fin, *fout;
  fin=fopen("siruri2.in", "r");
  readString(a, &sizea, fin);
  readString(b, &sizeb, fin);
  fclose(fin);

  for(int i=0; i<=sizea; i++){
    lev[i][0] = i;
  }
  for(int j=0; j<=sizeb; j++){
    lev[0][j] = j;
  }

  for(int i=1; a[i]!='\0'; i++){
    for(int j=1; b[j]!='\0'; j++){
      if(sizea==0) lev[i][j] = sizeb;
      if(sizeb==0) lev[i][j] = sizea;
      
      if(a[i]==b[j]) lev[i][j] = lev[i-1][j-1];
      else lev[i][j] = 1 + MIN( lev[i-1][j], MIN (lev[i][j-1], lev[i-1][j-1]) );
   }
  }

  fout=fopen("siruri2.out", "w");
  fprintf(fout, "%d\n", lev[sizea][sizeb]);
  fclose(fout);
  return 0;
}
