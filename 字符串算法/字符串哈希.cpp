#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
constexpr int maxn=1000,hs=0x1F351F35;

vector<ull> re(maxn),pr(maxn);
void strhash(string &s){
    re[0]=0;pr[0]=1;
    for(int i=1;i<s.size();i++){
        re[i]=re[i-1]*hs+s[i];
        pr[i]=pr[i-1]*hs;
    }
}
ull cal(int l,int r){       //计算s[l…r]的hash
    return re[r]-re[l-1]*pr[r-l+1];
}
ull strhash1(string &s){
    int res=0;
    for(int i=0;i<s.size();i++){
        res=res*hs+s[i];
    }
    return res;
}

int hs1=131,hs2=13331;
vector<pair<ull,ull>> re1(maxn),pr1(maxn);
void strhash2(string &s){
    re1[0]={0,0};pr1[0]={1,1};
    for(int i=1;i<s.size();i++){
        re1[i].first=re1[i].first*hs1+s[i];
        re1[i].second=re1[i-1].second*hs2+s[i];
        pr1[i].first=pr1[i-1].first*hs1;
        pr1[i].first=pr1[i-1].second*hs2;
        
    }
}

pair<ull,ull> strhash3(string &s){
    int res1=0,res2;
    for(int i=0;i<s.size();i++){
        res1=res1*hs1+s[i];
        res2=res2*hs2+s[i];
        
    }
    return {res1,res2};
}