#include <iostream>
#define MAXN 100000

using namespace std;

int aib[MAXN+2], n;

void update(int i, int val){
  while(i<n){
    aib[i]+=val;
    i+=(i&-i);
  }
}

int get(int i){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=(i&-i);
  }
  return sum;
}

int main(){
  cin>>n;
  for(int i=0; i<n; i++){
    int val;
    cin>>val;
    printf("%d ", get(val-1));
    update(val, 1);
  }
  printf("\n");

  return 0;
}
