#include <bits/stdc++.h>
using namespace std;
constexpr int INF=0x7f7f7f7f;



//Fleury算法
struct edge {int to,nxt;};
constexpr int maxn=1e5;
vector<edge> e(maxn);//重制ecnt就相当于重新建边
vector<int> head,vis(maxn);//初始化为-1
int ecnt=-1;
inline void addedge(int u,int v) {
    e[++ecnt]={v,head[u]};head[u]=ecnt;
    e[++ecnt]={u,head[v]};head[v]=ecnt;
}
void init(int n){//n点数
    ecnt=-1;head.assign(n+1,-1);
}
//链式前向星建图
stack<int> st;
vector<int> EulerRoad;
void dfs(int u) {
    st.push(u);
    for(int i=head[u];~i;i=e[i].nxt){
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        dfs(e[i].to);
        break;
   }
}
void fleury(int s){
    st.push(s);
    while(!st.empty()){
        int flag=0,u=st.top();st.pop();
        for(int i=head[u];~i;i=e[i].nxt){
            if(vis[i]) continue;
            flag=1;break;
        }
        if(!flag)EulerRoad.push_back(u);
        else dfs(u);
    }
}

//Hierholzers算法（输出字典序最小的答案）
int n;
vector<vector<int>> g;//记录边的数量
vector<int> d,ans;//入度  ans存的回路是倒序的
void init(int n){
    g.assign(n+1,vector<int>(n+1));
    d.clear();d.resize(n+1);
}
void dfs(int x){//入口是入度非0且为奇数数的节点
    for(int i=1;i<=n;i++){
        if(g[x][i]){
            g[x][i]--,g[i][x]--;
            dfs(i);
        }
    }
    ans.push_back(x);
}