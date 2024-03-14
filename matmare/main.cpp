// this crappy piece of code is provided to u 
// by razv
// PreOJI 2025 8th grade
// https://kilonova.ro/problems/2418

/*
F. bruta: (~~20 pct) calculam valorile intr o matrice, si facem suma pt fiecare submatrice
F. bruta fumoasa: (~~40 pct) acelasi lucru + sume partiale pe matrice

Pentru alte 40 pct, toate valorile sunt binare. (Analizand cazul asta, se deduce si solutia pt toata pb.)
Daca avem o intrebare de tipul: l c i j,
Fie n = (i-l+1) si m = (j-c+1) (dimensiunile submatricei)

Submatricea va fi compusa din produsul multimilor
{a[l], a[l+1], ... a[i]} x {b[c], b[c+1], .. b[j]}

Pentru op de sau binar:
0|0 = 0
0|1 = 1|0 = 1
1|1 = 1

Deci suma submatricei va fi: (a[l]|b[c] + a[l]|b[c+1] + ... a[l]|b[j] ) + (a[l+1]b[c] + ... + a[l+1]|b[j]) + ...

Asadar, in prima paranteza, daca a[l] = 1, toate operatiile vor egala 1, iar daca a[i] = 0, toate op vor egala b[c]+b[c+1]+...b[j];
Deci, daca k din cele n elemente ale lui a sunt 1 (n-k elemente sunt 0) si h dintre cele m elemente ale lui b sunt 1, 
suma intregii submatrici va fi: (k*m)+((n-k)*h)

Pentru exemplu, daca avem:
a: 0 0 1 1 0 1
b: 1 1 0 1 1 0

Si submatricea (l=1, i=4, c=2, j=5) (asumand indexare de la 1, ca si in enunt) va fi 
{0, 0, 1, 1} x {1, 0, 1, 1}

k = 2
h = 3
m = n = 4

Suma submatricei va fi: (2*4)+(2*3) = 14

Pentru cazul 4, cand nr<=2^26, putem considera acelasi rationament pentru fiecare bit al fiecarui nr.
astfel, sparA[MAXN][27] va tine suma partiala a bitilor de pe o anumita pozitie in toate nr lui a.
analog sparB[MAXN][27]

pentru a generaliza ideea, vom aplica aceeasi formula, folosind sumele partiale pentru a cauta k si h: 
((i-l+1)-(spara[i][bit]-spara[l-1][bit]))*(sparb[j][bit]-sparb[c-1][bit])+(spara[i][bit]-spara[l-1][bit])*((j-c+1))

Pentru fiecare bit, si vom inmulti formula cu 2^(ordinul bitului) pentru a compune rasp

E putin mai usor de inteles daca pui pe hartie si iti iei exemple.

Complexitate: O(q*26), ma rog, O(q) dar constanta e mare
*/

#include <stdio.h>

#define MAXN 200001
#define MAXBITS 27

int n, m, q;

int spara[MAXN][MAXBITS+1];
int sparb[MAXN][MAXBITS+1];

void swp(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

int main(){
  FILE *fin, *fout;
  fin = fopen("matmare.in", "r");
  fscanf(fin, "%d%d%d", &n, &m, &q);
  for(int i=0; i<n; i++){
    int val; fscanf(fin, "%d", &val);
    int pow = MAXBITS-1;
    while(pow>=0){
      spara[i][pow] = (i>0?spara[i-1][pow]:0) + val/(1<<pow);
      val = val % (1<<pow);
      pow--;
    }
  }
  for(int i=0; i<m; i++){
    int val; fscanf(fin, "%d", &val);
    int pow = MAXBITS-1;
    while(pow>=0){
      sparb[i][pow] = (i>0?sparb[i-1][pow]:0) + val/(1<<pow);
      val = val % (1<<pow);
      pow--;
    }
  }

  fout = fopen("matmare.out", "w");
  while(q>0){
    int l, c, i, j;
    fscanf(fin, "%d%d%d%d", &l, &c, &i, &j); l--; c--; i--; j--;
    if(i<l) swp(&i, &l);
    if(j<c) swp(&c, &j);
    unsigned long long val = 0;
    for(int bit=0; bit<MAXBITS; bit++){
      val +=  ((unsigned long long) ((i-l+1)-((unsigned long long)spara[i][bit]-(l>0?spara[l-1][bit]:0)))*(sparb[j][bit]-(c>0?sparb[c-1][bit]:0))+
              ((spara[i][bit]-(l>0?spara[l-1][bit]:0)))*((unsigned long long)(j-c+1)) ) * (unsigned long long)(1<<bit);
    }
    fprintf(fout, "%llu\n", val);
    q--;
  }

  fclose(fout);
  fclose(fin);
  return 0;
}
