#include <bits/stdc++.h>
using namespace std;

constexpr int INF=0x7f7f7f7f;
constexpr int maxn=5010;
int res;// 最小生成树权值之和

struct edge{
    int u,v,w;
    bool operator<(const edge &x)const{return w<x.w;} 
};

vector<int> fa;
vector<edge> e;

int find(int pos){  
    if(fa[pos]==pos)return pos;
    return fa[pos]=find(fa[pos]);
}
void merge(int i,int j){         
    int fx=find(i),fy=find(j);
    if(fx!=fy){fa[fx]=fy;}  
}
void kruskal(int n){//点数
    fa.resize(n+1);    
    for(int i=0;i<=n;i++)fa[i]=i;
    sort(e.begin(),e.end());
    for(int i=0;i<e.size();i++){
        if(find(e[i].u)!=find(e[i].v)){
            merge(e[i].u,e[i].v);
            res+=e[i].w;//按需修改 这条边属于最小生成树
        }
    }
}




//暴力 稠密图
int g[maxn][maxn];
//dis 中有INF说明不连通
void prim(int n){
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> q;
    vector<int> vis(n+1),dis(n+1,INF);
    dis.resize(n+1);for(int i=0;i<=n;i++)dis[i]=INF;
    dis[1]=0;q.push({0,1,0});
    while(q.size()){
        int u=q.top()[1];
        if(vis[u]){q.pop();continue;}
        res+=q.top()[0];//按需修改
        q.pop();
        vis[u]=1;
        for(int i=1;i<=n;i++){
            if(g[u][i]<dis[i]){
                dis[i]=g[u][i];
                q.push({g[u][i],i,u});//w v u  u表达从哪里转移来
            }
        }
    }
}