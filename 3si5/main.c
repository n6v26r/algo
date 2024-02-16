#include <stdio.h>
#include <stdlib.h>

#define MAXPOW 19

int n;
long long pow5[MAXPOW+1];
long long pow3[MAXPOW+1];

void _pow(){
  pow5[0] = 1;
  pow3[0] = 1;
  for(int i=1; i<=MAXPOW; i++){
    pow5[i] = pow5[i-1]*5;
    pow3[i] = pow3[i-1]*3;
  }
}

long long bintobase(int base, int val){
  long long result = 0;
  long long pow = 0;
  while(val>0){
    result += (val&1)*(base==3?pow3[pow]:pow5[pow]);
    pow++;
    val>>=1;
  }
  return result;
}

int main(){
  _pow();
  FILE *fin, *fout;
  fin = fopen("3si5.in", "r");
  fscanf(fin, "%d", &n);
  fclose(fin);
 
  fout = fopen("3si5.out", "w");
  int trei = 1; 
  int cinci = 1;
  long long next3 = bintobase(3, trei);
  long long next5 = bintobase(5, cinci);
  while(trei<=n || cinci<=n){
    if(next3<next5 && trei<=n){
      fprintf(fout, "%lld\n", next3);
      trei++;
      next3 = bintobase(3, trei);
    }
    else{
      fprintf(fout, "%lld\n", next5);  
      cinci++;
      next5 = bintobase(5, cinci);
    }
  }
  fclose(fout);
  return 0;
}
