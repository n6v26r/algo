#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXY 250

typedef struct{
  int size;
  unsigned char num[50]; 
}baban;

baban mat[MAXY+2][MAXY+1];

unsigned char get(baban a, int i){
  // printf("g %d:", i);
  unsigned char byte = a.num[i/2];
  // printf("%d => ", byte);
  // if(i%2) printf("%d\n", (unsigned char)(byte<<4)>>4);
  // else printf("%d\n", byte>>4);
  if(i%2) return (unsigned char)(byte<<4)>>4;
  return byte>>4;
}

void set(baban *a, int i, int cif){
  unsigned char byte = a->num[i/2];
  // printf("s %d, %d: %d =>", i, cif, byte);  
  if(i%2) byte = ((byte>>4)<<4) + cif;
  else byte = ((byte<<4)>>4) + (cif<<4);
  // printf("%d\n", byte);
  a->num[i/2] = byte;
}

void print(baban a, FILE *fout){
  int i = a.size-1;
  while(i>=0){
    fputc((int)get(a, i)+'0', fout);
    i--;
  }
  fputc('\n', fout);
}

baban add(baban a, baban b){
  baban c = {0, {}};
  int t = 0;
  int i = 0;
  while(i<a.size || i<b.size){
    t += get(a, i)+get(b, i);
    set(&c, i, t%10);
    t/=10;
    i++;
  }
  while(t>0){
    set(&c, i, t%10);
    t/=10;
    i++;
  }
  c.size = i;
  return c;
}

baban comb(int n, int k){
  if(k<0) return (baban){1, {0}};
  if(mat[n][k].size) return mat[n][k];

  if(n==0) return (baban) {1, {(k==0)<<4}};
  mat[n][k] = add(comb(n-1, k-1), comb(n-1, k));
  return mat[n][k];
}

int main(){
  int p, m;
  FILE *fin, *fout;
  fin = fopen("pm.in", "r");
  fscanf(fin, "%d %d\n", &p, &m);
  fclose(fin);

  baban x = comb(p+1, m);

  fout = fopen("pm.out", "w");
  print(x, fout);
  fclose(fout);
  return EXIT_SUCCESS;
}

