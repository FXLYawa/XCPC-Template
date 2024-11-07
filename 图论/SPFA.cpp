#include <bits/stdc++.h>
using namespace std;
const int INF=0x7f7f7f7f;

struct edge {
  int v, w;
};
vector<vector<edge>> e;
vector<int> dis,cnt,vis;//dis初始化为INF

//n 点数  s 源点    
//return false 说明可以到达一个负环
bool spfa(int n, int s) {
    dis[s] = 0, vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;  // 记录最短路经过的边数
                if (cnt[v] >= n+1) return false;//经过负环
                if (!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}


void init(int n){
    e.clear();e.resize(n+1);
    dis.clear();dis.resize(n+1,INF);
    cnt.clear();cnt.resize(n+1);
    vis.clear();vis.resize(n+1);
}