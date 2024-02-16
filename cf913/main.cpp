#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int t, n;

int f[128];

int main(){
  scanf("%d\n", &t);
  while(t>0){
    memset(f, 0, sizeof(f));
    scanf("%d\n", &n);
    int m = 0;
    for(int i=0; i<n; i++){
      char c = fgetc(stdin);
      f[c]++;
    }
    sort(f+'a', f+'z'+1);
    int sum = 0;
    for(int i='a'; i<'z'; i++){
      sum+=f[i];
    }
    if(f['z']>n/2) printf("%d\n", f['z']-sum);
    else printf("%d\n", (sum+f['z'])%2);
    t--;
  }
}
