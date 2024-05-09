// ONI 2015 8th grade
// __razv was here

#include <stdio.h>

int n, p, c;

int pw(int b, int e){
  int pw = 1;
  while(e>0){
    if(e%2) pw=((long long)pw*b)%p;
    b=((long long)b*b)%p;
    e/=2;
  }
  return pw;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("magic.in", "r");
  fscanf(fin, "%d%d%d", &c, &n, &p);
  fclose(fin);

  int rest = pw(c, n-1);
  fout = fopen("magic.out", "w");
  fprintf(fout, "%d\n", (p+rest-1)%p+1);
  fclose(fout);
}
