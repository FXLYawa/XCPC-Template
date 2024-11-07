#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct chunked_array{//base 0
    struct stu{int add,sum;};//状态
    vector<vector<T>> a;    //分块
    vector<stu> re;         //记录分块状态
    int n,m;//n总数居量  m每个分块数据量
    void init(int nn){
        n=nn;a.clear();re.clear();m=sqrt(nn);
    }
    void read(vector<T> &data){
        for(int i=0;i<n;i++){       //分块读入
            if(i%m==0)a.push_back({});
            a[i/m].push_back(data[i]);
        }
        re.resize(a.size());
        for(int i=0;i<a.size();i++){//维护初始状态
            re[i].add=0,re[i].sum=0;
            for(int j=0;j<a[i].size();j++){
                re[i].sum+=a[i][j];//跑分块内部处理
            }
        }
    }
    int perf(int l,int r){
        l--;r--;//注意如果有区间加等操作 分块内部要加入分块全局信息
        int i=l,ans=0;
        while(i<=r){//i在分块的编号是a[i/m][i%m]  对应分块是re[i%m]
            if(i%m==0&&i+m-1<=r){//进入分块i/m 
                i+=m;//查询一个块
            }
            else{
                i++;//查询边界两个块边界
            }
        }
    }
};