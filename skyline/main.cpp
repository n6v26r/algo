#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> buildings;
multiset<int> st;

typedef struct{int x; int h;}point;

bool cmp(point a, point b){
  return a.x<b.x;
}

int main(){
  int n;
  FILE *fin, *fout;
  fin = fopen("skyline.in" ,"r");
  fscanf(fin, "%d", &n);
  for(int i=0; i<n; i++){
    int x, y, z;
    fscanf(fin, "%d %d %d", &x, &y, &z);
    buildings.push_back({x, y, z});
  }
  fclose(fin);

  point v[2*buildings.size()+1];

  for(int i=0; i<buildings.size(); i++){
    v[2*i] = {buildings[i][0], buildings[i][2]};
    v[2*i+1] = {buildings[i][1], -buildings[i][2]};
  }

  sort(v, v+2*buildings.size(), cmp);

  int last;
  vector<vector<int>> mesh;
  for(int i=0; i<2*buildings.size(); i++){
    do{
      if(v[i].h<0){
        st.erase(st.find(-v[i].h));
        printf("R%d\n", -v[i].h);
      }
      else
        st.insert(v[i].h),printf("A%d\n", v[i].h);
    }while(v[i].x==v[++i].x);
    i--;
    printf("%d. %d\n", i, (st.size()>0?*st.rbegin():0)); fflush(stdout);

    if(st.size()>0 && last!=*st.rbegin()){
      printf("  %d %d\n", v[i].x, *st.rbegin());
      mesh.push_back({v[i].x, *st.rbegin()});
    }
    else if(st.size()==0){
      printf("  %d %d\n", v[i].x, 0);
      mesh.push_back({v[i].x, 0});
    }
    last = (st.size()>0?*st.rbegin():0);
  }

  fout = fopen("skyline.out", "w");
  fclose(fout);
  return 0;
}
