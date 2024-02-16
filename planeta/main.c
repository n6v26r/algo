#include <stdio.h>

#define MAXN 31

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

int n, k;

int v[MAXN];
char used[MAXN];

//            [root]
//            /   |                 
//           /    |                
//         [  ]   [  ]
//          /|
//         / |
//        [] []
//
//
void generateTree(int n, int root, int min, int max, int idx){
  printf("Conf: %d %d %d \n", root, min, max);
  if(idx==n){
    for(int i=0; i<n; i++){printf("%d ", v[i]);}printf("\n");
    return;
  }
  for(int i=min+1; i<max; i++){
    if(used[i]) continue;
    v[idx] = i;
    used[i] = 1;
    if(i<root){
      printf("L:[%d]\n", i);
      generateTree(n, i, min, root, idx+1);
    }
    else{
      printf("R:[%d]\n", i);
      generateTree(n, i, root, max, idx+1);
    }

    used[i] = 0;
  }
}

int main(){
  FILE *fin, *fout;
  fin = fopen("planeta.in", "r");
  fscanf(fin, "%d%d", &n, &k);
  fclose(fin);

  for(int i=1; i<=n; i++){
    printf("[%d]\n", i); v[0] = i;
    used[i] = 1;
    generateTree(n, i, 0, n+1, 1);
    used[i] = 0;
    printf("\n\n");
  }

  fout = fopen("planeta.out", "w");
  fclose(fout);
}
