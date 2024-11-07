#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
constexpr int INF=0x7f7f7f7f;
constexpr int maxn=1000;

struct edge {
  int v, w;
};

vector<int> dis,vis;//dis初始化为INF
// vector<int> f;
vector<vector<edge>> e;

void dijkstra(int s) {
    priority_queue<pii,vector<pii>,greater<pii>> q;
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto ed:e[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                // f[v]=f[u];
                q.push({dis[v], v});
            }
            // else if(dis[v]==dis[u]+w){
            //     f[v]+=f[u];
            // }
        }
    }
}

void init(int n){
    vis.clear();vis.resize(n+1);
    e.clear();e.resize(n+1);
    dis.clear();dis.resize(n+1,INF);
    //f.clear();f.resize(n+1);
}