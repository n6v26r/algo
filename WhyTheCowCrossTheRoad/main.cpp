#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAXN 50000

int v[MAXN*2+1], n;
int aib[MAXN*2+1];
int save[MAXN*2+1];

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=i&(-i);
  }
  return sum;
}

void update(int i, int val){
  while(i<=2*n){
    aib[i]+=val;
    i+=i&(-i);
  }
}

int main(){
    ifstream fin("circlecross.in");
    ofstream fout("circlecross.out");
    fin>>n;
    for(int i=1; i<=2*n; i++){
      fin>>v[i];
    }
    int total = 0;
    for(int i=1; i<=2*n; i++){
      int state = save[v[i]]>0;
      if(!state){
        save[v[i]] = i;
        update(i, 1);
      }
      else{
        update(save[v[i]], -1);
        int intersect = get(i)-get(save[v[i]]);
        total+=intersect;
      }
    }
    fout<<total;
    return 0;
}
