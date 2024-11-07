#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=40005;
std::vector<int> g[maxn];
int fa[maxn][31], dep[maxn];//初始化为0

//为lca做好准备 dfs(1,0)
void dfs(int u, int la) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    fa[u][0] = la;
    dep[u] = dep[fa[u][0]] + 1;
    //第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第2^(i-1) 的祖先节点。
    for (int i = 1; i < 31; ++i) 
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    // 遍历子节点来进行 dfs。
    for(auto v:g[u]){
        if(v==la)continue;
        dfs(v,u);
    }
}

//用倍增算法算取 x 和 y 的 lca 
int lca(int x, int y) {
    if(dep[x]>dep[y])swap(x,y);//保证y比x深
    // 令 y 和 x 在一个深度。
    int tmp=dep[y]-dep[x];
    for(int j=0;tmp;++j,tmp>>=1)
        if(tmp&1)y=fa[y][j];//令xy深度相同
    if(y==x)return x;
    for(int j=30;j>=0;--j){
        if(fa[x][j]!=fa[y][j]){
            x=fa[x][j];
            y=fa[y][j];
        }
    }
    return fa[x][0];
}


