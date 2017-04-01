#include<bits/stdc++.h>
using namespace std;
ifstream in("arduino.in");
ofstream out("arduino.out");
 
 
const int MOD = 1e9+7;
vector<int> rs[101];
int n,m,r,v[11],nr[101],df[11];
unsigned long long ans=0;
 
void back(int i,int mx,unsigned long long p){
    if(i>n){
        for(int j=1;j<=r;j++){
            int cn=0;
            for(auto it:rs[j]){
                if(df[v[it]]==0) cn++;
                df[v[it]]=1;
            }
            for(auto it:rs[j]) df[v[it]]=0;
            if(cn!=nr[j]) return;
        }
        ans = (ans + p)%MOD;
        return;
    }
    for(v[i]=1;v[i]<=mx+1;v[i]++){
        back(i+1,max(mx,v[i]), ( p*(v[i]<=mx?(1):(m-v[i]+1)) )%MOD  );
    }
}
 
int main(){
    in>>n>>m>>r;
    int k;
    for(int i=1;i<=r;i++){
        in>>nr[i]>>k;
        for(int j=1;j<=k;j++){
            int x; in>>x;
            rs[i].push_back(x);
        }
    }
    v[1]=1;
    back(2,1,m);
    out<<ans<<'\n';
    return 0;
}