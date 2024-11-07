#include <bits/stdc++.h>
using namespace std;

//Splay
template<class info>
struct Splay{
    vector<int> fa,val,cnt,siz;
    vector<array<int,2>> son;
    int tot,root;
    vector<int> lazy;//区间操作的标记
    Splay(int n){
        fa.resize(n+1);son.resize(n+1);
        cnt.resize(n+1);siz.resize(n+1);
        val.resize(n+1);tot=root=0;
    }
    void pushup(int p){siz[p]=siz[son[p][0]]+siz[son[p][1]]+cnt[p];}
    bool get(int p){return p==son[fa[p]][1];}//判断是父亲的哪个儿子
    void rotate(int p){
        int x=fa[p],y=fa[x],f=get(p);//父亲 爷爷 我是哪个儿子
        son[x][f]=son[p][f^1];
        if(son[p][f^1])fa[son[p][f^1]]=x;//更新儿子
        son[p][f^1]=x;fa[x]=p;fa[p]=y;
        if(y)son[y][x==son[y][1]]=p;
        pushup(x);pushup(p);
    }
    void splay(int p,int goal=0){
        if(!goal)root=p;
        for(int t=fa[p];(t=fa[p])!=goal;rotate(p))
            if(fa[t]!=goal)rotate(get(p)==get(t)?t:p);
    }
    void insert(const info &x){
        if(!root){
            val[++tot]=x;cnt[tot]++;root=tot;
            pushup(root);return;
        }
        int p=root,t=0;
        while(1){
            if(val[p]==x){
                cnt[p]++;pushup(p);pushup(t);
                splay(p);break;
            }
            t=p;p=son[p][val[p]<x];
            if(!p){
                val[++tot]=x;cnt[tot]++;
                fa[tot]=t;son[t][val[t]<x]=tot;
                pushup(tot);pushup(t);
                splay(tot);break;
            }
        }
    }
    bool del(const info &x){
        if(!root)return false;//空树
        queryrnk(x);//将节点splay上来
        if(val[root]!=x)return false;
        if(cnt[root]>1){
            cnt[root]--;pushup(root);
        }
        else if(!son[root][0]||!son[root][1]){
            root=son[root][0]+son[root][1];
            fa[root]=0;
        }
        else {
            int p=root,x=pre();
            fa[son[p][1]]=x;son[x][1]=son[p][1];
            pushup(root);
        }
        return true;
    }
    int queryrnk(const info &x){
        if(!root)return 1;
        int res=0,p=root;
        while(1){
            if(x==val[p])
                res+=siz[son[p][0]];
            else if(x<val[p]){
                if(son[p][0]){//有左儿子
                    p=son[p][0];
                    continue;
                }
            }
            else {
                res+=siz[son[p][0]];
                res+=cnt[p];
                if(son[p][1]){//有右儿子
                    p=son[p][1];
                    continue;
                }
            }
            splay(p);
            return res+1;
        }
    }
    info search(int k){
        int p=root;
        while(1){
            if(son[p][0]&&k<=siz[son[p][0]])
                p=son[p][0];
            else {
                k-=cnt[p]+siz[son[p][0]];
                if(k<=0){
                    splay(p);
                    return val[p];
                }
                p=son[p][1];
            }
        }
    }
    info querypre(const info &x){
        insert(x);info res=val[pre()];del(x);
        return res;
    }
    int pre(){//根节点的前驱
        int p=son[root][0];
        if(!p)return p;
        while(son[p][1])p=son[p][1];
        splay(p);return p;
    }
    info querysub(const info &x){
        insert(x);info res=val[sub()];del(x);
        return res;
    }
    int sub(){//根节点的后缀
        int p=son[root][1];
        if(!p)return p;
        while(son[p][0])p=son[p][0];
        splay(p);return p;
    }

    //区间翻转部分
    Splay(vector<info> _init){//base1  //区间翻转的初始化
        _init.push_back(info());
        int n=_init.size();
        fa.resize(n+1);son.resize(n+1);
        siz.resize(n+1);cnt.resize(n+1);
        val.resize(n+1);lazy.resize(n+1);
        tot=root=0;
        function<int(int,int,int)> build=[&](int l,int r,int f){
            if(l>r)return 0;
            int m=(l+r)/2,p=++tot;
            val[p]=_init[m],fa[p]=f,cnt[p]=1;
            son[p][0]=build(l,m-1,p);
            son[p][1]=build(m+1,r,p);
            pushup(p);return p;
        };
        root=build(0,n-1,0);
    }
    void apply(int p){swap(son[p][0],son[p][1]);lazy[p]^=1;}
    void pushdown(int p){
        if(lazy[p]){
            apply(son[p][0]);apply(son[p][1]);
            lazy[p]=0;
        }
    }
    int kth(int k){//返回第k个元素下标
        int p=root;
        while(1){
            pushdown(p);
            if(son[p][0]&&k<=siz[son[p][0]])
                p=son[p][0];
            else {
                k-=cnt[p]+siz[son[p][0]];
                if(k<=0){
                    splay(p);
                    return p;
                }
                p=son[p][1];
            }
        }
    }
    void reverse(int l,int r){
        int L=kth(l),R=kth(r+2);
        splay(L);splay(R,L);
        apply(son[son[L][1]][0]);
    }
    vector<info> getseq(){
        vector<info> res;
        function<void(int)> get=[&](int p){
            pushdown(p);//把序列输入res base1 末尾多一个元素
            if(son[p][0])get(son[p][0]);
            res.push_back(val[p]);
            if(son[p][1])get(son[p][1]);
        };
        get(root);
        return res;
    }
};