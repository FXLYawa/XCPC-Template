#include <bits/stdc++.h>
using namespace std;

//整数域
auto check=[&](int num){

};
int l=1,r=1e9,ans=l;
while(l<=r){
    int mid=(l+r)/2;
    if(check(mid)) l=mid+1,ans=mid;
    else r=mid-1;
}

//实数域
const double eps=1e-9;
auto check=[&](double num){

};
double l=0,r=1e12;
while((r-l)>max(1.0,l)*eps){
    double mid=(l+r)/2;
    if(check(mid))r=mid;
    else l=mid;
}

