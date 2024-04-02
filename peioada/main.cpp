#include <stdio.h>

int euclid(int a, int b){
  while(b>0){
    int r=b;
    b=a%b;
    a=r;
  }
  return a;
}

 char Fsimpla(int b){

  while(!(b%2))
    b/=2;
  while(!(b%5))
    b/=5;


  if(b!=1)
    return 0;
  return 1;
}

 int exp(int a, int b){
  int e=0;
  while(!(b%a))
   {b/=a;e++;}

  return e;
}

 int max(int a, int b){
  if(a>b)
    return a;
  return b;
}

 int Psimpla(FILE *fout, int a, int b){
  int cif = max(exp(2, b), exp(5, b));

  while(a%b>0 && cif>0){
    fprintf(fout, "%d", a/b);
    a=a%b*10;
    cif--;
  }
  if(a%b==0)
    fprintf(fout, "%d", a/b);

  return a;
}

int perioada(FILE *fout, int a, int b){
    int r=a;
    int i = 0;
    do{
      a=a%b*10;
      i++;
    }while(a!=r);
  return i;
}

int main(){
  // F BRUTA
  int a, b;
  FILE *fin, *fout;
  fin=fopen("perioada1.in", "r");
  fscanf(fin, "%d", &b);
  fclose(fin);

  a = 1;

  int cmmdc = euclid(a, b);
  a/=cmmdc;
  b/=cmmdc;

  fout=fopen("perioada1.out", "w");
  a=a%b*10;

  if(!Fsimpla(b))
    fprintf(fout, "%d\n", perioada(fout, a, b));
  fclose(fout);
  return 0;
}
