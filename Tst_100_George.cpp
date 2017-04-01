/**
George Chichirim
"Mireca cel Batran" National College, Constanta
**/
#include <cstdio>
#include <cstring>
 
using namespace std;
 
char sir[5010];
int pi[5010],next[5010];
 
int main()
{
    freopen("tst.in", "r", stdin);
    freopen("tst.out", "w", stdout);
    scanf("%s",sir+1);
    int n=strlen(sir+1);
    long long sol=0;
    for(int i=1;i<=n;i++)
    {
        pi[1]=0;
        for(int j=i;j<=n;j++) next[j]=n+1;
        for(int j=i+1,k=0;j<=n;j++)
        {
            while(k && sir[i+k]!=sir[j]) k=pi[k];
            if(sir[i+k]==sir[j]) k++;
            pi[j-i+1]=k;
        }
        for(int j=n;j>i;j--)
        {
            next[i+pi[j-i+1]-1]=j;
            if(sir[j]==sir[i]) next[i]=j;
        }
        for(int j=i;j<=n;j++)
            sol+=i*(next[j]-j);
    }
    printf("%lld",sol);
    return 0;
}