// ONI 2022 8th grade
// https://kilonova.ro/problems/1598
#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

#define MAXN 1000005
#define MIN(a, b) ((a)<(b)?(a):(b))

int n, p;
int v[MAXN];
int pr[MAXN];
int vf[MAXN]; int vftotal = 0;

int vai[MAXN];
int vv[MAXN];

stack<int> stivaVf;

void swp(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("proeminenta.in", "r");
  fscanf(fin, "%d%d", &p, &n);
  fscanf(fin, "%d", &v[0]);
  int last = v[0];
  int antelast  = -1;
  int varfuri = 0;

  int lowest = __INT_MAX__;

  for(int i=1; i<n; i++){
    fscanf(fin, "%d", &v[i]);
    if(v[i]==last) continue;

    if(v[i]<last && last>antelast){
      vf[vftotal++] = last;
      if(vftotal>1){
        vai[vftotal-1] = lowest;
      }
      varfuri++;
      lowest = v[i];
    }
    lowest = MIN(lowest, v[i]);
    antelast = last;
    last = v[i];
  }
  fclose(fin);

  if(last>antelast) varfuri++;

  memcpy(vv, vai, sizeof(int)*vftotal);
  for(int i=0; i<vftotal; i++){
    while(!stivaVf.empty() && vf[i]>=vf[stivaVf.top()]){
      if(vv[i] > vv[stivaVf.top()])
        vv[i] = vv[stivaVf.top()];
      stivaVf.pop();
    }

    if(!stivaVf.empty() && vf[i]>vv[i])
      pr[i] = vf[i]-vv[i];
    else pr[i] = vf[i];

    stivaVf.push(i);
  }

  while(!stivaVf.empty()) stivaVf.pop();
  int i = 0;
  int j = vftotal-1;
  while(i<j){
    if(i+1<j)
      swp(&vai[i+1], &vai[j]);
    swp(&vf[i], &vf[j]);
    i++;
    j--;
  }
  memcpy(vv, vai, sizeof(int)*vftotal);

  for(int i=0; i<vftotal; i++){
    while(!stivaVf.empty() && vf[i]>=vf[stivaVf.top()]){
      if(vv[i] > vv[stivaVf.top()])
        vv[i] = vv[stivaVf.top()];
      stivaVf.pop();
    }

    if(!stivaVf.empty() && vf[i]>vv[i])
      pr[vftotal-i-1] = MIN(pr[vftotal-i-1], vf[i]-vv[i]);
    else pr[vftotal-i-1] = MIN(pr[vftotal-i-1], vf[i]);

    stivaVf.push(i);
  }

  fout = fopen("proeminenta.out", "w");
  if(p==1) fprintf(fout, "%d\n", varfuri);
  else{
    for(int i=0; i<vftotal; i++){
      fprintf(fout, "%d ", pr[i]);
    }fprintf(fout, "\n");
  }
  fclose(fout);
}
