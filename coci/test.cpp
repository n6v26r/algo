#include <bits/stdc++.h>
using namespace std;
struct node{
    long long int a, b, dif;
} v[500005];
bool cmp(node a1, node b1){
    return a1.b<b1.b;
}
long long int f[500005];
int main(){
    long long int n, a, b, min1=1e9, sum=0, ras=1e9, salv;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> v[i].a >> v[i].b;
        v[i].dif=v[i].a-v[i].b;
        v[i].poz=i;
    }
    for(int i=n; i>=1; i--) ras=min(ras, v[i].a), f[i]=ras;
    for(int i=1; i<=n; i++){
        sum+=v[i].b;
        min1=min(min1, v[i].dif);
        cout << min(sum+min1, sum-v[i].b+f[i]) << "\n";
    }
    return 0;
}
