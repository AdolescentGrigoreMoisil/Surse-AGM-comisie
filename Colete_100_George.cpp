/**
George Chichirim
"Mircea cel Batran" National College, Constanta
**/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>
 
using namespace std;
 
const long long inf=1e18;
const int MaxN=50010;
struct drona
{
    int x,y,v,h,d,poz;
    bool operator <(const drona &aux) const
    {
        return y<aux.y;
    }
}v[MaxN];
vector<int> norm;
struct convex_hull
{
    struct dreapta1
    {
        long long a,b;
        double x;
        bool operator <(const dreapta1 &aux) const
        {
            if(a==aux.a) return b<aux.b;
            else return a>aux.a;
        }
    };
    struct dreapta2
    {
        long long a,b;
        double x;
        bool operator <(const dreapta2 &aux) const
        {
            return x<aux.x;
        }
    };
    set<dreapta1> v1;
    set<dreapta2> v2;
 
    void insert(long long a,long long b)
    {
        dreapta1 d1={a,b};
        dreapta2 d2;
        set<dreapta1>::iterator it1,it2;
        if(v1.count(d1)) return;
        it1=v1.lower_bound(d1);
        if(it1!=v1.begin() && it1!=v1.end())
        {
            it2=it1;
            it1--;
            if(inters(it1->a,it1->b,a,b)>inters(a,b,it2->a,it2->b)) return;
        }
        while(1)
        {
            d1={a,b};
            it2=v1.lower_bound(d1);
            if(it2==v1.begin()) break;
            it2--;
            if(it2==v1.begin()) break;
            it1=it2;
            it1--;
            if(inters(it1->a,it1->b,a,b)>inters(it2->a,it2->b,a,b))
            {
                d1={it2->a,it2->b,it2->x};
                d2={it2->a,it2->b,it2->x};
                v1.erase(d1);
                v2.erase(d2);
            }
            else break;
        }
        while(1)
        {
            d1={a,b};
            it1=v1.lower_bound(d1);
            if(it1==v1.end()) break;
            it2=it1;
            it2++;
            if(it2==v1.end()) break;
            if(inters(a,b,it1->a,it1->b)>inters(a,b,it2->a,it2->b))
            {
                d1={it1->a,it1->b,it1->x};
                d2={it1->a,it1->b,it1->x};
                v1.erase(d1);
                v2.erase(d2);
            }
            else break;
        }
        d1={a,b};
        d2={a,b};
        it1=v1.lower_bound(d1);
        if(it1==v1.begin()) d1.x=d2.x=-inf;
        else
        {
            it1--;
            d1.x=d2.x=inters(it1->a,it1->b,a,b);
            it1++;
        }
        if(it1!=v1.end())
        {
            long long a1=it1->a,b1=it1->b;
            double x=inters(a,b,a1,b1);
            dreapta1 dd1={it1->a,it1->b,it1->x};
            dreapta2 dd2={it1->a,it1->b,it1->x};
            v1.erase(dd1);
            v2.erase(dd2);
            dd1={a1,b1,x};
            v1.insert(dd1);
            dd2={a1,b1,x};
            v2.insert(dd2);
        }
        v1.insert(d1);
        v2.insert(d2);
    }
 
    pair<long long,long long> query(double x)
    {
        set<dreapta2>::iterator it=v2.lower_bound({0,0,x});
        it--;
        return {it->a,it->b};
    }
 
    int size()
    {
        return v1.size();
    }
 
    double inters(long long a1,long long b1,long long a2,long long b2)
    {
        if(a1==a2) if(b1<b2) return inf;
                   else return -inf;
        else return 1.0*(b1-b2)/(a2-a1);
    }
};
struct arbint
{
    convex_hull v1,v2;
}arb[4*MaxN];
long long din[MaxN];
map<int,int> bagat;
 
void arbint_update(int nod,int st,int dr,int poz,drona p)
{
    arb[nod].v1.insert(-p.x-p.y,din[p.poz]);
    arb[nod].v2.insert(p.x-p.y,din[p.poz]);
    if(st==dr) return;
    int mid=(st+dr)/2;
    if(poz<=mid) arbint_update(nod*2,st,mid,poz,p);
    else arbint_update(nod*2+1,mid+1,dr,poz,p);
}
 
long long arbint_query(int nod,int st,int dr,int left,int right,int tip,drona p)
{
    if(left<=st && dr<=right)
    {
        if(tip==1)
        {
            if(arb[nod].v1.size()==0) return inf;
            pair<long long,long long> ret=arb[nod].v1.query(p.v);
            return 1LL*ret.first*p.v+ret.second+1LL*p.v*(p.x+p.y+2*p.h);
        }
        else
        {
            if(arb[nod].v2.size()==0) return inf;
            pair<long long,long long> ret=arb[nod].v2.query(p.v);
            return 1LL*ret.first*p.v+ret.second+1LL*p.v*(-p.x+p.y+2*p.h);
        }
    }
    else
    {
        int mid=(st+dr)/2;
        long long ret=inf;
        if(left<=mid) ret=min(ret,arbint_query(nod*2,st,mid,left,right,tip,p));
        if(mid<right) ret=min(ret,arbint_query(nod*2+1,mid+1,dr,left,right,tip,p));
        return ret;
    }
}
 
int main()
{
    freopen("colete.in", "r", stdin);
    freopen("colete.out", "w", stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d%d",&v[i].x,&v[i].y,&v[i].v,&v[i].h,&v[i].d);
        assert(1<=v[i].x && v[i].x<=1e8);
        assert(1<=v[i].y && v[i].y<=1e8);
        assert(1<=v[i].v && v[i].v<=1e8);
        assert(1<=v[i].h && v[i].h<=1e8);
        assert(1<=v[i].d && v[i].d<=1e8);
        assert(bagat[v[i].y]==0);
        bagat[v[i].y]=1;
        v[i].poz=i;
        norm.push_back(v[i].x);
    }
    sort(norm.begin(),norm.end());
    sort(v+1,v+1+n);
    for(int i=1;i<=n;i++)
    {
        int poz=lower_bound(norm.begin(),norm.end(),v[i].x)-norm.begin()+1;
        int left=lower_bound(norm.begin(),norm.end(),v[i].x-v[i].d)-norm.begin()+1;
        int right=upper_bound(norm.begin(),norm.end(),v[i].x+v[i].d)-norm.begin();
        din[v[i].poz]=1LL*v[i].v*(v[i].y+2*v[i].h);
        din[v[i].poz]=min(din[v[i].poz],arbint_query(1,1,n,left,poz,1,v[i]));
        din[v[i].poz]=min(din[v[i].poz],arbint_query(1,1,n,poz,right,2,v[i]));
        arbint_update(1,1,n,poz,v[i]);
    }
    for(int i=1;i<=n;i++) printf("%lld\n",din[i]);
    return 0;
}