#include <stdio.h>

#define MAXVAL 1000002

int r, g, b, p;

int aibr[2*MAXVAL];
int aibg[2*MAXVAL];
int aibb[2*MAXVAL];

int vr[MAXVAL];
int vg[MAXVAL];
int vb[MAXVAL];

int rr[MAXVAL];
int rg[MAXVAL];
int rb[MAXVAL];

void update(int i, int val, int* aib){
  while(i<=2*MAXVAL){
    aib[i] += val;
    i+=i&-i;
  }
}

int get(int i, int*aib){
  int sum = 0;
  while(i>0){
    sum+=aib[i];
    i-=i&-i;
  }
  return sum;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("rgb.in", "r");
  fscanf(fin, "%d%d%d%d", &p, &r, &g, &b);
  int val;
  for(int i=0; i<r; i++){
    fscanf(fin, "%d", &val); vr[i] = val;
    update(val, 1, aibr);
  }
  for(int i=0; i<g; i++){
    fscanf(fin, "%d", &val); vg[i] = val;
    update(val, 1, aibg);
  }
  for(int i=0; i<b; i++){
    fscanf(fin, "%d", &val); vb[i] = val;
    update(val, 1, aibb);
  }
  fclose(fin);

  int maxwins = 0;
  int bestpower = 0;
  for(int i=0; i<r; i++){
    int wins = get(vr[i]*2, aibg)+get(vr[i]/2, aibb)+get(vr[i]-1, aibr);
    rr[i] = wins;
    if(wins>maxwins){
      maxwins = wins;
      bestpower = vr[i];
    }
    else if(wins==maxwins && vr[i]<bestpower){
      bestpower = vr[i];
    }
  }

  for(int i=0; i<g; i++){
    int wins = get(vg[i]*2, aibb)+get(vg[i]/2, aibr)+get(vg[i]-1, aibg);
    rg[i] = wins;
    if(wins>maxwins){
      maxwins = wins;
      bestpower = vg[i];
    }
    else if(wins==maxwins && vg[i]<bestpower){
      bestpower = vg[i];
    }
  }

  for(int i=0; i<b; i++){
    int wins = get(vb[i]*2, aibr)+get(vb[i]/2, aibg)+get(vb[i]-1, aibb);
    rb[i] = wins;
    if(wins>maxwins){
      maxwins = wins;
      bestpower = vb[i];
    }
    else if(wins==maxwins && vb[i]<bestpower){
      bestpower = vb[i];
    }
  }

  fout = fopen("rgb.out", "w");
  if(p==1)
    fprintf(fout, "%d\n", bestpower);
  else{
    for(int i=0; i<r; i++)
      fprintf(fout, "%d ", rr[i]);
    fprintf(fout, "\n");
    for(int i=0; i<g; i++)
      fprintf(fout, "%d ", rg[i]);
    fprintf(fout, "\n");
    for(int i=0; i<b; i++)
      fprintf(fout, "%d ", rb[i]);
    fprintf(fout, "\n");
  }
  fclose(fout);
  return 0;
}
