#include <stdio.h>
#include <string.h>

#define MAXN 140

int n, m, t;
char mat[MAXN][MAXN];

int main(){
  FILE *fin, *fout;
  fin = fopen("raze.in", "r");
  fout = fopen("raze.out", "w");
  fscanf(fin, "%d", &t);
  while(t){
    fscanf(fin, "%d %d", &n, &m);
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        fscanf(fin, "%d", &mat[i][j]);
        if(mat[i][j] == 1){
          mat[i][j] = -1;
        }
      }    
    }
    for(int i=0; i<n; i++){
      int l = i;
      int c = 0;
      while(mat[l][c]>=0 && l<n && c<m){
        mat[l][c]++;
        l++;
        c++;
      }
    }
    for(int i=1; i<m; i++){
      int l = 0;
      int c = i;
      while(mat[l][c]>=0 && l<n && c<m){
        mat[l][c]++;
        l++;
        c++;
      }
    }
    for(int i=0; i<n; i++){
      int l = i;
      int c = m-1;
      while(mat[l][c]>=0 && l>=0 && c>=0){
        mat[l][c]++;
        l--;
        c--;
      }
    }
    for(int i=0; i<m-1; i++){
      int l = n-1;
      int c = i;
      while(mat[l][c]>=0 && l>=0 && c>=0){
        mat[l][c]++;
        l--;
        c--;
      }
    }

    for(int i=0; i<n; i++){
      int l = i;
      int c = m-1;
      while(mat[l][c]>=0 && l<n && c>=0){
        mat[l][c]++;
        l++;
        c--;
      }
    }
    for(int i=0; i<m-1; i++){
      int l = 0;
      int c = i;
      while(mat[l][c]>=0 && l<n && c>=0){
        mat[l][c]++;
        l++;
        c--;
      }
    }
    for(int i=0; i<n-1; i++){
      int l = i;
      int c = 0;
      while(mat[l][c]>=0 && l>=0 && c<m){
        mat[l][c]++;
        l--;
        c++;
      }
    }
    for(int i=0; i<m; i++){
      int l = n-1;
      int c = i;
      while(mat[l][c]>=0 && l>=0 && c<m){
        mat[l][c]++;
        l--;
        c++;
      }
    }
    int max = 0;
    int maxp = 0;
    for(int i=1; i<n-1; i++){
      for(int j=1; j<m-1; j++){
        if(mat[i][j]>max) max = mat[i][j], maxp = 1;
        else if(mat[i][j]==max) maxp++;
      }
    }
    fprintf(fout, "%d %d\n", max, maxp);
    t--;
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
