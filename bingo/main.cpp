#include <iostream>
#include <queue>

#define MAXN 55
#define MAXM 99

#define MAXS 6

using namespace std;

int n, m;
pair<int, int> f[MAXN][MAXM];
bool mat[MAXN][MAXS][MAXS];
string name[MAXN];

queue<int> ans;

int main(){
  //freopen("file.in", "r", stdin);
  //freopen("file.out", "w", stdout);
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    cin>>name[i];
    for(int l=0; l<5; l++){
      for(int c=0; c<5; c++){
        int val; scanf("%d", &val);
        f[i][val] = make_pair(l+1, c+1);
      }
    }
  }
  scanf("%d", &m);
  for(int i=0; i<m; i++){
    int val; scanf("%d", &val);
    for(int i=0; i<n; i++){
      if(f[i][val].first>0 && f[i][val].second>0)
      mat[i][f[i][val].first-1][f[i][val].second-1] = true;
    }
  }

  int total = 0;
  for(int i=0; i<n; i++){
    int l;
    for(l=0; l<5; l++){
      int col = 0; while(col<5 && mat[i][l][col]) col++;
      if(col == 5){ total++, ans.push(i); break;}
    }
    if(l<5) continue;

    int c;
    for(c=0; c<5; c++){
      int lin = 0; while(lin<5 && mat[i][lin][c]) lin++;
      if(lin == 5){ total++, ans.push(i); break;}
    }
    if(c<5) continue;
    c = l = 0;
    while(c<5 && l<5 && mat[i][l][c]) {l++; c++;}
    if(c>=5 && l>=5){total++; ans.push(i); continue;}


    c = 0; l = 4;
    while(c<5 && l>=0 && mat[i][l][c]) {l--; c++;}
    if(c>=5 && l<0) {total++, ans.push(i);}

  }

  printf("%d\n", total);
  while(!ans.empty()){
    cout<<name[ans.front()]<<endl;
    ans.pop();
  }
  /*for(int i=0; i<n; i++){
    for(int l=0; l<5;l++){
      for(int c=0; c<5; c++){
        printf("%d", mat[i][l][c]);
      }printf("\n");
    }printf("\n");
  }*/
  return 0;
}
