#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> siz,ans,weight,fa;//wei是最重的子树编号

//求出的重心的fa可能是一个重心
void dfs(int u){//求出每个子树的一个重心
    siz[u]=1,ans[u]=u;
    for(auto v:g[u]){
        if(v==fa[u])continue;
        fa[v]=u;
        dfs(v);
        siz[u]+=siz[v];
        weight[u]=max(weight[u],siz[v]);
    }
    for(auto v:g[u]){
        if(v==fa[u])continue;
        int p=ans[v];
        while(p!=u){
            if(max(weight[p],siz[u]-siz[p])<=siz[u]/2) {
                ans[u]=p;
                break;
            } 
            else p=fa[p];
        }
    }
}
void init(int n){
    g.clear();g.resize(n+1);
    siz.clear();siz.resize(n+1);
    weight.clear();weight.resize(n+1);
    ans.clear();ans.resize(n+1);
    fa.clear();fa.resize(n+1);
}