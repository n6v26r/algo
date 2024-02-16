#include <cstdio>
#include <set>

std::set<long long> v;
int n, m;

int p[169];

int main(){
  FILE *fin, *fout;
  fin = fopen("numar.in", "r");
  fscanf(fin, "%d%d", &n, &m);
  for(int i=0; i<n; i++)
    fscanf(fin, "%d", &p[i]), v.insert(p[i]);
  fclose(fin);

  int solution=-69420;
  while(m>0){
    solution = *v.begin();
    v.erase(solution);
    m--;
    for(int i=0; i<n; i++)
      v.insert((long long)solution*p[i]);
  }
  fout = fopen("numar.out", "w");
  fprintf(fout, "%d\n", solution);
  fclose(fout);
  return 0;
}
