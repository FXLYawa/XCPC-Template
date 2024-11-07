#include <bits/stdc++.h>

using namespace std;

/***********************************************/
//区间加 乘 求和
// const int mod = 1e9 + 7;
// struct info{
//     int mx,sz;
// };
// struct node {
//     int mul = 1, add = 0;
// };
// using tag=node;
// info operator+(const info &a, const info &b){
//     return {(a.mx + b.mx) % mod, a.sz + b.sz};
// }

// tag operator + (const tag &a,const tag &b) {
//     return {(a.mul * b.mul) % mod,(a.add * b.mul + b.add) % mod};
// }

// void apply(info &x, tag &a, tag f){
//     x.mx = (x.mx * f.mul + x.sz * f.add) % mod;
//     a = a + f;
// }

//设计取模的话query函数要修改一下
// info query(int x, int y,int p, int l, int r){
//         if (y<l|| r < x){
//             return info();
//         }
//         if (x <= l && r <= y){
//             return tree[p];
//         }
//         int m = (l + r) / 2;
//         push(p);
//         auto ans = query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
//         ans.mx %= mod;
//         return ans;
// }
/***********************************************/
//区间最值以及区间最值个数
// struct info{
//     int mx = INF;
//     int cnt = 0;
// };

// using tag = int;

// info operator+(const info &a, const info &b){
//     int mx = min(a.mx, b.mx);
//     int cnt = 0;
//     if(a.mx == mx) cnt += a.cnt;
//     if(b.mx == mx) cnt += b.cnt;
//     return {mx, cnt};
// }
/***********************************************/
//单点修改， 区间修改，最大值查询：
// struct info{
//     int mx = -INF;
// };

// using tag = int;

// info operator+(const info &a, const info &b){
//     return {max(a.mx, b.mx)};
// }

// void apply(info &x, tag &a, tag f){
//     x.mx += f;
//     a += f;
// }
/***********************************************/

struct info{//节点信息
    int mx;
};

struct node{//标签
    
};
using tag=node;
info operator+(const info &a,const info &b){

}
tag operator+(const tag &a,const tag &b){

}
//将标记f放置到标记a上并且把改标签影响传递到x上
void apply(info &x,tag &a,tag f){
    //x+=f;把f的影响放到x上
    //a+=f;把f的影响放到a上
}

//单点修改线段树，区间查询
template<class info>//info 维护的信息  base0
struct SegmentTree{
    int n;
    vector<info> tree;
    SegmentTree(){}//初始化空树
    SegmentTree(int n,info _init=info()){//下面参数为n+1则base1
        init(vector<info>(n,_init));//初始化成info成_init
    }
    SegmentTree(const vector<info> &_init){init(_init);}

    void init(const vector<info> &_init){
        n=(int)_init.size();//减1则base1
        tree.assign((n<<2)+1,info());//开4倍大小，先初始化成默认值
        function<void(int, int, int)> build=[&](int p,int l,int r){//建树，[l,r]对应节点为p
            if(l==r){
                tree[p]=_init[l-1];//删去减1则base0
                return;
            }
            int m=(l+r)/2;
            build(2*p,l,m);
            build(2*p+1,m+1,r);
            pushup(p);
        };
        build(1,1,n);
    }

    void pushup(int p){//用子节点维护父节点
        tree[p]=tree[2*p]+tree[2*p+1];
    }
    //单点修改，将下标为pos的数据修改成v
    void modify(int x,const info &v,int p,int l,int r){
        if(l==r){//到根节点  按需修改
            tree[p]=v;
            return;
        }
        int m=(l+r)/2;
        if(x<=m){//左节点
            modify(x,v,2*p,l,m);
        }
        else{//右节点
            modify(x,v,2*p+1,m+1,r);
        }
        pushup(p);
    }
    void modify(int x,const info &v){
        modify(x,v,1,1,n);
    }
    //区间询问 query（l，r）;
    info query(int x,int y,int p,int l,int r){
        if(y<l||r<x){//该区间不在询问区间内，返回空值
            return info();
        }
        if (x<=l&&r<=y){//该区间包含在询问区间，返回信息
            return tree[p];
        }
        int m=(l+r)/2;
        return query(x,y,2*p,l,m)+query(x,y,2*p+1,m+1,r);
    }
    info query(int l,int r){
        return query(l,r,1,1,n);
    }
};
template<class info,class tag>
struct LazySegmentTree{//base1
    int n;
    vector<info> tree;
    vector<tag> lazy;
    LazySegmentTree(){}//初始化空树
    LazySegmentTree(int n,info _init=info()){//下面参数为n则base0
        init(vector<info>(n,_init));//初始化成info成_init
    }
    LazySegmentTree(const vector<info> &_init){init(_init);}

    void init(const vector<info> &_init){
        n=(int)_init.size();//减1则base1
        tree.assign((n<<2)+1,info());//开4倍大小，先初始化成默认值
        lazy.assign((n << 2) + 1, tag());
        function<void(int,int,int)> build=[&](int p,int l,int r){//建树，[l,r]对应节点为p
            if(l==r){
                tree[p]=_init[l-1];//删去减1则base0
                return;
            }
            int m=(l+r)/2;
            build(2*p,l,m);
            build(2*p+1,m+1,r);
            pushup(p);
        };
        build(1,1,n);
    }
    void apply(int p,const tag &v){//在p节点放置lazy标记
        ::apply(tree[p],lazy[p],v);
    }
    void pushup(int p){//用子节点维护父节点 注意lazy标记的值
        tree[p]=tree[2*p]+tree[2*p+1];
    }
    void pushdown(int p){//下放lazy标记
        apply(2*p,lazy[p]);
        apply(2*p+1,lazy[p]);
        lazy[p]=tag();//标记下放，并删去该节点的标记
    }
    //单点修改
    void modify(int x,const info &v,int p,int l,int r){
        if(l==r){
            tree[p]=v;
            return;
        }
        int m=(l+r)/2;
        pushdown(p);
        if(x<=m){
            modify(x,v,2*p,l,m);
        }
        else{
            modify(x,v,2*p+1,m+1,r);
        }
        pushup(p);
    }
    void modify(int x,const info &v){
        modify(x,v,1,1,n);
    }
    
    //区间修改，将[x,y]的值修改为v
    void modify(int x,int y,const tag &v,int p,int l,int r){
        if(y<l||r<x){//该区间不在修改区间内，无需修改
            return ;
        }
        if (x<=l&&r<=y){//该区间包含在修改区间，放置lazy标记
            apply(p,v);
            return ;
        }
        int m=(l+r)/2;
        pushdown(p);//下放标记
        modify(x,y,v,2*p,l,m);
        modify(x,y,v,2*p+1,m+1,r);
        pushup(p);//维护当前节点
    }
    void modify(int x,int y,const tag &v){
        modify(x,y,v,1,1,n);
    }
    //区间询问 query（l，r）;
    info query(int x,int y,int p,int l,int r){
        if(y<l||r<x){//该区间不在询问区间内，返回空值
            return info();
        }
        if(x<=l&&r<=y){//该区间包含在询问区间，返回信息
            return tree[p];
        }
        int m=(l+r)/2;
        pushdown(p);//要往下查询，所以下放标记
        return query(x,y,2*p,l,m)+query(x,y,2*p+1,m+1,r);
    }
    info query(int x,int y){
        return query(x,y,1,1,n);
    }
};


template<class info,class tag>
struct DLazySegmentTree{
    int L,R;
    vector<info> tree;
    vector<tag> lazy;
    vector<int> lson,rson;
    DLazySegmentTree(){}
    DLazySegmentTree(int l,int r){init(l,r);}
    DLazySegmentTree(const vector<info> &_init){//base1
        init(1,_init.size());
        for(int i=L;i<=R;i++)modify(i,_init[i]);
    }
    int build(){
        tree.push_back(info());lazy.push_back(tag());
        lson.push_back(0);rson.push_back(0);
        return (int)tree.size()-1;
    }
    void init(int l,int r){
        L=l,R=r;build();build();
    }
    void apply(int p,const tag &v){//在p节点放置lazy标记
        ::apply(tree[p],lazy[p],v);
    }
    void pushup(int p){//用子节点维护父节点 注意lazy标记的值
        tree[p]=tree[lson[p]]+tree[rson[p]];
    }
    void pushdown(int p){//下放lazy标记
        if(!lson[p])lson[p]=build();apply(lson[p],lazy[p]);
        if(!rson[p])rson[p]=build();apply(rson[p],lazy[p]);
        lazy[p]=tag();//标记下放，并删去该节点的标记
    }
    //单点修改
    void modify(int x,const info &v,int p,int l,int r){
        if(l==r){
            tree[p]=v;
            return;
        }
        int m=(l+r)/2;
        pushdown(p);
        if(x<=m){
            modify(x,v,lson[p],l,m);
        }
        else{
            modify(x,v,rson[p],m+1,r);
        }
        pushup(p);
    }
    void modify(int x,const info &v){
        modify(x,v,1,L,R);
    }
    
    //区间修改，将[x,y]的值修改为v
    void modify(int x,int y,const tag &v,int p,int l,int r){
        if(y<l||r<x){//该区间不在修改区间内，无需修改
            return ;
        }
        if (x<=l&&r<=y){//该区间包含在修改区间，放置lazy标记
            apply(p,v);
            return ;
        }
        int m=(l+r)/2;
        pushdown(p);//下放标记
        modify(x,y,v,lson[p],l,m);
        modify(x,y,v,rson[p],m+1,r);
        pushup(p);//维护当前节点
    }
    void modify(int x,int y,const tag &v){
        modify(x,y,v,1,L,R);
    }
    //区间询问 query（l，r）;
    info query(int x,int y,int p,int l,int r){
        if(!p)return info();//节点为空，则没有值
        if(y<l||r<x){//该区间不在询问区间内，返回空值
            return info();
        }
        if(x<=l&&r<=y){//该区间包含在询问区间，返回信息
            return tree[p];
        }
        int m=(l+r)/2;
        pushdown(p);//要往下查询，所以下放标记
        return query(x,y,lson[p],l,m)+query(x,y,rson[p],m+1,r);
    }
    info query(int x,int y){
        return query(x,y,1,L,R);
    }
};