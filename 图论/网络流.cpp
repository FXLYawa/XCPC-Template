#include <bits/stdc++.h>
using namespace std;
const int INF=0x7f7f7f7f;
#define pii pair<int,int>

//EK算法（Edmonds–Karp 算法）  n m^2
struct EK{//最大流则修改边的和加边函数的定义 删去cost
    const int M=1e5+100;//终点，下一条边，残量，容量上限
    struct edge {int to,net,val,cap,cost;};
    vector<edge> e;
    vector<int> head,pre,flow,dis,h;
    int ecnt;//初始化为-1或1

    int n,s,t;
    
    inline void addedge(int u,int v,int w,int cost=0){//重复使用可以写e.pb({});再加入边
        e[++ecnt]={v,head[u],w,w,cost};head[u]=ecnt;
        e[++ecnt]={u,head[v],0,w,-cost};head[v]=ecnt;
    }
    EK(int nn,int S=0,int T=0){
        n=nn;s=S;t=T;ecnt=-1;
        head.assign(n+1,-1);e.resize(M);
        pre.resize(n+1);flow.resize(n+1);
    }
    //最大流部分
    bool bfs(){ //寻找增广路
        vector<int> vis(n+1);vis[s]=1;
        queue<int> q;q.push(s);
        flow[s]=INF;//源点流量无限大
        while(q.size()){
            int u=q.front();q.pop();
            for(int i=head[u];~i;i=e[i].net){
                int v=e[i].to;
                if(e[i].val==0||vis[v])continue;//余量为0或者已经访问过下一个点
                flow[v]=min(flow[u],e[i].val);//记录最小增广路容量
                pre[v]=i;//记录前驱的边 以便寻找增广路方案
                q.push(v);vis[v]=1;
                if(v==t)return true;
            }
        }
        return false;//找不到增广路
    }
    int update(){//更新增广路及其反向边残量
        int u=t;
        while(u!=s){
            e[pre[u]].val-=flow[t];
            e[pre[u]^1].val+=flow[t];
            u=e[pre[u]^1].to;
        }
        return flow[t];
    }
    int get_maxflow(){
        int res=0;
        while(bfs())res+=update();
        return res;
    }
    //费用流部分
    void spfa() {
        h.resize(n+1,INF);vector<int> vis(n+1);
        queue<int> q;q.push(s);
        h[s]=0,vis[s]=1;
        while (!q.empty()) {
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=head[u];~i;i=e[i].net) {
                int v=e[i].to;
                if (e[i].val&&h[v]>h[u]+e[i].cost) {
                    h[v]=h[u]+e[i].cost;
                    if(!vis[v])vis[v]=1,q.push(v);
                }
            }
        }
    }
    bool dijkstra() {
        priority_queue<pii,vector<pii>,greater<pii>> q;
        dis.assign(n+1,INF);
        vector<int> vis(n+1);
        dis[s]=0;
        q.push({0, s});
        while(q.size()) {
            int u=q.top().second;q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(int i=head[u];~i;i=e[i].net) {
                int v=e[i].to,cost=e[i].cost+h[u]-h[v];
                if(e[i].val&&dis[v]>dis[u]+cost){
                    dis[v]=dis[u]+cost;
                    pre[v]=i;//记录前驱的边 以便寻找增广路方案
                    if(!vis[v])q.push({dis[v],v});
                }
            }
        }
        // 前提是答案不是INF(特殊情况要特判)
        return dis[t]!=INF;
    }
    pair<int,int> get_mincost(){
        int res=0,cost=0;
        spfa();//求出初始势能
        while(dijkstra()){
            for(int i=1;i<=n;i++)h[i]+=dis[i];//更新势能
            int flow=INF;
            for(int u=t;u!=s;u=e[pre[u]^1].to)flow=min(flow,e[pre[u]].val);
            for(int u=t;u!=s;u=e[pre[u]^1].to){
                e[pre[u]].val-=flow;
                e[pre[u]^1].val+=flow;
            }
            res+=flow;
            cost+=flow*h[t];
        }
        return {res,cost};
    }
};


//Dinic算法（当前弧优化）   n^2 m   求解二分图最大匹配时 n^1/2 m   
struct Dinic{
    const int M=2e6;//终点，下一条边，残量，容量上限
    struct edge {int to,net,val,cap,cost;};
    vector<edge> e;
    vector<int> head,dep,now,dis,vis;
    int ecnt;//初始化为-1或1

    int n,s,t;

    inline void addedge(int u,int v,int w,int cost=0){//重复使用可以写e.pb({});再加入边
        e[++ecnt]={v,head[u],w,w,cost};head[u]=ecnt;
        e[++ecnt]={u,head[v],0,w,-cost};head[v]=ecnt;
    }
    Dinic(int nn,int S=0,int T=0){
        n=nn;s=S;t=T;ecnt=-1;
        head.assign(n+1,-1);e.resize(M);
        dep.resize(n+1);now.resize(n+1);
        vis.resize(n+1);
    }
    //最大流部分
    bool bfs(){  //构造分层图  同时初始化当前弧
        dep.assign(n+1,0);
        queue<int> q;q.push(s);dep[s]=1;now[s]=head[s];
        while(q.size()){
            int u=q.front();q.pop();
            for(int i=head[u];~i;i=e[i].net){
                int v=e[i].to;
                if(dep[v]||e[i].val==0)continue;
                q.push(v);
                now[v]=head[v];
                dep[v]=dep[u]+1;
                if(v==t)return true;
            }
        }   
        return false;
    }
    int dfs(int u,int in){//流入量
        if(u==t)return in;
        int flow=0;//实际有用的流量
        for(int i=now[u];~i&&in;i=e[i].net){
            now[u]=i;//当前弧优化
            int v=e[i].to;
            if(dep[v]!=dep[u]+1||e[i].val==0)continue;
            int out=dfs(v,min(in,e[i].val));//通过这条边可以流出去的流量
            if(out==0)dep[v]=-1;//剪掉增广完毕的点
            e[i].val-=out;
            e[i^1].val+=out;
            flow+=out;
            in-=out;
        }
        if(!flow)dep[u]=-1;
        return flow;
    }
    int get_maxflow(){
        int res=0;
        while(bfs())res+=dfs(s,INF);
        return res;
    }


    //费用流部分
    bool spfa(){
        now=head;
        dis.assign(n+1,INF);dis[s]=0;
        queue<int> q;q.push(s);vis[s]=1;
        for(int u;q.size();q.pop()){
            vis[u=q.front()]=0;
            for(int i=head[u];~i;i=e[i].net){
                int v=e[i].to,w=e[i].cost;
                if(e[i].val&&dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    if(!vis[v])q.push(v),vis[v]=1;
                }
            }
        }
        return dis[t]!=INF;
    }
    pair<int,int> _dfs(int u,int in){//流入量
        if(u==t||!in)return {in,0};
        int flow=0,cost=0;//实际有用的流量
        vis[u]=1;
        for(int &i=now[u];~i&&in;i=e[i].net){
            int v=e[i].to,w=e[i].cost;
            if(dis[v]!=dis[u]+w||!e[i].val||vis[v])continue;
            pair<int,int> tmp=_dfs(v,min(in,e[i].val));//通过这条边可以流出去的流量
            int out=tmp.first;
            if(!out)dis[v]=-1;
            e[i].val-=out;e[i^1].val+=out;
            flow+=out;in-=out;
            cost+=out*w+tmp.second;
        }
        if(!flow)dis[u]=-1;
        vis[u]=0;
        return {flow,cost};
    }
    pair<int,int> get_mincost(){
        pair<int,int> res={0,0},tmp;
        while(spfa()){
            tmp=_dfs(s,INF);
            res.first+=tmp.first;
            res.second+=tmp.second;
        }
        return res;
    }
};


//ISAP算法     gap和当前弧优化 n^2 m
struct ISAP{
    const int M=20000;//终点，下一条边，残量，容量上限
    struct edge {int to,net,val,cap;};
    vector<edge> e;
    vector<int> head,dep,now,gap;
    int ecnt;//初始化为-1或1

    int n,s,t;

    inline void addedge(int u,int v,int w){//重复使用可以写e.pb({});再加入边
        e[++ecnt]={v,head[u],w,w};head[u]=ecnt;
        e[++ecnt]={u,head[v],0,w};head[v]=ecnt;
    }
    ISAP(int nn,int S=0,int T=0){
        n=nn;s=S;t=T;ecnt=-1;
        head.assign(n+1,-1);e.resize(M);
        dep.resize(n+1,n);//处理了孤立点
        gap.resize(n+2); //分层图退化层链时，存在深度为n的点
    }
    void bfs(){
        queue<int> q;q.push(t);dep[t]=0;gap[0]++;
        while(q.size()){
            int u=q.front();q.pop();
            for(int i=head[u];~i;i=e[i].net){
                int v=e[i].to;
                if(dep[v]!=n)continue;
                dep[v]=dep[u]+1;
                gap[dep[v]]++;
                q.push(v);
            }
        }
    }
    int dfs(int u,int in){//流入量  
        if(u==t)return in;
        int flow=0;//实际有用的流量
        for(int i=now[u];~i;i=e[i].net){
            now[u]=i;//当前弧优化
            int v=e[i].to;
            if(dep[v]+1!=dep[u]||e[i].val==0)continue;
            int out=dfs(v,min(in,e[i].val));//通过这条边可以流出去的流量
            e[i].val-=out;
            e[i^1].val+=out;
            flow+=out;
            in-=out;
            if(in==0)return flow;
        }
        if(--(gap[dep[u]])==0)dep[s]=n;//出现断层 直接结束程序
        ++(gap[++dep[u]]);//所有边流完，离汇点更远了
        return flow;
    }
    
    int get_maxflow(){
        int ans=0;
        bfs();
        while(dep[s]<n){
            now=head;
            ans+=dfs(s,INF);
        }
        return ans;
    }
};


//HLPP算法  n^2 m^(1/2)
//标准版  s和t的答案对称 (可以不考虑高度大于n的节点，加速 但是会破坏图的结构)
struct HLPP{
    const int M=3e5;//终点，下一条边，残量，容量上限
    struct edge {int to,net,val,cap;};
    vector<edge> e;
    vector<int> head,h,over,vis,gap;
    //节点高度标记   超限流  是否在队列中  gap优化
    priority_queue<pair<int,int>> q;
    int ecnt;//初始化为-1或1

    int n,s,t;
    
    inline void addedge(int u,int v,int w){//重复使用可以写e.pb({});再加入边
        e[++ecnt]={v,head[u],w,w};head[u]=ecnt;
        e[++ecnt]={u,head[v],0,w};head[v]=ecnt;
    }
    HLPP(int nn,int S=0,int T=0){
        n=nn;s=S;t=T;ecnt=-1;
        head.assign(n+1,-1);e.resize(M);
        h.assign(n+1,n+1);over.resize(n+1);
        vis.resize(n+1);gap.resize(n+100);//gap开大，避免乱贴标签出问题
    }
    bool bfs(){ //bfs完成节点高度的初始化 特别的 h[s]=n
        queue<int> q;q.push(t);h[t]=0;
        while(q.size()){
            int u=q.front();q.pop();
            for(int i=head[u];~i;i=e[i].net){
                int v=e[i].to;
                if(e[i^1].val==0||h[v]!=n+1)continue;
                h[v]=h[u]+1;
                q.push(v);
            }
        }
        if(h[s]==n+1)return false;
        h[s]=n;
        return true;
    }
    void push(int u){   //推送节点流量
        for(int i=head[u];~i;i=e[i].net){
            int v=e[i].to;
            if(e[i].val==0||h[v]+1!=h[u])continue;
            int out=min(over[u],e[i].val);
            e[i].val-=out;e[i^1].val+=out;//更新边流量
            over[u]-=out;over[v]+=out;//更新节点超限量
            if(vis[v]||v==s||v==t)continue;
            q.push({h[v],v});vis[v]=1;
            if(over[u]==0)break;//没有流量了
        }
    }
    void relabel(int u){    //重贴标签
        h[u]=INF;
        for(int i=head[u];~i;i=e[i].net){
            int v=e[i].to;//让下次可以推送
            if(e[i].val&&h[v]+1<h[u])h[u]=h[v]+1;
        }
    }
    int get_maxflow(){//hlpp主体
        if(!bfs())return 0;//不连通
        for(int i=1;i<=n;i++)gap[h[i]]++;
        for(int i=head[s];~i;i=e[i].net){//单独推送源点
            int v=e[i].to;
            int out=e[i].val;
            e[i].val-=out;e[i^1].val+=out;//更新边流量
            over[s]-=out;over[v]+=out;//更新节点超限量
            if(vis[v]||v==s||v==t)continue;
            q.push({h[v],v});vis[v]=1;
        }
        while(q.size()){
            int u=q.top().second;q.pop();vis[u]=0;
            push(u);
            if(!over[u])continue;//还有余流 则重新贴标签
            if(!--gap[h[u]])//该高度只有一个节点
                for(int i=1;i<=n;i++)//出现断层 高度大于我的都不可能到汇点
                    if(i!=t&&i!=s&&h[i]<n+1&&h[i]>h[u])
                        gap[h[i]]--,h[i]=n+1,gap[h[i]]++;
            relabel(u);//重贴标签，保证下次能够推送
            gap[h[u]]++;//更新高度 
            q.push({h[u],u});//因为还有余流所以进队 
			vis[u]=1;//标记 
        }
        return over[t];
    }
};

//一堆优化
struct HLPP {
    /*
     * set int to int or long long
     * nodes numbered by 1, 2, ..., n
     */
    typedef long long int; // or int
    struct Edge {
        int to;
        int c;
        int rev;
        Edge(int to, int c, int rev): to(to), c(c), rev(rev) {}
    };
    
    int n, m, s, t;
    int maxh, maxgaph, workcnt;
    std::vector<std::vector<Edge>> vec; // graph
    std::vector<int> ov,h,cur,ovList,ovNxt,gap,gapPrv,gapNxt;
    // overflow of nodes height of nodes   current arc
    // n: nodes, m: edges, s: source node, t: sink node
    HLPP(int n, int m, int s, int t): n(n), m(m), s(s), t(t), maxh(0), maxgaph(0), workcnt(0),
                                      vec(n+1), ov(n+1), h(n+1), cur(n+1),
                                      ovList((n+1), -1), ovNxt(n+1, -1),
                                      gap((n+1), -1), gapPrv(n+1, -1), gapNxt(n+1, -1) {}

    void addEdge(int u, int v, int c) {
        vec[u].push_back(Edge(v, c, vec[v].size()));
        vec[v].push_back(Edge(u, 0, vec[u].size()-1));
    }
    int getMaxFlow() {
        globalRelabel();
        for(auto &e: vec[s]) if(e.c) { pushFlow(s, e, e.c);  maxh = std::max(maxh, h[e.to]); }
        for(; maxh >= 0; --maxh) {
            while(~ovList[maxh]) {
                int x = ovList[maxh];
                ovList[maxh] = ovNxt[x];
                discharge(x);
                if(workcnt > (n<<2))  globalRelabel();
            }
        }
        return ov[t];
    }
private:
    void discharge(int x) {
        int nh = n, sz = vec[x].size();
        for(int i = cur[x]; i < sz; ++i) {
            auto &e = vec[x][i];
            if(e.c > 0) {
                if(h[x] == h[e.to]+1) {
                    pushFlow(x, e, std::min(ov[x], e.c));
                    if(ov[x] == 0) { cur[x] = i;  return ; }
                } else nh = std::min(nh, h[e.to]+1);
            }
        }
        for(int i = 0; i < cur[x]; ++i) {
            auto &e = vec[x][i];
            if(e.c > 0) { nh = std::min(nh, h[e.to]+1); }
        }
        cur[x] = 0;
        ++workcnt;
        if(~gapNxt[gap[h[x]]])  setHeight(x, nh);
        else {
            int oldh = h[x];
            for(int i = oldh; i <= maxgaph; ++i) {
                for(int j = gap[i]; ~j; j = gapNxt[j])  h[j] = n;
                gap[i] = -1;
            }
            maxgaph = oldh-1;
        }
    }
    void globalRelabel() {
        workcnt = maxh = maxgaph = 0;
        std::fill(h.begin(), h.end(), n);  h[t] = 0;
        std::fill(gapPrv.begin(), gapPrv.end(), -1);
        std::fill(gapNxt.begin(), gapNxt.end(), -1);
        std::fill(gap.begin(), gap.end(), -1);
        std::fill(ovList.begin(), ovList.end(), -1);
        std::fill(ovNxt.begin(), ovNxt.end(), -1);
        std::fill(cur.begin(), cur.end(), 0);
        std::queue<int> que;  que.push(t);
        int x;
        while(!que.empty()) {
            x = que.front();  que.pop();
            for(auto &e: vec[x]) {
                if(h[e.to] == n && e.to != s && vec[e.to][e.rev].c > 0) {
                    setHeight(e.to, h[x]+1);
                    que.push(e.to);
                }
            }
        }
    }
    void setHeight(int x, int newh) {
        if(~gapPrv[x]) {
            if(gapPrv[x] == x) {
                gapPrv[gapNxt[x]] = gapNxt[x];
                gap[h[x]] = gapNxt[x];
            } else {
                gapNxt[gapPrv[x]] = gapNxt[x];
                if(~gapNxt[x])  gapPrv[gapNxt[x]] = gapPrv[x];
            }
        }
        if((h[x] = newh) >= n)  return ; // ignore the case of h >= n
        maxgaph = std::max(maxgaph, h[x]);
        if(ov[x] > 0) { maxh = std::max(maxh, h[x]);  ovNxt[x] = ovList[h[x]];  ovList[h[x]] = x; }
        if(~(gapNxt[x] = gap[h[x]]))  gapPrv[gapNxt[x]] = x;
        gap[h[x]] = gapPrv[x] = x;
    }
    void pushFlow(int from, Edge &e, int flow) {
        if(!ov[e.to] && e.to != t) {
            ovNxt[e.to] = ovList[h[e.to]];
            ovList[h[e.to]] = e.to;
        }
        e.c -= flow;
        vec[e.to][e.rev].c += flow;
        ov[from] -= flow;
        ov[e.to] += flow;
    }
};