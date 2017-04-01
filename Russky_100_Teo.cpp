/*
TeoIonescu
--- Solutie O( Q*logQ + N^2*logN + Q*logN )
*/
#include<bits/stdc++.h>
using namespace std;
ifstream in("russky.in");
ofstream out("russky.out");
 
const int Nmax = 1000;
const int Qmax = 100000;
 
vector<pair<int,int>> Q;
int v[Nmax+1],Ans[Qmax+1];
int N,Z,quer;
 
void read(){
    in>>N>>Z;
    for(int i=1;i<=N;i++) in>>v[i];
    in>>quer;
    for(int i=0;i<quer;i++){
        int l,p; in>>l>>p;
        Q.push_back(make_pair(l,p));
    }
}
 
queue<pair<int,int>> que[Nmax+1];
map<int,int> Idx;
int Lst[Nmax+1],Pval[Nmax+1];
int kIdx=0;
 
map<int,vector<pair<int,int>>> Qfor;
map<int,vector<pair<pair<int,int>,pair<int,int>>>> Puds;
 
class pstruc{
private:
    int *A,*C,N;
    int lsb(int x){return x&(-x);}
    void upd(int* v,int x,int val){while(x<=N) v[x]+=val,x+=lsb(x);}
    int quer(int* v,int x){int s=0; while(x) s+=v[x],x-=lsb(x); return s;}
public:
    pstruc(int n){
        A=new int[n+1];
        C=new int[n+1];
        for(int i=0;i<=n;i++) A[i]=C[i]=0;
        N=n;
    }
    void addPair(int a,int b,int c,int d,int op){
        int st = c-b+1;
        int mx = max(d-c,b-a);
        int mn = min(d-c,b-a);
        upd(A,st         ,op*(1));
        upd(A,st+mn      ,op*(-1));
        upd(A,st+mx+1    ,op*(-1));
        upd(A,st+mn+mx+1 ,op*(1));
        upd(C,st         ,op*(-st+1));
        upd(C,st+mn      ,op*(st+mn));
        upd(C,st+mx+1    ,op*(st+mx));
        upd(C,st+mn+mx+1 ,op*(-st-1-mx-mn));
    }
    int getPos(int i){
        return i*quer(A,i) + quer(C,i);
    }
} *Aib;
 
void SolveForPvalue(vector<pair<int,int>> ques,vector<pair<pair<int,int>,pair<int,int>>> upds){
    for(auto it:upds){
        pair<int,int> p1=it.first;
        pair<int,int> p2=it.second;
        int a=p1.first,b=p1.second;
        int c=p2.first,d=p2.second;
        if(a>b || c>d) continue;
        Aib->addPair(a,b,c,d,1);
    }
    for(auto it:ques){
        int q=it.first+1;
        int L=it.second;
        Ans[q]=Aib->getPos(L);
    }
    for(auto it:upds){
        pair<int,int> p1=it.first;
        pair<int,int> p2=it.second;
        int a=p1.first,b=p1.second;
        int c=p2.first,d=p2.second;
        if(a>b || c>d) continue;
        Aib->addPair(a,b,c,d,-1);
    }
}
 
void solve(){
    Aib = new pstruc(Nmax+1);
 
    for(int q=0;q<Q.size();q++){
        int L=Q[q].first;
        int P=Q[q].second;
        Qfor[P].push_back(make_pair(q,L));
    }
    for(int dif=0;dif<N;dif++){
        Idx.clear();
        for(int i=0;i<=kIdx;i++){
            Lst[i]=0;
            while(que[i].size()) que[i].pop();
        }
        kIdx=0;
        int fst=dif+1;
        for(int i=1;i<=N;i++) if(i-dif>=1){
            int j=i-dif;
            int aij=v[i]+v[j];
            if(!Idx[aij]) Idx[aij]=++kIdx,Pval[kIdx]=aij;
            int pid=Idx[aij];
            if(!Lst[pid]) Lst[pid]=fst-1;
            pair<int,int> t = make_pair(Lst[pid]+1,i);
            if(que[pid].size()==Z){
                pair<int,int> pr=que[pid].front(); que[pid].pop();
                Puds[aij].push_back(make_pair(pr,make_pair(t.first-1,t.second-1)));
            }
            que[pid].push(t);
            Lst[pid]=i;
        }
        for(int pid=1;pid<=kIdx;pid++){
            if(que[pid].size()==Z){
                pair<int,int> pr=que[pid].front(); que[pid].pop();
                pair<int,int> t = make_pair(Lst[pid],N);
                Puds[Pval[pid]].push_back(make_pair(pr,t));
            }
        }
    }
    for(auto it : Qfor) SolveForPvalue(it.second,Puds[it.first]);
    for(int q=0;q<Q.size();q++) out<<Ans[q+1]<<'\n';
}
 
int main(){
    read();
    solve();
    return 0;
}