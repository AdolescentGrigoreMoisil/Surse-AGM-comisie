/**
George Chichirim
"Mireca cel Batran" National College, Constanta
**/
#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>
 
using namespace std;
 
const int MaxN=10010,nr=8;
const double eps=1e-9;
vector<int> g[MaxN],v1;
vector<double> v[MaxN];
double sol[MaxN];
int pol[20],grad[MaxN];
char vaz[MaxN],gasit[MaxN];
 
double caut_bin()
{
    double st=-10,dr=10;
    for(int i=1;i<=50;i++)
    {
        double mid=(st+dr)/2,s=0,p=1;
        for(int i=0;i<nr;i++)
        {
            s+=p*pol[i];
            p*=mid;
        }
        if(s<0) st=mid;
        else dr=mid;
    }
    return st;
}
 
void solve()
{
    for(;v1.size() && vaz[v1.back()];v1.pop_back());
    if(v1.size()==0) return;
    int nod=v1.back();
    v1.pop_back();
    vaz[nod]=1;
    for(vector<int>::iterator it=g[nod].begin();it!=g[nod].end();it++)
        if(!vaz[*it] && --grad[*it]==5) v1.push_back(*it);
    solve();
    vector<double> aux;
    for(vector<int>::iterator it=g[nod].begin();it!=g[nod].end();it++)
        if(gasit[*it]) aux.push_back(sol[*it]);
    for(int i=0;i<v[nod].size();i++)
    {
        int ok=1;
        for(int j=0;j<aux.size();j++)
            if(abs(v[nod][i]-aux[j])<eps) {ok=0;break;}
        if(ok)
        {
            sol[nod]=v[nod][i];
            break;
        }
    }
    gasit[nod]=1;
}
 
int main()
{
    freopen("worms.in", "r", stdin);
    freopen("worms.out", "w", stdout);
    int n,m,q,x,y,tip,a;
    for(int i=0;i<nr;i++) scanf("%d",&pol[i]);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
        grad[x]++;
        grad[y]++;
    }
    scanf("%d",&q);
    pol[0]++;
    double val=caut_bin();
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&tip,&a);
        if(tip==1)
        {
            pol[2*a]++;
            val=caut_bin();
        }
        else v[a].push_back(val);
    }
    for(int i=1;i<=7;i++) assert(pol[i]<=10);
    assert(pol[0]<=11);
    for(int i=1;i<=n;i++)
        if(grad[i]<=5) v1.push_back(i);
    solve();
    for(int i=1;i<=n;i++) printf("%.10f\n",sol[i]);
    return 0;
}