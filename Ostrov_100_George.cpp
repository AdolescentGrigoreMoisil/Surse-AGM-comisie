/**
George Chichirim
"Mireca cel Batran" National College, Constanta
**/
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
 
using namespace std;
 
const int MaxN=100010,inf=1e9;
struct operatie
{
    int tip,x,y,s;
};
vector<operatie> op;
struct componenta
{
    map<int,int> poz;
    vector<vector<int> > d;
    componenta(){}
};
vector<componenta> comp;
vector<int> v[MaxN],g[2*MaxN];
vector<pair<int,int> > q;
map<pair<int,int>,int> cost,cecomp;
int niv[2*MaxN],nivmin[MaxN];
int first[2*MaxN],last[2*MaxN],tata[20][2*MaxN],aib[2*MaxN],nr,lognr,n;
int rad[MaxN],height[MaxN];
char vaz[MaxN],vaz1[2*MaxN];
 
void comp_biconexa(int x,int y)
{
    comp.push_back(componenta());
    int a,b,nr=n+comp.size(),cnt=0;
    do
    {
        a=q.back().first;
        b=q.back().second;
        q.pop_back();
        g[nr].push_back(b);
        g[b].push_back(nr);
        comp.back().poz[b]=cnt++;
    }while(x!=a || y!=b);
    g[nr].push_back(x);
    g[x].push_back(nr);
    comp.back().poz[x]=cnt++;
    comp.back().d.resize(cnt,vector<int>(cnt));
}
 
void dfs(int nod,int tata,int lev)
{
    vaz[nod]=1;
    niv[nod]=nivmin[nod]=lev;
    for(vector<int>::iterator it=v[nod].begin();it!=v[nod].end();it++)
    {
        if(*it==tata) continue;
        if(!vaz[*it])
        {
            q.push_back({nod,*it});
            dfs(*it,nod,lev+1);
            nivmin[nod]=min(nivmin[nod],nivmin[*it]);
            if(nivmin[*it]>=niv[nod]) comp_biconexa(nod,*it);
        }
        else nivmin[nod]=min(nivmin[nod],niv[*it]);
    }
}
 
void dfs1(int nod,int dad,int lev)
{
    vaz1[nod]=1;
    tata[0][nod]=dad;
    for(int i=1;i<=lognr;i++) tata[i][nod]=tata[i-1][tata[i-1][nod]];
    niv[nod]=lev;
    first[nod]=++nr;
    for(vector<int>::iterator it=g[nod].begin();it!=g[nod].end();it++)
        if(*it!=dad) dfs1(*it,nod,lev+1);
    last[nod]=nr;
}
 
void roy_floyd(vector<vector<int> > &d)
{
    for(int k=0;k<d.size();k++)
        for(int i=0;i<d.size();i++)
            for(int j=0;j<d.size();j++)
                if(i!=j) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
 
void aib_update(int i,int s)
{
    for(;i<=nr;i+=i&(-i)) aib[i]+=s;
}
 
int aib_query(int i)
{
    int s=0;
    for(;i>=1;i-=i&(-i)) s+=aib[i];
    return s;
}
 
int radacina(int x)
{
    int y=x;
    for(;x!=rad[x];x=rad[x]);
    while(y!=x)
    {
        int aux=rad[y];
        rad[y]=x;
        y=aux;
    }
    return x;
}
 
void precalc()
{
    for(int i=0;i<comp.size();i++)
    {
        for(map<int,int>::iterator it1=comp[i].poz.begin();it1!=comp[i].poz.end();it1++)
            for(map<int,int>::iterator it2=comp[i].poz.begin();it2!=comp[i].poz.end();it2++)
            {
                if(!cost.count({it1->first,it2->first})) comp[i].d[it1->second][it2->second]=inf;
                else comp[i].d[it1->second][it2->second]=cost[{it1->first,it2->first}];
                cecomp[{it1->first,it2->first}]=i;
            }
        roy_floyd(comp[i].d);
    }
    for(int i=1;i<=n;i++)
        if(tata[0][i]!=0)
        {
            int c=tata[0][i]-n-1;
            int a=comp[c].poz[i];
            int b=comp[c].poz[tata[0][tata[0][i]]];
            int s=comp[c].d[a][b];
            aib_update(first[i],s);
            aib_update(last[i]+1,-s);
        }
}
 
void update_edge(int x,int y,int s)
{
    int c=cecomp[{x,y}];
    int t=tata[0][n+c+1],poz=comp[c].poz[t];
    vector<int> old_cost=vector<int>(comp[c].d.size());
    for(map<int,int>::iterator it=comp[c].poz.begin();it!=comp[c].poz.end();it++)
        if(it->first!=t) old_cost[it->second]=comp[c].d[it->second][poz];
    int a=comp[c].poz[x],b=comp[c].poz[y];
    cost[{x,y}]=cost[{y,x}]=s;
    for(map<int,int>::iterator it1=comp[c].poz.begin();it1!=comp[c].poz.end();it1++)
        for(map<int,int>::iterator it2=comp[c].poz.begin();it2!=comp[c].poz.end();it2++)
        {
            if(!cost.count({it1->first,it2->first})) comp[c].d[it1->second][it2->second]=inf;
            else comp[c].d[it1->second][it2->second]=cost[{it1->first,it2->first}];
        }
    roy_floyd(comp[c].d);
    for(map<int,int>::iterator it=comp[c].poz.begin();it!=comp[c].poz.end();it++)
        if(it->first!=t)
        {
            aib_update(first[it->first],-old_cost[it->second]);
            aib_update(last[it->first]+1,old_cost[it->second]);
            aib_update(first[it->first],comp[c].d[it->second][poz]);
            aib_update(last[it->first]+1,-comp[c].d[it->second][poz]);
        }
}
 
pair<int,int> lca(int x,int y)
{
    if(niv[x]<niv[y]) swap(x,y);
    for(int i=lognr;i>=0;i--)
        if(niv[tata[i][x]]>=niv[y]) x=tata[i][x];
    for(int i=lognr;i>=0;i--)
        if(tata[i][x]!=tata[i][y]) {x=tata[i][x];y=tata[i][y];}
    return {x,y};
}
 
void uneste(int x,int y)
{
    x=radacina(x);
    y=radacina(y);
    if(x!=y)
    {
        if(height[x]<height[y]) swap(x,y);
        rad[y]=x;
        if(height[x]==height[y]) height[x]++;
    }
}
 
class InParser {
private:
    FILE *fin;
    char *buff;
    int sp;
 
    char read_ch() {
        ++sp;
        if (sp == 4096) {
            sp = 0;
            fread(buff, 1, 4096, fin);
        }
        return buff[sp];
    }
 
public:
    InParser(const char* nume) {
        fin = fopen(nume, "r");
        buff = new char[4096]();
        sp = 4095;
    }
 
    InParser& operator >> (int &n) {
        char c;
        while (!isdigit(c = read_ch()) && c != '-');
        int sgn = 1;
        if (c == '-') {
            n = 0;
            sgn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = read_ch())) {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }
 
    InParser& operator >> (long long &n) {
        char c;
        n = 0;
        while (!isdigit(c = read_ch()) && c != '-');
        long long sgn = 1;
        if (c == '-') {
            n = 0;
            sgn = -1;
        } else {
            n = c - '0';
        }
        while (isdigit(c = read_ch())) {
            n = 10 * n + c - '0';
        }
        n *= sgn;
        return *this;
    }
};
 
int main()
{
    InParser fin("ostrov.in");
    freopen("ostrov.out", "w", stdout);
    int q,nrop3=0,nrop4=0,nrmuc=0;
    for(fin>>q;q;q--)
    {
        int tip,x,y,nr,m,s;
        fin>>tip;
        if(tip==0) {n++;rad[n]=n;height[n]=1;}
        else if(tip==1)
        {
            int X;
            fin>>X>>nr>>m;
            assert(nr<=10);
            for(int i=n+1;i<=n+nr;i++) {rad[i]=i;height[i]=1;}
            n+=nr;
            for(int i=1;i<=m;i++)
            {
                fin>>x>>y>>s;
                assert((n-nr+1<=x && x<=n) || x==X);
                assert((n-nr+1<=y && y<=n) || y==X);
                assert(1<=s && s<=1000);
                cost[{x,y}]=cost[{y,x}]=s;
                v[x].push_back(y);
                v[y].push_back(x);
                uneste(x,y);
                nrmuc++;
            }
        }
        else if(tip==2)
        {
            fin>>x>>y>>s;
            assert(1<=x && x<=n);
            assert(1<=y && y<=n);
            assert(1<=s && s<=1000);
            cost[{x,y}]=cost[{y,x}]=s;
            v[x].push_back(y);
            v[y].push_back(x);
            op.push_back({tip,x,y});
            nrmuc++;
        }
        else if(tip==3)
        {
            fin>>x>>y>>s;
            assert(1<=x && x<=n);
            assert(1<=y && y<=n);
            assert(1<=s && s<=1000);
            op.push_back({tip,x,y,s});
            nrop3++;
        }
        else if(tip==4)
        {
            fin>>x>>y;
            assert(1<=x && x<=n);
            assert(1<=y && y<=n);
            op.push_back({tip,x,y});
            nrop4++;
        }
    }
    assert(n<=100000);
    assert(nrmuc<=300000);
    assert(nrop3<=10000);
    assert(nrop4<=300000);
    for(int i=1;i<=n;i++)
        if(!vaz[i]) dfs(i,0,1);
    for(lognr=1;(1<<lognr)<=n+comp.size();lognr++);lognr--;
    for(int i=1;i<=n;i++)
        if(!vaz1[i]) dfs1(i,0,1);
    precalc();
    for(int i=0;i<op.size();i++)
        if(op[i].tip==2) uneste(op[i].x,op[i].y);
        else if(op[i].tip==3) update_edge(op[i].x,op[i].y,op[i].s);
        else if(op[i].tip==4)
        {
            int a=radacina(op[i].x),b=radacina(op[i].y);
            if(a!=b) printf("-1\n");
            else
            {
                pair<int,int> ret=lca(op[i].x,op[i].y);
                if(ret.first==ret.second || ret.first>n)
                {
                    int nod;
                    if(ret.first==ret.second) nod=ret.first;
                    else nod=tata[0][ret.first];
                    printf("%d\n",aib_query(first[op[i].x])+aib_query(first[op[i].y])-2*aib_query(first[nod]));
                }
                else
                {
                    int nod=tata[0][ret.first],c=nod-n-1;
                    int a=comp[c].poz[ret.first],b=comp[c].poz[ret.second],t=comp[c].poz[tata[0][nod]];
                    printf("%d\n",aib_query(first[op[i].x])+aib_query(first[op[i].y])-2*aib_query(first[nod])-comp[c].d[a][t]-comp[c].d[b][t]+comp[c].d[a][b]);
                }
            }
        }
    return 0;
}