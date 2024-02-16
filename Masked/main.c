#include <stdio.h>
#include <ctype.h>

int main(){
  FILE *fin, *fout;
  fin = fopen("masked.in", "r");
  fout = fopen("masked.out", "w");
  char c = fgetc(fin);
  int i = 0;
  int n = 0;
  int first;
  while(c!=EOF){
    if(i>5){
      if(first=='M')
        fputc(n+('A')-1, fout);
      else
        fputc(n+('a')-1, fout);
      i = 0;
      n = 0;
    }
    if(isalpha(c)){
      if(i==0){
        first = c;
        i++;
        c=fgetc(fin);
        continue;
      }
      n = n + ('A'<=c && c<='Z')*(1<<(5-i));
      i++;
    }
    else{
      fputc(c, fout);
    }
    c=fgetc(fin);
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
