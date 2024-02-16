#include <fstream>

using namespace std;
ifstream fin("stele.in");
ofstream fout("stele.out");
int cerinta;
long long int s;
long long int p[30];
char rez[30];
char sir[1000];
int sum[100], lgs;
int rezultat[100], lgr;
int prod[100], lgprod;
void decodifica();
void produs (long long int a, long long int b, int c[], int& lgc);
void suma(int a[], int lga, int b[], int lgb, int s[], int &lgs);
int main()
{int i, j, nr;
 for (i=p[0]=1; i<26; i++) p[i]=2*p[i-1];
 fin>>cerinta;
 if (cerinta==1)
    {
      fin>>s;
      for (i=25, j=0; s; i--)
          if (p[i]<=s) {rez[j++]=i+'a'; s-=p[i];}
      for (i=j-1; i>=0; i--) fout<<rez[i];
    }
    else
    {
      fin>>nr;
      for (i=0; i<nr; i++)
           {fin>>sir;
            decodifica();
            suma(sum,lgs,rezultat,lgr, sum, lgs);}
      for (i=lgs-1; i>=0; i--) fout<<sum[i];
    }
    fout<<'\n';
    fout.close();
    return 0;
}

void decodifica()
{int i;
 long long int nr;
 rezultat[0]=0; lgr=1;
 for (i=0; sir[i]; i++)
      {if (sir[i]>='a' && sir[i]<='z') nr=1;
           else
           for (nr=0; sir[i]>='0' && sir[i]<='9'; i++) nr=nr*10+sir[i]-'0';
       produs (nr, p[sir[i]-'a'], prod, lgprod);
       suma(rezultat,lgr,prod,lgprod,rezultat,lgr);
      }
}

void suma(int a[], int lga, int b[], int lgb, int s[], int &lgs)
{int i, t, val;
  if (lga<lgb) {for (i=lga; i<lgb; i++) a[i]=0; lgs=lgb;}
      else   {for (i=lgb; i<lgs; i++) b[i]=0; lgs=lga;}
  for (i=t=0; i<lgs; i++)
      {
       val=a[i]+b[i]+t;
       s[i]=val%10;
       t=val/10;
      }
  if (t) s[lgs++]=t;
}

void produs (long long int a, long long int b, int c[], int& lgc)
{
  int sa[100], lga, i;
  long long int t, val;
  if (!a || !b) {lgc=1; c[0]=0; return;}
  for (lga=0; a; lga++) {sa[lga]=a%10; a/=10;}
  for (t=i=0; i<lga; i++)
      {
       val=sa[i]*b+t;
       c[i]=val%10;
       t=val/10;
      }
   lgc=lga;
   while (t) {c[lgc++]=t%10; t/=10;}
}

