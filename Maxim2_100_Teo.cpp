/*
TeoIonescu
--- Solutie O( N )
*/
#include<bits/stdc++.h>
using namespace std;
ifstream in("maxim2.in");
ofstream out("maxim2.out");
 
const int Nmax = 100000;
int N,v[Nmax+2];
 
void read(){
    in>>N;
    for(int i=1;i<=N;i++) in>>v[i];
}
 
int dl[Nmax+2];
int lib[Nmax+2];
int pars[Nmax+2];
int w[Nmax+2];
 
void solve(){
    for(int i=1;i<=N;i++) dl[i]=(v[i]==0);
    v[0]=v[N+1]=0;
    dl[0]=dl[N+1]=0;
 
    for(int i=1;i<=N;i++) lib[i]=1;
    for(int i=1;i<=N;i++){
        if(dl[i]) w[i]=0;
        else lib[v[i]]=0,w[i]=v[i];
    }
    pars[0]=0; for(int i=1;i<=N;i++) pars[i]=pars[i-1]+lib[i];
 
    long long total=pars[N];
    long double E=0.;
 
    for(int i=1;i<=N;i++){
        int mx=max(w[i-1],w[i+1]);
        int bro=dl[i-1]+dl[i+1];
        if(dl[i]){
            long long can=total-pars[mx];
            long long ans=can,mn=total;
            if(bro==1){
                ans=can*(2*total-can-1)/2;
                mn=total*(total-1);
            }
            if(bro==2){
                ans=can*(can*can -3*can*(total-1) +3*total*(total-2) +2)/3;
                mn=total*(total-1)*(total-2);
            }
            E += (long double)(ans)/(long double)(mn);
        }
        else{
            if(mx >= w[i]) continue;
            long long can=pars[w[i]];
            long long ans=1,mn=1;
            if(bro==1){
                ans=can;
                mn=total;
            }
            if(bro==2){
                ans=can*(can-1);
                mn=total*(total-1);
            }
            E += (long double)(ans)/(long double)(mn);
        }
    }
    out.precision(9);
    out<<fixed<<E<<'\n';
}
 
int main(){
    read();
    solve();
    return 0;
}