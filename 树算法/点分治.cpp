#include <bits/stdc++.h>
using namespace std;
constexpr int INF = 0x7f7f7f7f;

// 我们在点分治过程中每次选取子树的重心为子树的树根进行处理，
// 这样总的递归深度不会超过logN层，整个点分治的时间复杂度也就保证了O(NlogN)
// 点分治题的思想大都如上， 对于不同的题要设计不同的calc函数
//洛谷P3806 给定一棵有n个点的树，询问树上距离为k的点对是否存在。
//第一行两个数n,m。第2到第n行，每行三个整数 u,v,w，代表树上存在一条连接u和v边权w 的路径。
//接下来m行，每行一个整数k，代表一次询问

struct edge{int v,w;};
vector<vector<edge>> g;
vector<int> siz,maxp,vis,re,dis,query,test;
map<int,int> judge;
int sum,rt,m;//m是询问总数
void init(int n,int m){
    g.clear();g.resize(n+1);
    siz.clear();siz.resize(n+1);//子树大小
    maxp.clear();maxp.resize(n+1);//u的最大的子树大小
    vis.clear();vis.resize(n+1);//该节点是否计算过
    re.clear();re.resize(n+1);//记录存在的dis
    dis.clear();dis.resize(n+1);//记录每个点到根的距离
    test.clear();test.resize(n+1);//记录每个询问的答案
    query.clear();query.resize(m+1);//记录所有询问
    judge.clear();//记录有那些dis
    rt=sum=0;//以u为根的子树大小，当前的根
}
//找到当前树的重心,作为根节点
void getroot(int u,int fa){
    siz[u]=1;maxp[u]=0;
    for(auto e:g[u]){
        int v=e.v;
        if(v==fa||vis[v])continue;
        getroot(v,u);
        siz[u]+=siz[v];
        maxp[u]=max(maxp[u],siz[v]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt])rt=u;//maxp最小的点即为重心
} 
//计算每个点到当前根的距离
void getdis(int u,int fa){
    re[++re[0]]=dis[u];
    for(auto e:g[u]){
        int v=e.v;
        if(v==fa||vis[v])continue;
        dis[v]=dis[u]+e.w;
        getdis(v,u);
    }
}
void calc(int u){
    for(auto e:g[u]){
        int v=e.v;
        if(vis[v])continue;
        re[0]=0;dis[v]=e.w;
        getdis(v,u);//处理u的每个子树的dis
        for(int i=re[0];i;i--)//遍历当前子树的dis
            for(int j=1;j<=m;j++)//遍历每个询问
                if(query[j]>=re[i]&&judge.count(query[j]-re[i]))
                    test[j]=1;
        //如果query[k]-rem[j]d的路径存在就标记第k个询问
        for(int i=re[0];i;i--)judge[re[i]]=1;//保存出现过的dis于judge
    }
    judge.clear();//处理完这个子树就清空judge(注意清空的时间复杂度)
}
void work(int u){
    //judge[i]表示到根距离为i的路径是否存在
    vis[u]=judge[0]=1;calc(u);//处理以u为根的子树
    for(auto e:g[u]){//对每个子树进行分治
        int v=e.v;
        if(vis[v])continue;
        sum=siz[v];maxp[rt=0]=INF;//注意sum是以v为根的子树大小
        getroot(v,0);work(rt);//在子树中找重心并递归处理
    }
}
inline void solve(){
    int n;cin>>n>>m;init(n,m);
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    for(int i=1;i<=m;i++)cin>>query[i];
    maxp[rt]=sum=n;
    getroot(1,0);work(rt);
    for(int i=1;i<=m;i++)cout<<(test[i]?"AYE":"NAY")<<endl;
}



