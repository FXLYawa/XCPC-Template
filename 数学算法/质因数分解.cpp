#include <bits/stdc++.h>

using namespace std;
vector<int> pr;
//分解质因数 x=(p1^c1)*(p2^c2)*……*(pn^cn)
vector<pair<int,int>> Prime_fac(int num){    
    vector<pair<int,int>> pf;
    // for(int i=2;i<=num/i;i++){    //暴力
    for(auto i:pr){
        if(i>num/i)break;
        if(num%i==0){
            int cnt=0;
            while(num%i==0){
                num/=i;cnt++;
            }
            pf.push_back({i,cnt});
        }
    }
    if(num!=1)pf.push_back({num,1});
    return pf;
}