#include <bits/stdc++.h>

using namespace std;

vector<int> Eratosthenes(int n){
    vector<int> a(n+1,0);a[0]=1;a[1]=1;vector<int> out;
    for(int i=0;i<=n;i++){
        if(a[i])continue;
        out.push_back(i);
        for(int j=i;j<=n/i;j++)a[i*j]=1;
    }
    return out;
}//埃氏筛
vector<int> Euler(int n){
    vector<int> a(n+1,0);a[0]=1;a[1]=1;vector<int> out;
    for(int i=2;i<=n;i++){
        if(!a[i]){a[i]=i;out.push_back(i);}
        for(int j=0;j<out.size();j++){
            if(out[j]>a[i]||out[j]>n/i)break;
            a[i*out[j]]=out[j];
        }
    }
    return out;
}//欧拉筛