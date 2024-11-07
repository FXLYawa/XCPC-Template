#include <bits/stdc++.h>
using namespace std;

//有旋Treap(Tree+Heap)
template<class info>
struct Treap {  //小根堆
    vector<int> lson,rson,rnk,siz,cnt;
    vector<info> val;
    int root,tot;
    Treap(int n){
        lson.resize(n+1);rson.resize(n+1);
        siz.resize(n+1);cnt.resize(n+1);
        rnk.resize(n+1);val.resize(n+1);
        root=0;tot=0;
    }
    void pushup(int p){siz[p]=siz[lson[p]]+siz[rson[p]]+cnt[p];}
    void lrotate(int &p){
        int t=rson[p];
        rson[p]=lson[t];lson[t]=p;//旋转
        pushup(p);pushup(t);//更新大小
        p=t;
    }
    void rrotate(int &p){
        int t=lson[p];
        lson[p]=rson[t];rson[t]=p;
        pushup(p);pushup(t);
        p=t;
    }
    void insert(const info &x){insert(x,root);}
    void insert(const info &x,int &p){    //插入x
        if(!p){    //新增一个节点
            p=++tot;
            siz[p]=cnt[p]=1;
            val[p]=x;rnk[p]=rnd();
            return;
        }
        if(val[p]==x)cnt[p]++;
        else if(val[p]<x){
            insert(x,rson[p]);
            if(rnk[p]>rnk[rson[p]])lrotate(p);
        }
        else {
            insert(x,lson[p]);
            if(rnk[p]>rnk[lson[p]])rrotate(p);
        }
        pushup(p);
    }
    bool del(const info &x){return del(x,root);}
    bool del(const info &x,int &p){//删除权值为x的节点
        if(!p)return false;
        bool flag=false;
        if(val[p]<x)flag=del(x,rson[p]);
        else if(val[p]>x)flag=del(x,lson[p]);
        else{
            if(cnt[p]>1){//删除相同元素
                cnt[p]--;siz[p]--;
                return true;//若节点非空则无需操作
            }
            if(!lson[p]||!rson[p]){
                p=lson[p]+rson[p];
                return true;//若有一个子树为空，直接把子树接上
            }
            if(rnk[lson[p]]<rnk[rson[p]])rrotate(p);
            else lrotate(p);
            flag=del(x,p);//旋转结束重新进入节点判断
        }
        pushup(p);
        return flag;
    }
    int queryrnk(const info &x){return queryrnk(x,root);}
    int queryrnk(const info &x,int p){//查找x的排名
        if(!p)return 1;
        if(val[p]==x)
            return siz[lson[p]]+1;
        else if(x>val[p])
            return siz[lson[p]]+cnt[p]+queryrnk(x,rson[p]);
        else 
            return queryrnk(x,lson[p]);
    }
    info search(int k){return search(k,root);}
    info search(int k,int p){//查询排名为k的元素
        if(!p)return info();
        if(k<=siz[lson[p]])
            return search(k,lson[p]);
        else if(k>siz[lson[p]]+cnt[p])
            return search(k-siz[lson[p]]-cnt[p],rson[p]);
        else return val[p];
    }
    //info querypre(const info &x){return search(queryrnk(x)-1);}
    info querypre(const info &x){return val[querypre(x,root)];}
    int querypre(const info &x,int p,int ans=0){
        if(!p)return ans;//搜索x的前驱，返回其在val数组中的位置
        if(val[p]<x)
            return querypre(x,rson[p],p);
        else 
            return querypre(x,lson[p],ans);
    }
    //info querysub(const info &x){return search(queryrnk(x+1));}
    info querysub(const info &x){return val[querysub(x,root)];}
    int querysub(const info &x,int p,int ans=0){
        if(!p)return ans;//搜索x的后继，返回其在val数组中的位置
        if(val[p]>x)
            return querysub(x,lson[p],p);
        else 
            return querysub(x,rson[p],ans);
    }
};


//无旋Treap(Tree+Heap)
template<class info>
struct Treap {  //小根堆
    vector<int> lson,rson,rnk,siz;
    vector<info> val;
    int root,tot;
    Treap(int n){
        lson.resize(n+1);rson.resize(n+1);
        rnk.resize(n+1);val.resize(n+1);
        siz.resize(n+1);root=0;tot=0;
    }
    void pushup(int p){siz[p]=siz[lson[p]]+siz[rson[p]]+1;}
    pair<int,int> split(const info &x,int p){//<=x的放在左树
        if(!p)return {0,0};
        if(val[p]<=x){
            pair<int,int> t=split(x,rson[p]);
            rson[p]=t.first;pushup(p);
            return {p,t.second};
        }
        else{
            pair<int,int> t=split(x,lson[p]);
            lson[p]=t.second;pushup(p);
            return {t.first,p};
        }
    }
    pair<int,int> split_by_rnk(int k,int p){//把前k个值分入左树
        if(!p)return {0,0};
        if(siz[lson[p]]<k){
            pair<int,int> t=split_by_rnk(k-siz[lson[p]]-1,rson[p]);
            rson[p]=t.first;pushup(p);
            return {p,t.second};
        }
        else{
            pair<int,int> t=split_by_rnk(k,lson[p]);
            lson[p]=t.second;pushup(p);
            return {t.first,p};
        }
    }
    int merge(pair<int,int> t){return merge(t.first,t.second);}
    int merge(int u,int v){
        if(!u||!v)return u+v;
        if(rnk[u]<rnk[v]){
            rson[u]=merge(rson[u],v);
            pushup(u);return u;
        }
        else{
            lson[v]=merge(u,lson[v]);
            pushup(v);return v;
        }
    }
    void insert(const info &x){    //插入x
        val[++tot]=x;rnk[tot]=rnd();siz[tot]=1;//新建节点
        pair<int,int> t=split(x,root);
        root=merge(merge(t.first,tot),t.second);
    }
    void del(const info &x){//删除权值为x的节点
        pair<int,int> a,b;
        a=split(x,root);b=split(x-1,a.first);//比x小的第一个值
        b.second=merge(lson[b.second],rson[b.second]);//删除一个值
        root=merge(merge(b),a.second);
    }
    //另一种实现和有旋Treap一样
    int queryrnk(const info &x){//查找x的排名
        pair<int,int> t=split(x-1,root);//比x小的第一个值
        int res=siz[t.first]+1;
        root=merge(t);
        return res;
    }
    info search(int k){//查询排名为k的元素
        pair<int,int> a,b;
        a=split_by_rnk(k,root);
        b=split_by_rnk(k-1,a.first);
        root=merge(merge(b),a.second);
        return val[b.second];
    }
    info querypre(const info &x){return search(queryrnk(x)-1);}
    info querysub(const info &x){return search(queryrnk(x+1));}

    //区间操作部分 （文艺平衡树）  要给split和merge函数增加pushdown
    vector<int> lazy;
    Treap(vector<info> _init){//base1  //区间翻转的初始化
        _init.push_back(info());
        int n=_init.size();
        lson.resize(n+1);rson.resize(n+1);
        val.resize(n+1);rnk.resize(n+1);
        lazy.resize(n+1);siz.resize(n+1);
        tot=root=0;
        function<int(int,int)> build=[&](int l,int r){
            if(l>r)return 0ll;
            int m=(l+r)/2,p=++tot;
            val[p]=_init[m],rnk[p]=rnd();
            lson[p]=build(l,m-1);
            rson[p]=build(m+1,r);
            pushup(p);return p;
        };
        root=build(0,n-1);
    }
    void apply(int p){swap(lson[p],rson[p]);lazy[p]^=1;}
    void pushdown(int p){
        if(!lazy[p])return;
        apply(lson[p]);apply(rson[p]);
        lazy[p]=0;
    }
    void reverse(int l,int r){
        pair<int,int> a,b;
        a=split_by_rnk(l,root);
        b=split_by_rnk(r-l+1,a.second);
        apply(b.first);
        root=merge(a.first,merge(b));
    }
    vector<info> getseq(){
        vector<info> res;
        function<void(int)> get=[&](int p){
            pushdown(p);//把序列输入res base1 末尾多一个元素
            if(lson[p])get(lson[p]);
            res.push_back(val[p]);
            if(rson[p])get(rson[p]);
        };
        get(root);
        return res;
    }
};


// //前缀和询问排名
// int queryrnk(const info &x,int p){//查找x的排名
//     if(!p)return 1;
//     if(x<=sum[lson[p]])
//         return queryrnk(x,lson[p]);
//     else if(x>sum[lson[p]]+val[p]*cnt[p])
//         return siz[lson[p]]+cnt[p]+queryrnk(x-sum[lson[p]]-val[p]*cnt[p],rson[p]);
//     else 
//         return siz[lson[p]]+x/val[p]+1;
// }

