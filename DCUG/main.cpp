//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
#include <string.h>
class Solution {
  public:
    static const int MAXN = 1e5;
    int sef[MAXN+1];
    int sz[MAXN+1];
    int f(int n){
      if(sef[n]==n)
        return n;

      return sef[n] = f(sef[n]);
    }

    bool u(int a, int b){
      int u = f(a);
      int v = f(b);
      if(u==v) return true;
      if(sz[u]<sz[v]){
        sef[u] = v;
        sz[v]+=sz[u];
      }else{
        sef[v] = u;
        sz[u] += sz[v];
      }
      return false;
    }

    bool isCycle(int V, vector<int> adj[]) {
        for(int i=0; i<=V; i++) sef[i] = i, sz[i] = 1;
        for(int i=0; i<V; i++){
            for(int j=0; j<adj[i].size(); j++){
                if(u(adj[i][j], i)){
                    return true;
                }
            }
        }
        return false;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isCycle(V, adj);
        if (ans)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}
// } Driver Code Ends
