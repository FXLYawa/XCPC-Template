#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g;
vector<int> dfn,low,fa,sta;
int dfncnt;//记录dfs序
int top=0;//初始化大小为n+1
vector<vector<int>> dcc;
void init(int n){
    dfncnt=0;top=0;
    fa.clear();fa.resize(n+1);
    g.clear();g.resize(n+1);
    dfn.clear();dfn.resize(n+1);//dfs序
    low.clear();low.resize(n+1);//最早能回到的节点
    sta.clear();sta.resize(n+1);

}

void tarjan(int u){//点双连通分量
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;int cnt=0;
    for(auto v:g[u]){
        if(dfn[v]){
            if(v!=fa[u])low[u]=min(low[u],dfn[v]);
            continue;
        }
        cnt++;fa[v]=u;
        tarjan(v);
        low[u]=min(low[u],low[v]);
        if(low[v]>=dfn[u]){
            vector<int> res;
            while(sta[top+1]!=v)res.push_back(sta[top--]);
            res.push_back(u);dcc.push_back(res);
        }
    }
    if(!fa[u]&&!cnt)dcc.push_back({u});//特判独立点
}

vector<vector<int>> T;
//标号为1-n的为圆点  标号大于n的为方点
void build(int n){
    tarjan(1);//跑点双的tarjan
    T.resize(n+1+dcc.size());
    for(int i=0;i<dcc.size();i++){
        int u=n+i+1;
        for(auto v:dcc[i]){
            T[v].push_back(u);
            T[u].push_back(v);
        }
    }
}
//后续就在树上维护