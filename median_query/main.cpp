#include <bits/stdc++.h>
using namespace std;
ifstream fin("median_query.in");
ofstream fout("median_query.out");
struct Elem
{
    int val,poz;
    bool operator < (const Elem &other) const
    {
        return val < other.val;
    }
};
Elem nnorm[100005];
int rnorm[100005];
int vec[100005], Lbuck;
struct Query
{
    int l,r,orig;
    bool operator < (const Query &other) const
    {
        if(l / Lbuck == other.l / Lbuck)
            return r < other.r;
        return l / Lbuck < other.l / Lbuck;
    }
} queries[100005];
int ans[100005];
int N,Q;
struct AIB
{
    int v[100005];
    void update(int node,int val)
    {
        for(int i=node;i<=N;i+=(i&(-i)))
            v[i]+=val;
    }
    int query(int node)
    {
        int s=0;

        for(int i=node;i>=1;i-=(i&(-i)))
            s+=v[i];
        return s;
    }
    int binary_lifting(int val)
    {
        int step=(1<<17);
        int poz=0;
        while(step)
        {
            if(poz+step<=N&&v[poz+step]<val)
                val-=v[poz+step],poz+=step;
            step/=2;
        }
        return poz+1;
    }
} aib;

void ADD(int poz)
{
    aib.update(vec[poz],1);
}

void DEL(int poz)
{
    aib.update(vec[poz],-1);
}

int main()
{
    fin>>N>>Q;
    Lbuck=sqrt(N);
    for(int i=1;i<=N;++i)
    {
        int x;
        fin>>x;
        nnorm[i].val=x;
        nnorm[i].poz=i;
    }
    sort(nnorm+1,nnorm+N+1);
    for(int i=1;i<=N;++i)
    {
        vec[nnorm[i].poz]=i;
        rnorm[i]=nnorm[i].val;
    }
    for(int i=1;i<=Q;++i)
        {
            fin>>queries[i].l>>queries[i].r;
            queries[i].orig=i;
        }
    sort(queries+1,queries+Q+1);
    int st=1,dr=0;
    for(int i=1;i<=Q;++i)
    {
        int l,r;
        l=queries[i].l;
        r=queries[i].r;
        while(dr<r)
            ++dr,ADD(dr);
        while(st<l)
            DEL(st),++st;
        while(st>l)
            --st,ADD(st);
        while(dr>r)
            DEL(dr),--dr;
        int med=(r-l+2)/2;
        ans[queries[i].orig]=rnorm[aib.binary_lifting(med)];
    }
    for(int i=1;i<=Q;++i)
        fout<<ans[i]<<'\n';
    return 0;
}
