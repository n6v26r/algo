#include <iostream>
#include <string.h>
using namespace std;

int t, n;

bool f[256];

int main(){
  cin>>t;
  while(t>0){
    memset(f, 0, sizeof(f));
    f[0] = true;
    cin>>n;
    int sum = 0;
    for(int i=0; i<n; i++){
      int val;
      cin>>val;
      sum^= val;
      f[sum] = true;
    }
    int _max = 0;
    for(int i=0; i<256; i++){
      if(!f[i]) continue;
      for(int j=0; j<256; j++){
        if(!f[j]) continue;
        if((i^j)>_max) _max = i^j;
      }
    }
    printf("%d\n", _max);
    t--;
  }
  return 0;
}
