#include <bits/stdc++.h>
using namespace std;


template<typename T>
class ST{//最大值
public:
    vector<vector<T>> st;
    vector<int> lg;
    int n;
    ST(vector<T>& a){
        n=a.size()-1;lg.resize(n+1);
        for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
        st.resize(n+1,vector<T>(lg[n]+1));
        for(int i=1;i<=n;i++)st[i][0]=a[i];
        for(int j=1;j<=lg[n];j++)
            for(int i=1;i<=n-(1<<j)+1;i++)
                st[i][j]=cmp(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
    T& ask(int l,int r){
        int t=lg[r-l+1];
        return cmp(st[l][t],st[r-(1<<t)+1][t]);
    }
    T& cmp(T &a,T &b){return a>b?a:b;}
};