#include <bits/stdc++.h>
using namespace std;
//tarjan
constexpr int maxn=1000;
vector<vector<int>> g;
vector<int> dfn,low,belong,vis,siz,st;
int dfncnt,scc;//记录dfs序，连通编号
void init(int n){
    dfncnt=0;scc=0;
    g.clear();g.resize(n+1);
    siz.clear();siz.resize(n+1);
    dfn.clear();dfn.resize(n+1);//dfs序
    low.clear();low.resize(n+1);//最早能回到的节点
    belong.clear();belong.resize(n+1);
    vis.clear();vis.resize(n+1);//是否在栈
}

void tarjan(int u){ //强连通分量
    low[u]=dfn[u]=++dfncnt;
    st.push_back(u);vis[u]=1;
    for(auto v:g[u]){
        if(dfn[v]){
            if(vis[v])low[u]=min(low[u],dfn[v]);
            continue;
        }
        tarjan(v);
        low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u]){
        ++scc;int k;
        do{
            k=st.back();st.pop_back();
            belong[k]=scc;
            siz[scc]++;vis[k]=0;
        }while(k!=u);
    }
}


//*************************************************//
//kosaraju
vector<vector<int>> g1,g2;
vector<int> vis,dfn,rnk,belong,siz;
int dfncnt=0,scc=0;
void init(int n){
    dfncnt=0;scc=0;
    g1.clear();g1.resize(n+1);//正向图
    g2.clear();g2.resize(n+1);//反向图
    dfn.clear();dfn.resize(n+1);
    rnk.clear();rnk.resize(n+1);
    siz.clear();siz.resize(n+1);
    belong.clear();belong.resize(n+1);
    vis.clear();vis.resize(n+1);
}

void dfs1(int x){
    vis[x]=1;
    for(int i:g1[x])
        if(!vis[i])dfs1(i);
    dfn[x]=++dfncnt;rnk[dfn[x]]=x;
}
void dfs2(int x){
    belong[x]=scc;
    siz[scc]++;
    for(int i:g2[x])
        if(!belong[i])dfs2(i);
}
void kosaraju(int n){  //节点个数
    for(int i=1;i<=n;++i)
        if(!vis[i])dfs1(i);
    for(int i=n;i>=1;--i){
        if(belong[rnk[i]])continue;
        ++scc;
        dfs2(rnk[i]);
    }
}