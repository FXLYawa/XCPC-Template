//cf741d
#include <bits/stdc++.h>
using namespace std;

typedef long long                               ll;
typedef unsigned long long                      ull;
#define int                                     long long
#define endl                                    '\n'
#define Endl                                    endl;
#define al(a)                                   (a).begin(),(a).end()
#define all(a)                                  (a).begin()+1,(a).end()
#define vi                                      vector<int>
#define pii                                     pair<int,int>

constexpr int INF = 0x7f7f7f7f; //2139062143



constexpr int N=1231564;

vector<vector<int>> g;
vector<int> fa,dep,siz,son,col;
//父节点，深度，子树大小，重儿子，节点权值
vector<int> ans;         //记录答案
vector<int> res;         //记录节点贡献
map<pii,int> mp;         //题目部分（计算节点贡献用）   

void dfs1(int u,int t){     //dfs预处理
    son[u]=-1;siz[u]=1;
    col[u]=t;
    for(auto v:g[u]){
        if(v==fa[u])continue;
        fa[v]=u;
        dep[v]=dep[u]+1;
        dfs1(v,t^(mp[{min(v,u),max(v,u)}]));
        siz[u]+=siz[v];
        if(son[u]==-1||siz[v]>siz[son[u]])son[u]=v;
    }
}

void init(int n){       //初始化
    fa.resize(n+1);son.resize(n+1);
    siz.resize(n+1);dep.resize(n+1);
    g.resize(n+1);col.resize(n+1);
    ans.resize(n+1);res.resize((1<<22),-INF);
}

void handle(int u,int p){       //计算方式
    int t=col[u]^0;
    for(int i=0;i<=22;i++){
        ans[p]=max(ans[p],dep[u]+res[t]-2*dep[p]);
        t=col[u]^(1ll<<i);
    }
}
void lig_cal(int u,int p){//二次遍历轻儿子计算答案
    handle(u,p);
    for(auto v:g[u]){
        if(v==fa[u])continue;
        lig_cal(v,p);
    }
}
void lig_re(int u){//二次遍历轻儿子记录贡献
    res[col[u]]=max(dep[u],res[col[u]]);   
    for(auto v:g[u]){
        if(v==fa[u])continue;
        lig_re(v);
    }
}

void deal(int u){       //计算答案
    for(auto v:g[u]){       
        if(v==fa[u]||v==son[u])continue;
        lig_cal(v,u);
        lig_re(v);
        ans[u]=max(ans[u],ans[v]);//答案不经过x
    }
    handle(u,u);
    ans[u]=max(ans[u],ans[son[u]]);
}

void clear(int u){              //清空贡献
    res[col[u]]=-INF;
    for(auto v:g[u]){
        if(v==fa[u])continue;
        clear(v);
    }
}

void dsu(int u){        //主体
    if(son[u]==-1){
        res[col[u]]=max(dep[u],res[col[u]]);
        return;
    }
    for(auto v:g[u]){
        if(v==fa[u]||v==son[u])continue;
        dsu(v);         //处理轻儿子
        clear(v);       //清空轻儿子贡献
    }
    dsu(son[u]);        //处理重儿子
    deal(u);            //处理当前节点的答案
    res[col[u]]=max(dep[u],res[col[u]]);   //记录当前节点的贡献
}

inline void solve(){    //开始
    int n;cin>>n;init(n);
    for(int i=2;i<=n;i++){
        int x;char c;cin>>x>>c;
        g[x].push_back(i);
        g[i].push_back(x);
        mp[{min(i,x),max(i,x)}]=(1ll<<(c-'a'));
    }
    dfs1(1,0);
    dsu(1);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
}




