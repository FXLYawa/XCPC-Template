#include <bits/stdc++.h>
using namespace std;



const int INF = 0x7f7f7f7f; //2139062143
const int maxn=110;
vector<vector<int>> g;//初始化为INF
int n;//节点数
//对g[i][j]初始化，i=j为0，i与j有边为边权，其余为INF 
//如果g[i][i]<0则有负环存在
void floyd(){
    for(int k=1;k<=n;k++)  //状态 表示i到j只经过小于k的节点的最短路
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}

void init(int n){
    g.resize(n+1,vector<int>(n+1,INF));
} 