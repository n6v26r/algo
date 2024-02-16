#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int v[MAXN+1];
int uses[MAXN+2];
int sum;

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("butoane.in", "r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    sum += v[i];
  }
  sum/=n;
  fclose(fin);


  for(int i=0; i<n-1; i++){
    if(i==0) {
      int dif = sum-v[0];
      if(dif>0) v[0]+=dif, v[1]-=2*dif, v[2]+=dif, uses[1]+=abs(dif);
      else v[0]+=dif, v[1]-=dif, uses[0]+=abs(dif);
    }
    else if(i==n-2){
      int dif = sum-v[n-2];
      if(dif>0) v[n-2]+=dif, v[n-1]-=dif, uses[n-1]+=abs(dif);
      else if(dif!=0) v[n-3]-=dif, v[n-2]+=2*dif, v[n-1]-=dif, uses[n-2]+=abs(dif), i=n-4;
    }
    else{
      int dif = sum-v[i];
      if(dif>0) v[i]+=dif, v[i+1]-=2*dif, v[i+2]+=dif, uses[i+1]+=abs(dif);
      else if(dif!=0) v[i-1] -=dif, v[i]+=2*dif, v[i+1]-=dif, uses[i]+=abs(dif), i-=2;
    }
  }

  fout = fopen("butoane.out", "w");
  for(int i=0; i<n; i++){
    fprintf(fout, "%d\n", uses[i]);
  }
  fclose(fout);
  return 0;
}
