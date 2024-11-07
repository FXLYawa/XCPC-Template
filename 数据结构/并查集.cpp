#include <bits/stdc++.h>

using namespace std;

const int N=1000;
//并查集        下标从1开始
vector<int> fa;         //父节点
vector<int> ele;           //元素

//初始化一个长度为n的并查集
void init(int n){       
    fa.resize(n+1); 
    for(int i=0;i<=n;i++){
        fa[i]=i;
    }
};

    
int findA(int pos){  //找爹  递归实现
    if(fa[pos]==pos)return pos;
    return fa[pos]=findA(fa[pos]);
}

void mergeA(int i,int j){     //普通合并    
    int fx=findA(i),fy=findA(j);
    if(fx!=fy){fa[fx]=fy;}  
}


vector<int>  r;       //节点的秩
int findB(int pos){  //找爹  递归实现  不进行路径压缩  保持树的结构
    if(fa[pos]==pos)return pos;
    return findB(fa[pos]);
}

void mergeB(int i,int j){     //启发式合并     
    int fx=findB(i),fy=findB(j);
    if(r[fx]>r[fy])fa[fy]=fx;
    else if(r[fx]>r[fy])fa[fx]=fy;
    else{/*rank[fx]=rank[fy]*/ 
        fa[fy]=fx;
        ++r[fx];
    }
}


vector<int> weight;      //节点的权
int findC(int pos){  //找爹  递归实现 带权
    if(fa[pos]==pos)return pos;
    else{
        int t=fa[pos];
        fa[pos]=findC(fa[pos]);     //记录与根节点的权值
        weight[pos]+=weight[t];     //当前节点的权值加上原本父节点的权值 
        return fa[pos];
    }
}

void mergeC(int i,int j,int s){     //带权合并  s为边（i，j）的权值
    int fx=findC(i),fy=findC(j);
    if(fx!=fy){
        fa[fx]=fy;
		weight[fx]=s+weight[j]-weight[i];
    }
}
