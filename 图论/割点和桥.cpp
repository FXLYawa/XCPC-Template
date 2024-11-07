#include <bits/stdc++.h>
using namespace std;
//无向图
//cut[x]=1时，x为割点，若cut记录边的情况，则(cut[x],x)为割边
//边双连通分量  去掉桥之后剩下的
vector<vector<int>> g;
vector<int> dfn,low,cut,fa;
int dfncnt;//记录dfs序
void init(int n){
    dfncnt=0;
    fa.clear();fa.resize(n+1);
    cut.clear();cut.resize(n+1);//记录割点
    g.clear();g.resize(n+1);
    dfn.clear();dfn.resize(n+1);//dfs序
    low.clear();low.resize(n+1);//最早能回到的节点
}

void tarjan(int u){ 
    low[u]=dfn[u]=++dfncnt;
    int cnt=0;//孩子数量
    for(auto v:g[u]){
        if(dfn[v]){
            if(v!=fa[u])low[u]=min(low[u],dfn[v]);
            continue;
        }
        cnt++;fa[v]=u;
        tarjan(v);
        low[u]=min(low[u],low[v]);
        if(fa[u]==0&&cnt>1||fa[u]!=0&&dfn[u]<=low[v])cut[u]=1; //割点
        //if(dfn[x]<low[i])cut[x]=1;    //割边
    } 
}

vector<int> sta;int top=0;//初始化大小为n+1
vector<vector<int>> dcc;
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