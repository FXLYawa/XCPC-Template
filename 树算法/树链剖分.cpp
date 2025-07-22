#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=1000;
vector<vector<int>> g;
vector<int> fa,dep,siz,son;
//父节点，深度，子树大小，重儿子

void dfs1(int u){
    son[u]=-1;siz[u]=1;
    for(auto v:g[u]){
        if(v==fa[u])continue;
        fa[v]=u;
        dep[v]=dep[u]+1;
        dfs1(v);
        siz[u]+=siz[v];
        if(son[u]==-1||siz[v]>siz[son[u]])son[u]=v;
    }
}
int cnt=0;//初始编号
vector<int> top,dfn,rnk;
//重链顶部节点  dfs序编号  dfs序对应的节点 (rnk[dfs[x]]=x)
void dfs2(int u,int t){//t表示链头  初始dfs2(root,root)
    top[u]=t;
    dfn[u]=++cnt;
    rnk[cnt]=u;
    if(son[u]==-1)return;
    dfs2(son[u],t);
    for(auto v:g[u]){
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
}

int lca(int x,int y){ //树剖求lca
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            y=fa[top[y]];
        }
        else x=fa[top[x]];
    }
    return dep[x]>dep[y]?y:x;
}

void init(int n){
    fa.resize(n+1);son.resize(n+1);
    siz.resize(n+1);dep.resize(n+1);
    dfn.resize(n+1),rnk.resize(n+1);
    top.resize(n+1);g.resize(n+1);
}

void modify(int l,int r){}//对应数据结构的修改函数
void modifypath(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])  
            swap(u,v); //深度大的点先跳，保证能跳到一条重链上
        modify(dfn[top[u]],dfn[u]);    
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    modify(dfn[u],dfn[v]); //在一条重链上，直接加
}
void modifysub(int u){
    modify(dfn[u],dfn[u]+siz[u]-1);
}
void getpath(int u,int v){
    vector<array<int,2>> path;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])  
            swap(u,v); //深度大的点先跳，保证能跳到一条重链上
        path.push_back({dfn[top[u]], dfn[u]});
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    path.push_back({dfn[u], dfn[v]}); //在一条重链上，直接加
}