/**
George Chichirim
"Mireca cel Batran" National College, Constanta
**/
#include <cstdio>
#include <vector>
 
using namespace std;
 
const int MaxN=2010,MaxG=1000;
struct obiect
{
    int p,g;
}v[MaxN];
vector<int> g[MaxN],radacina[MaxN];
vector<vector<int> > din[MaxN];
int size[MaxN];
char elim[MaxN];
 
void dfs1(int nod,int tata)
{
    size[nod]=1;
    for(vector<int>::iterator it=g[nod].begin();it!=g[nod].end();it++)
        if(!elim[*it] && *it!=tata)
        {
            dfs1(*it,nod);
            size[nod]+=size[*it];
        }
}
 
int get_centroid(int nod,int tata,int n)
{
    int maxx=n-size[nod];
    for(vector<int>::iterator it=g[nod].begin();it!=g[nod].end();it++)
        if(!elim[*it] && *it!=tata)
        {
            int a=get_centroid(*it,nod,n);
            if(a) return a;
            maxx=max(maxx,size[*it]);
        }
    if(maxx<=n/2+1) return nod;
    else return 0;
}
 
void dfs2(int nod,int tata,int centre)
{
    radacina[nod].push_back(centre);
    din[nod].push_back(vector<int>(MaxG+10));
    int l=radacina[nod].size()-1;
    for(int i=0;i<=MaxG;i++) din[nod][l][i]=din[tata][l][i];
    for(int i=MaxG;i>=v[nod].g;i--) din[nod][l][i]=max(din[nod][l][i],din[nod][l][i-v[nod].g]+v[nod].p);
    for(vector<int>::iterator it=g[nod].begin();it!=g[nod].end();it++)
        if(!elim[*it] && *it!=tata) dfs2(*it,nod,centre);
}
 
void solve(int nod)
{
    dfs1(nod,0);
    int centre=get_centroid(nod,0,size[nod]);
    radacina[centre].push_back(centre);
    din[centre].push_back(vector<int>(MaxG+10));
    for(vector<int>::iterator it=g[centre].begin();it!=g[centre].end();it++)
        if(!elim[*it]) dfs2(*it,centre,centre);
    elim[centre]=1;
    for(vector<int>::iterator it=g[centre].begin();it!=g[centre].end();it++)
        if(!elim[*it]) solve(*it);
}
 
int main()
{
    freopen("simulare.in", "r", stdin);
    freopen("simulare.out", "w", stdout);
    int n,m,x,y,s;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&v[i].p,&v[i].g);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    solve(1);
    for(int i=1;i<=m;i++)
    {
        int sol=0;
        scanf("%d%d%d",&x,&y,&s);
        if(x==y)
        {
            if(v[x].g<=s) sol=v[x].p;
        }
        else
        {
            int j=0;
            for(;radacina[x][j]==radacina[y][j];j++);j--;
            obiect a=v[radacina[x][j]];
            for(int k=0;k<=s;k++)
            {
                sol=max(sol,din[x][j][k]+din[y][j][s-k]);
                if(k+a.g<=s) sol=max(sol,din[x][j][k]+din[y][j][s-k-a.g]+a.p);
            }
        }
        printf("%d\n",sol);
    }
    return 0;
}