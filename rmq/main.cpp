#include <iostream>

#define MAXN 100001
#define MAX(a, b) ((a)<(b)?(b):(a))
#define MIN(a, b) ((a)>(b)?(b):(a))


using namespace std;

int st[30][MAXN];
int lg[MAXN];

int n, q;

int main(){
 // freopen("rmq.in", "r", stdin);
 // freopen("rmq.out", "w", stdout);

  for(int i=2; i<=MAXN; i++){
    lg[i] = 1 + lg[i/2];
  }

  scanf("%d", &n);
  for(int i=0; i<n; i++){
    scanf("%d", &st[0][i]);
  }

  for(int i=1; i<=lg[n]; i++){
    for(int j=0; j+(1<<(i-1))<n; j++){
      st[i][j] = MAX( st[i-1][j], st[i-1][j+(1<<(i-1))] );
      //printf("%d ", st[i][j]);
    }//printf("\n");
  }

  int x, y; scanf("%d %d %d", &q, &x, &y);
  long long sum = 0;
  while(q>0){
    int i = MIN(x, y);
    int j = MAX(x, y);
    int len = j-i+1;
    int k = lg[len];
    int m = MAX(st[k][i], st[k][j-(1<<k)+1]);
    sum += m;
    x = (x+7)%(n-1);
    y = (y+11)%(n);
    q--;
  }
  printf("%lld\n", sum);
  return 0;
}
