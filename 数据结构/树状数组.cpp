#include <bits/stdc++.h>
using namespace std;

#define lowbit(x)       (x&-x)
//维护满足结合律并且 知道x（）y 和x 可以推出y是多少的运算
//多组数据可以考虑时间戳优化 当时间戳和当前时间相同
//则使用当前数据，否则认为这个数据为空
//(避免暴力清空导致的高时间复杂度)
struct tree_array{           //树状数组 0号位置始终为0；     
    int n;vector<int> array;
    tree_array(int n):array(n+1),n(n){}
    void add(int pos,int x){        //单点修改       //O(logn)
        for(;pos<=n;pos+=lowbit(pos))
            array[pos]+=x; //维护信息 要根据维护的信息特点
    }
    int ask(int pos){    //获取0……pos的信息
        int ans=0;          //O(logn)
        for(;pos;pos-=lowbit(pos))
            ans+=array[pos];         //要根据维护信息修改
        return ans;
    }
};

struct tree_array_2D{           //二维树状数组 0号位置始终为0；     
    int n;vector<vector<int>> array; //int array[n+1][n+1]
    tree_array_2D(int n):array(n+1,vector<int>(n+1)),n(n){}
    void add(int x,int y,int a){        //(x,y) +a  单点修改    //O(logn)
        for(int i=x;i<=n;i+=lowbit(i))
            for(int j=y;j<=n;j+=lowbit(j))
                array[i][j]+=x;  //维护信息 要根据维护的信息特点
    }

    int ask(int x,int y){    //获取(0,0)……(x,y)的信息
        int ans=0;          //O(logn)
        for(int i=x;i;i-=lowbit(i))
            for(int j=y;j;j-=lowbit(j))
            ans+=array[i][j];      //要根据维护信息修改
        return ans;
    }
};


namespace build{    //仅考虑一维，二维可简单拓展
    int add(int pos,int x);

    const int n=1000;
    vector<int> array(n);

    //对每个点进行一次add操作    //O(nlogn)
    void buildA(vector<int> &a){  
        array[0]=0;
        for(int i=1;i<=n;i++){add(i,a[i]);}
    }

    void buildB(vector<int> &a){    //考虑每次更新儿子时 都对父亲做一次贡献     //O(n)
        for(int i=1;i<=n;i++){
            array[i]+=a[i];     //更新方法和维护数据有关
            int j=i+lowbit(i);
            if(j<=n)array[j]+=array[i]; //更新方法和维护数据有关
        }
    }

    vector<int> t;      //预处理数组
    void buildC(vector<int> &a){    //用预处理数组更新    //O(n)
        for(int i=1;i<=n;i++){
            array[i]=t[i]-t[i-lowbit(i)];  //更新方法和维护数据有关
        }
    }
}



