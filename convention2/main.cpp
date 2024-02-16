#include <iostream>

using namespace std;

typedef struct{
  int ord;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("convention2.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);

  fout = fopen("convention2.out", "w");
  fclose(fout);
}
