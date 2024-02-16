#include <stdio.h>
#include <stdlib.h>
int mat[101][101];
int main()
{
  int n, i;
    FILE *fin, *fout;
    fin=fopen("sume1.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);
    int lin=0;
    int col;
    for(i=1; i<=n*n; i+=n){
      int val=i;
      for(col=lin; mat[lin][col]==0; col=(col+1)%n){
        mat[lin][col]=val;
        val=(val+n)%(n*n)+1;
      }
      lin++;
    }
 
    fout=fopen("sume1.out", "w");
    for(lin=0; lin<n; lin++){
      for(col=0; col<n; col++){
        fprintf(fout, "%d ", mat[lin][col]);
      }
      fprintf(fout, "\n");
    }
    fclose(fout);
    return 0;
}
