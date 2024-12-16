#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> indeg;
vector<int> topu;  // res

bool toposort(int n) {  // 节点
    queue<int> S;
    // 用优先队列可以得到最大/最小字典序
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0) S.push(i);
    while (!S.empty()) {
        int u = S.front();
        S.pop();
        topu.push_back(u);
        for (auto v : g[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                S.push(v);
            }
        }
    }  // 返回能否构造一个拓扑序
    if (topu.size() == n)
        return true;
    else
        return false;
}

void init(int n) {
    g.clear();
    g.resize(n + 1);
    indeg.clear();
    indeg.resize(n + 1);
    topu.clear();
}