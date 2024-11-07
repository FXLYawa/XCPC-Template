#include <bits/stdc++.h>
using namespace std;
constexpr int INF = 0x7f7f7f7f7f7f7f7f; //2139062143^2

void ShortestPath(){//同余最短路 转圈
    int n,m;
    vector<int> a;
    vector<int> dp(m+1,INF);dp[0]=0;
    for(int i=2;i<=n;i++){//枚举物品 
        for(int j=0,ub=__gcd(a[i],m);j<ub;j++){//枚举环的起点
            for(int k=j,c=0;c<2;c+=(k==j)){//转两圈 确保更新完全
                int p=(k+a[i])%m;
                dp[p]=min(dp[p],dp[k]+a[i]);//dp更新方程
                k=p;
            }
        }
    }
}


