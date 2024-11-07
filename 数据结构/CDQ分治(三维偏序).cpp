#include <bits/stdc++.h>
using namespace std;
#define al(a)                                  (a).begin(),(a).end()
#define lowbit(x)                               (x&-x)
class tree_array{           //树状数组  
    public:
    vector<int> array;
    void add(int pos,int x){}
    int ask(int pos){}
};


//主体 三维偏序
struct node{
    int a,b,c,ans,cnt;
};
bool cmp(node x,node y){
    if(x.b==y.b)return x.c<y.c;
    else return x.b<y.b;
}
vector<node> a;//初始已经按a排序完
tree_array cnt;//树状数组
void CDQ(int l,int r){//分治区间
    if(l==r)return;
    int m=(l+r)/2;
    CDQ(l,m);//计算左区间 
    CDQ(m+1,r);//右区间
    sort(a.begin()+l,a.begin()+m+1,cmp);
    sort(a.begin()+m+1,a.begin()+r+1,cmp);
    int i=m+1,j=l;
    for(;i<=r;i++){//用左边的结果计算右边
        while(a[j].b<=a[i].b&&j<=m){
            cnt.add(a[j].c,a[j].cnt);
            j++;
        }
        a[i].ans+=cnt.ask(a[i].c);
    }
    for(int k=l;k<j;k++)cnt.add(a[k].c,-a[k].cnt);
}

