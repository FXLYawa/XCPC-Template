#include <bits/stdc++.h>
using namespace std;
constexpr int maxn=1000;
constexpr int mod=998244353;

int power(int a,int b,int p){
    int ans=1%p;
    for(;b;b>>=1){
        if(b&1)ans=(long long)ans*a%p;
        a=(long long)a*a%p;
    }
    return ans;
}

//阶乘加逆元  大
vector<int> fac,inv;
void init(int n) 
{
    fac.resize(n+1);inv.resize(n+1);
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=fac[i-1]*i%mod;
    inv[n]=power(fac[n],mod-2,mod);//逆元快速幂
    for(int i=n-1;i;i--)
        inv[i]=inv[i+1]*(i+1)%mod;
} 
int c(int a,int b){//Cab a在下
    if(a<0||b<0||a<b) return 0;
    return fac[a]*inv[a-b]%mod*inv[b]%mod;
}

//递推 小
int C[maxn][maxn];//C[a][b]  a在下
void init(){
    C[0][0]=1;
    for(int i=1;i<maxn;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
}






