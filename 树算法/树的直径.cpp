#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g;

int d=0;//记录直径
int dfs(int u,int fa){
    int mx=0,res=0;
    for(auto v:g[u]){
        if(v==fa)continue;
        res=dfs(v,u)+1;
        d=max(d,mx+res);
        mx=max(mx,res);
    }
    return mx;
}