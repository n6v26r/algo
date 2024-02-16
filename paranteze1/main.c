#include <stdio.h>
#include <stdlib.h>
char v[1000001];
int main()
{
  int paranteze=0, acolade=0, max=0, i;
  char c;
    FILE *fin, *fout;
    fin=fopen("paranteze1.in", "r");
    c=fgetc(fin);
    i=0;
    while(c!='\n' && i>-1){
      switch(c){
        case '(':
          paranteze++;
          v[i]='(';
          i++;
          break;
 
        case')':
          if(v[i-1]=='('){
              paranteze--;
            v[i-1]=0;
            i--;
          }
          else
            i=-1;
          break;
 
        case'{':
          acolade++;
          v[i]='{';
          i++;
          break;
 
        case'}':
          if(v[i-1]=='{'){
            acolade--;
            v[i-1]=0;
            i--;
          }
          else
            i=-1;
          break;
 
        default:
          i=-1;
      }
      if(i>max)
        max=i;
     c=fgetc(fin);
    }
    fclose(fin);
 
    fout=fopen("paranteze1.out", "w");
    if (paranteze==0 && acolade==0 && i>-1)
      fprintf(fout, "%d", max);
    else
      fprintf(fout, "-1");
    fclose(fout);
    return 0;
}
