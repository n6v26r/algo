#include <stdio.h>
#include <stdlib.h>
FILE *fin;
FILE *fout;
int cer,n,s,r,p,i,nx;
int pp[26],sum[100],nr[100];
char cod[421],car;
void afiseaza(int sum[100])
{
    int i;
    for(i=sum[0];i>=1;i--)
        fprintf(fout,"%d",sum[i]);
    fprintf(fout,"%c",'\n');
}
void aduna(int sum[],int nr[])
{
    int a[100],i,t=0,x;
    if(sum[0]>nr[0])
    {
        a[0]=sum[0];
        for(i=nr[0]+1;i<=a[0];i++)nr[i]=0;
    }
    else
    {
        a[0]=nr[0];
        for(i=sum[0]+1;i<=a[0];i++)sum[i]=0;
    }
    for(i=1;i<=a[0];i++)
    {
        x=sum[i]+nr[i]+t;
        a[i]=x%10;t=x/10;
    }
    if(t)a[0]++,a[a[0]]=t;
    for(i=0;i<=a[0];i++)
        sum[i]=a[i];
}
void produs(long long x,int b,int prod[100])
{
    int i,t=0;
    prod[0]=0;
    while(x)
    {
        prod[0]++;
        prod[prod[0]]=x%10;
        x=x/10;
    }
    for(i=1;i<=prod[0];i++)
    {
        x=prod[i]*b+t;
        t=x/10;
        prod[i]=x%10;
    }
    while(t)
    {
        prod[0]++;
        prod[prod[0]]=t%10;
        t=t/10;
    }
}
void decodifica(char c[421],int nr[100])
{
    int i,prod[100],x;
    long long k;
    nr[0]=1;
    nr[1]=0;
    k=0;
    for(i=0; c[i]; i++)
    {
        if(c[i]>='0'&&c[i]<='9')k=k*10+(c[i]-'0');
        else
        {
            if(k)
            {
                produs(k,pp[c[i]-'a'],prod);
                aduna(nr,prod);
                k=0;
            }
            else
            {
                prod[0]=0;
                x=pp[c[i]-'a'];
                while(x)
                {
                    prod[0]++;
                    prod[prod[0]]=x%10;
                    x=x/10;
                }
                aduna(nr,prod);
                k=0;
            }
        }
    }

}
int main()
{
    fin=fopen("stele.in","r");
    fout=fopen("stele.out","w");
    fscanf(fin,"%d",&cer);
    if(cer==1)
    {
        fscanf(fin,"%d",&s);
        p=1;
        while(s!=0)
        {
            r=s%2;
            if(r)
            {
               car=(char)('a'+nx);
               fprintf(fout,"%c",car);
            }
            nx++;
            s=s/2;
        }
    }
    else
    {
        pp[0]=1;
        for(i=1; i<26; i++)pp[i]=pp[i-1]*2;
        fscanf(fin,"%d",&n);
        for(i=1; i<=n; i++)
        {
            fscanf(fin,"%s",cod);
            decodifica(cod, nr);
            //afiseaza(nr);
            aduna(sum,nr);
        }
        afiseaza(sum);

    }
    return 0;
}


