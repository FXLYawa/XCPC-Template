#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long                      ull;


mt19937_64 rnd(time(0));

int mask=rnd();
int hs=rnd();
vector<ull> trhash;
vector<vector<int>> g;
ull shift(ull x){
    x^=mask;
    x^=x<<15;x^=x>>3;x^=x<<12;
    x=x*x*x*mask;
    return x^mask;
}
void getHash(int u,int fa){
    trhash[u]=1;//换根的时候只需要直接减去hash值
    for(auto v:g[u]){
        if(v==fa)continue;
        getHash(v,u);
        trhash[u]+=shift(trhash[v]);
    }
}
void init(int n){
    g.clear();g.resize(n+1);
    trhash.clear();trhash.resize(n+1);
    mask=rnd();hs=rnd();
}