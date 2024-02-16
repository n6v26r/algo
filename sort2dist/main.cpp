#include <iostream>
#include <fstream>
#define MAXN 1001

using namespace std;

typedef struct{
  int a;
  int b;
}intP;

string v[MAXN];

intP ans[12501];

int main(){
  int n;
  ifstream fin("sort2dist.in");
  ofstream fout("sort2dist.out");
  fin>>n;
  for(int i=0; i<n; i++){
    fin>>v[i];
  }

  int mv = 0;

  for(int i=n-1; i>0; i--){
    string m = v[0];
    int mpos = 0;
    for(int j=1; j<=i; j++){
      if(v[j].size()>m.size() || (v[j].size()==m.size() && v[j]>m)) {m=v[j]; mpos=j;}
    }

    int dist = i-mpos;
    int p2 = 1; while(p2*2<=dist) p2<<=1;
    while(p2>0){
      if(dist&p2) {
          ans[mv++] = (intP){.a=mpos, .b=mpos+p2};
          v[mpos] = v[mpos+p2];
          v[mpos+p2] = m;
          mpos+=p2;
      }
      dist=dist%p2;
      p2/=2;
    }
  }
  fout<<mv<<endl;
  for(int i=0; i<mv; i++){
    fout<<ans[i].a+1<<" "<<ans[i].b+1<<endl;
  }
  fin.close();
  fout.close();
}
