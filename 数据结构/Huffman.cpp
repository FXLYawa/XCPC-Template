#include <bits/stdc++.h>
using namespace std;
#define pii     pair<int,int>


struct Huffman{
    vector<vector<int>> g;
    vector<int> val;
    int root;
    Huffman(){}
    Huffman(vector<int> &_init){
        priority_queue<pii,vector<pii>,greater<pii>> q;
        int n=_init.size()-1;
        g.resize(2*n+1);int cnt=n+1;
        val=_init;val.resize(2*n+1);
        for(int i=1;i<=n;i++)q.push({_init[i],i});
        while(q.size()>=2){
            int x=q.top().first,u=q.top().second;q.pop();
            int y=q.top().first,v=q.top().second;q.pop();
            g[cnt].push_back(u);g[cnt].push_back(v);
            val[cnt]=x+y;q.push({x+y,cnt++});
        }
        root=q.top().second;
    }
    int getvalue(){
        int res=0;
        function<void(int,int)> dfs=[&](int u,int dep){
            if(g[u].empty())
            res+=dep*val[u];
            for(auto v:g[u]){
                dfs(v,dep+1);
            }
        };
        dfs(root,0);
        return res;
    }
};