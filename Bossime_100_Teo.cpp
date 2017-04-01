/*
TeoIonescu
--- Solutie
*/
#include<bits/stdc++.h>
using namespace std;
ifstream in("bossime.in");
ofstream out("bossime.out");
 
int N;
long long A,B;
int main(){
    in>>N;
    for(int i=1;i<=N;i++){
        in>>A>>B;
        long long d=(A>B)?(A-B):(B-A);
        if(d%9==0){
            d/=9;
            if(A>B) d*=10;
            out<< (long long)(1e15) + d - A <<'\n';
        }
        else out<<"Imposibil\n";
    }
    return 0;
}