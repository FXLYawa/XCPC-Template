//Johnson 全源最短路径算法 nmlogm
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int INF=0x7f7f7f7f;


struct edge {int v,w;};
vector<vector<edge>> e;
vector<vector<int>> dis;//dis初始化为INF

bool johnson(int n,int m){//n 节点数 m 边数  返回false说明有负环
    for(int i=1;i<=n;i++)e[0].push_back({i,0});
    vector<int> h(n+1,INF),vis(n+1),cnt(n+1);
    h[0]=0;vis[0]=1;
    queue<int> q;q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                cnt[v] = cnt[u] + 1;  // 记录最短路经过的边数
                if (cnt[v] >= n+1) return false;//经过负环
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }//spfa  给边权加上势
    e[0].clear();
    for(int s=1;s<=n;s++){  //dijkstra
        priority_queue<pii,vector<pii>,greater<pii>> p;
        dis[s][s] = 0;
        for(int i=0;i<=n;i++)vis[i]=0;
        p.push({0, s});
        while (!p.empty()) {
            int u = p.top().second;
            p.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto ed : e[u]) {
                int v = ed.v, w = ed.w+h[u]-h[ed.v];
                if (dis[s][v] > dis[s][u] + w) {
                    dis[s][v] = dis[s][u] + w;
                    p.push({dis[s][v], v});
                }
            }
        }
        for(int i=1;i<=n;i++)dis[s][i]-=h[s]-h[i];
    }
    return true;
}

void init(int n){
    e.clear();e.resize(n+1);
    dis.clear();dis.resize(n+1,vector<int>(n+1,INF));
}