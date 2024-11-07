#include <bits/stdc++.h>
using namespace std;


//可持久化权值线段树(主席树)   查询区间第k小模板
struct LastingSegmentTree{
    int L,R,cnt,rt;
    vector<int> root;
    vector<int> tree;
    vector<int> lson,rson;
    LastingSegmentTree(int l,int r,int n){//n是操作总数
        int m=n*(log(r-l+1)/log(2)+3);
        root.resize(n+5);tree.resize(m+1);
        lson.resize(m+1);rson.resize(m+1);
        L=l,R=r,cnt=1,rt=0,root[0]=1;
    }
    void create(int p){
        if(!lson[p])lson[p]=++cnt;
        if(!rson[p])rson[p]=++cnt;
    }
    void pushup(int p){//用子节点维护父节点 注意lazy标记的值
        tree[p]=tree[lson[p]]+tree[rson[p]];
    }
    //单点修改
    void modify(int x,const int &v,int p,int now,int l,int r){
        if(l==r){
            tree[now]+=v;
            return;
        }
        int m=(l+r)/2;
        create(p);
        if(x<=m){
            rson[now]=rson[p];
            lson[now]=++cnt;tree[cnt]=tree[lson[p]];
            modify(x,v,lson[p],lson[now],l,m);
        }
        else{
            lson[now]=lson[p];
            rson[now]=++cnt;tree[cnt]=tree[rson[p]];
            modify(x,v,rson[p],rson[now],m+1,r);
        }
        pushup(now);
    }
    void modify(int x,const int &v){//版本号 位置 值
        root[++rt]=++cnt;
        modify(x,v,root[rt-1],root[rt],L,R);
    }
    //区间询问 query（l，r）;
    int query(int x,int y,int l,int r,int k){
        int m=(l+r)/2,d=tree[lson[y]]-tree[lson[x]];
        if(l==r)return l;
        if(d>=k)return query(lson[x],lson[y],l,m,k);
        else return query(rson[x],rson[y],m+1,r,k-d);
    }
    int query(int l,int r,int k){//询问操作不增加节点
        return query(root[l-1],root[r],L,R,k);
    }
};


//可持久化数组
template<class info>
struct LastingArray{
    int L,R,cnt,rt;
    vector<info> tree;
    vector<int> root;
    vector<int> lson,rson;
    LastingArray(){}
    LastingArray(int l,int r,int m){init(l,r,m);}
    LastingArray(const vector<info> &_init,int m){//base1
        init(1,_init.size(),m);
        function<void(int,int,int)> build=[&](int p,int l,int r){//建树，[l,r]对应节点为p
            if(l==r){
                tree[p]=_init[l];
                return;
            }
            create(p);
            int m=(l+r)/2;
            build(lson[p]=++cnt,l,m);
            build(rson[p]=++cnt,m+1,r);
            pushup(p);
        };
        build(root[0]=++cnt,L,R);
    }
    void init(int l,int r,int m){
        int n=m*(log(r-l+1)/log(2)+3)+4*(r-l+1);
        tree.resize(n+1);root.resize(m+1);
        lson.resize(n+1);rson.resize(n+1);
        L=l,R=r,cnt=0,rt=0;
    }
    void create(int p){
        if(!lson[p])lson[p]=++cnt;
        if(!rson[p])rson[p]=++cnt;
    }
    void pushup(int p){//用子节点维护父节点 注意lazy标记的值
        tree[p]=tree[lson[p]]+tree[rson[p]];
    }
    //单点修改
    void modify(int x,const int &v,int p,int now,int l,int r){
        if(l==r){
            tree[now]=v;
            return;
        }
        int m=(l+r)/2;
        create(p);
        if(x<=m){
            rson[now]=rson[p];
            lson[now]=++cnt;tree[cnt]=tree[lson[p]];
            modify(x,v,lson[p],lson[now],l,m);
        }
        else{
            lson[now]=lson[p];
            rson[now]=++cnt;tree[cnt]=tree[rson[p]];
            modify(x,v,rson[p],rson[now],m+1,r);
        }
        pushup(now);
    }
    void modify(int x,int board,const int &v){
        root[++rt]=++cnt;
        modify(x,v,root[board],root[rt],L,R);
    }
    //单点查询
    int query(int x,int p,int l,int r){
        if(l==r)return tree[p];
        int m=(l+r)/2;
        if(x<=m)return query(x,lson[p],l,m);
        else return query(x,rson[p],m+1,r);
    }
    int query(int x,int board){
        root[++rt]=++cnt;
        lson[cnt]=lson[root[board]];rson[cnt]=rson[root[board]];
        return query(x,root[rt],L,R);
    }
};