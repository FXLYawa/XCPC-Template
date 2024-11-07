#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to,net,val;
};
vector<edge> e(100000);//重制ecnt就相当于重新建边
vector<int> head;//初始化为-1
int ecnt=-1;

inline void addedge(int u,int v,int w) {
    e[++ecnt]={v,head[u],w};head[u]=ecnt;
}
// 遍历 u 的出边
//for (int i = head[u]; ~i; i = e[i].net)  // ~i 表示 i != -1
void init(int n){//n点数 
    head.assign(n+1,-1);
}