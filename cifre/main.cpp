// ONI 2014 8th grade
// __razv was here
// ~UwU~
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>

#define MAXN 100001

int n;

bool closed[MAXN];
long long v[MAXN];
int cif[100];

int sp[100];

std::string s;

bool comp(char a, char b){
  return a>b;
}

__int128 pw(__int128 b, __int128 e){
  __int128 p = 1;
  while(e>0){
    if(e%2) p = p*b;
    b = b*b;
    e/=2;
  }
  return p;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("cifre.in", "r");
  fscanf(fin, "%d\n", &n);
  for(int i=0; i<n; i++){
    char c = fgetc(fin);
    int j = 0;
    while(c!='\n'){
      s.push_back(c);
      j++;
      c = fgetc(fin);
    }
    cif[j]++;
  }
  fclose(fin);

  std::sort(s.begin(), s.end(), comp);
  
  int usableFirstDigits = 0;
  for(int i=0; s[i]>'0' && i<s.size(); i++) usableFirstDigits++;
  for(int i=1; i<20; i++) sp[i] = sp[i-1]+cif[i];

  long long sum = 0;
  int i = 0;
  for(int j = 12; j>0; j--){
    int y = 0;
    while(cif[j]>0 && i<s.size()){
      while(closed[y]) y++;
      while(cif[j]<sp[j]-sp[j-1])sp[j]--;
      if(j>1 && sp[j]-sp[j-1]<cif[j] && sp[j]-sp[1]>=usableFirstDigits-i){
        s.pop_back();
        closed[y++] = true;
        cif[j]--;
        continue;
      } 
      long long add = (s[i++]-'0')*pw(10, j-1);
      v[y++] +=add;
      sum += add;
      cif[j]--;
      cif[j-1]++;
    }
  } 

  fout = fopen("cifre.out", "w");
  fprintf(fout, "%lld\n", sum);
  for(int i=0; i<n; i++)
    fprintf(fout, "%lld\n", v[i]);
  fclose(fout);
}
