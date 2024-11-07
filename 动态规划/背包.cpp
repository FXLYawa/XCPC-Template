#include <bits/stdc++.h>
using namespace std;

int W,n;//背包容量
vector<int> wei,val;
vector<int> dp;

//01背包
void O1bag(){
    for(int i=1;i<=n;i++)
        for(int j=W;j>=wei[i];j--)
            dp[j]=max(dp[j-wei[i]]+val[i],dp[j]);
}
//完全背包
void completebag(){
    for(int i=1;i<=n;i++)
        for(int j=wei[i];j<=W;j++)
            dp[j]=max(dp[j-wei[i]]+val[i],dp[j]);
}
//多重背包
void div(int cnt,int w,int v){//多重分组函数，分完跑01
    for(int c=1;c<cnt;c*=2){
        cnt-=c;
        wei.push_back(c*w);
        val.push_back(c*v);
    }
    if(cnt){
        wei.push_back(cnt*w);
        val.push_back(cnt*v);
    }
}
//二维背包
vector<int> cost,tim;int C,T;
void TwoDBag(vector<vector<int>> dp){//经费时间
    for(int i=1;i<=n;i++)
        for(int j=C;j>=cost[i];j--)// 对经费进行一层枚举
            for (int k=T;k>=tim[i];k--)// 对时间进行一层枚举
                dp[j][k]=max(dp[j][k],dp[j-cost[i]][k-tim[i]]+val[i]);
}
//分组背包
vector<vector<int>> goods;//物品编号
void GroupBag(){
    for(int k=1;k<=n;k++)// 循环每一组
        for(int i=W;i>=0;i--)// 循环背包容量
            for(auto j:goods[k])// 循环该组的每一个物品
                if(i>=wei[j])// 背包容量充足
                    dp[i]=max(dp[i],dp[i-wei[j]]+val[j]);// 像0-1背包一样状态转移
}

