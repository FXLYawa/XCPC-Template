#include <bits/stdc++.h>
using namespace std;

struct twosat{
    int n;//节点数量
    vector<vector<int>> g;//图
    vector<int> ans;//base1
    twosat(int n) : n(n), g(2 * n + 2), ans(n + 1){};//图从2开始存
    //a,b至少选一个      连边 !a->b与!b->a
    //a,b不能同时选   连边 a->!b与b->!a
    //a,b必须同时选   连边 a->b与b->a
    //a必须选    连边 !a->a
    void add(int u,bool x,int v,bool y){ //加边 下标较小者为false点
        g[2 * u + x].push_back(2 * v + y);
    }
    bool satisfiable(){//判定命题能否被满足
        vector<int> belong(2 * n), dfn(2 * n), low(2 * n),vis(2 * n +1);
        vector<int> st;
        int dfncnt = 0, scc = 0;//dfn序  SCC计数
        function<void(int)> tarjan = [&](int u){
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
                ++scc;
                int k;
                do{
                    k=st.back();st.pop_back();
                    belong[k]=scc;vis[k]=0;
                } while(k!=u);
            }
        };
        for (int i = 2; i <= 2 * n + 1; i++) if (!dfn[i]) tarjan(i);
        for (int i = 1; i <= n; i++) {
            if (belong[2 * i] == belong[2 * i + 1]) return false;
            ans[i] = belong[2 * i] > belong[2 * i + 1];//由于tarjan缩点是按照反拓扑序编号，越大的节点拓扑序越大
        }
        return true;
    }
    vector<int> getans() { return ans; };//获得一组可行解
};

struct TwoSat {//蒋老师的码 base 0
    int n;
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}
    void addClause(int u, bool f, int v, bool g) {
    	//表示u满足f或v满足 g 
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }
    void add(int u, bool f, int v, bool g) {
    	//满足(u,f)必须满足(v,g) 
        e[2 * u + f].push_back(2 * v + g);
    }
    bool satisfiable() {
        std::vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        std::vector<int> stk;
        int now = 0, cnt = 0;
        std::function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};//注意下标应当从零开始,故addclause时注意是否需要-1 