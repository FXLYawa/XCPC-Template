#include <bits/stdc++.h>

using namespace std;


//计算a^b%p
int power(int a,int b,int p){
    int ans=1%p;
    for(;b;b>>=1){
        if(b&1)ans=(long long)ans*a%p;
        a=(long long)a*a%p;
    }
    return ans;
}