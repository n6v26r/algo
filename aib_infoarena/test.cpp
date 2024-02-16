#include <bits/stdc++.h>
using namespace std;
long long int n, val, m;
long long int BIT[100001];
void update(int i, long long int val){
    while(i<=n){
        BIT[i]+=val;
        i+=(i&-i);
    }
}
int presum(int i){
    long long int sum=0;
    while(i>0){
        sum+=BIT[i];
        i-=(i&-i);
    }
    return sum;
}
int main(){
    ifstream cin("aib.in");
    ofstream cout("aib.out");
    long long int a, b, c;
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> val;
        update(i, val);
    }
    for(int i=1; i<=m; i++){
        cin >> a;
        if(a==0){
            cin >> b >> c;
            update(b, c);
        }
        else if(a==1){
            cin >> b >> c;
            cout << presum(c)-presum(b-1) << "\n";
        }
        else{
            cin >> a;
            int st=1, dr=n;
            while(dr-st>1){
                int mid=(st+dr+1)/2;
                if(presum(mid)<=a) st=mid;
                else dr=mid-1;
            }
            if(presum(st)==a) cout << st << "\n";
            else if(presum(dr)==a) cout << dr << "\n";
            else cout << "-1\n";
        }
    }
    return 0;
}
