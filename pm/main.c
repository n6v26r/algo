// dp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXY 250

typedef struct{
  int size;
  unsigned char num[50]; 
}baban;

baban* mat[2*MAXY+1];

unsigned char get(baban a, int i){
  unsigned char byte = a.num[i/2];
  if(i%2) return (unsigned char)(byte<<4)>>4;
  return byte>>4;
}

void set(baban *a, int i, int cif){
  unsigned char byte = a->num[i/2];
  if(i%2) byte = ((byte>>4)<<4) + cif;
  else byte = ((byte<<4)>>4) + (cif<<4);
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
  mat[0] = (baban*)malloc(5*sizeof(baban));
  mat[1] = (baban*)malloc(5*sizeof(baban));
  for(int i=2; i<2*MAXY+1; i++){
    mat[i] = (baban*)malloc((i/2+1)*sizeof(baban));
  }
  int p, m;
  FILE *fin, *fout;
  fin = fopen("pm.in", "r");
  fscanf(fin, "%d %d\n", &p, &m);
  fclose(fin);

  mat[1][0]=mat[1][1] = (baban){1, {16}};
  for(int l=2; l<=p+m; l++){
    for(int y=0; y<=l/2+1; y++){
      baban new = {1, {0}};
      if(l>=2){ if(y>1) new = add(new, mat[l-2][y-1]);
                else if(y==1) new = add(new, mat[l-1][y-1]);
      }
      if(l>=1) new = add(new, mat[l-1][y]);
      mat[l][y] = new;
    }
  }

  fout = fopen("pm.out", "w");
  print(mat[p+m][m], fout);
  fclose(fout);
  return EXIT_SUCCESS;
}

