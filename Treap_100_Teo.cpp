/*
TeoIonescu
--- Solutie ?
*/
#include<bits/stdc++.h>
using namespace std;
ifstream in("treap.in");
ofstream out("treap.out");
const int Nmax = 150001;
vector<int> G[Nmax],S[Nmax];
int N,k[Nmax],p[Nmax];
int mn[Nmax],mx[Nmax],ans[Nmax];
void dfsS(int x){ mn[x]=1; for(auto it:G[x]) if(!mn[it]) S[x].push_back(it),dfsS(it); }
void solve(int x){
    mn[x]=mx[x]=k[x];
    ans[x]=(S[x].size()<=2);
    for(auto it:S[x]){
        solve(it);
        mn[x]=min(mn[x],mn[it]);
        mx[x]=max(mx[x],mx[it]);
        ans[x]&=(ans[it] & (p[it]<=p[x]));
    }
    if(S[x].size()==1) ans[x]&=((mx[S[x][0]]<=k[x]) | (k[x]<=mn[S[x][0]]));
    if(S[x].size()==2) ans[x]&=((mx[S[x][0]]<=k[x]) & (k[x]<=mn[S[x][1]])) | ((mx[S[x][1]]<=k[x]) & (k[x]<=mn[S[x][0]]));
}
int main(){
    in>>N;
    for(int i=1;i<N;i++){ int x,y; in>>x>>y; G[x].push_back(y); G[y].push_back(x); }
    dfsS(1); int sm=0; for(int i=1;i<=N;i++) sm+=mn[i],mn[i]=0; if(sm!=N) while(1);
    for(int i=1;i<=N;i++) in>>k[i];
    for(int i=1;i<=N;i++) in>>p[i];
    solve(1);
    for(int i=1;i<=N;i++) out<<ans[i]<<' '; out<<'\n';
    return 0 ;
}