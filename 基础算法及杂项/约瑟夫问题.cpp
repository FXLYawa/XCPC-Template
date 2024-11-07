#include <bits/stdc++.h>
using namespace std;

int josephus(int n,int m,int k) { //n
  int res = 0;
  for(int i=1;i<=m;++i)res=(res+k)%m;
  return res;
}


int josephus(int n,int m,int k) {// klogn   n总人数  m找第m个出列的  报到k出列
    if(k==1)return (m-1)%n;
    if(m==1)return k-1;
    if(m>=k)return (josephus(n-1,m,k-1)+m)%n;
    int q=min(k-1,n/m),p=josephus(n-q,m,k-q)+q*m-n;
    return p<0?p+n:p+p/(m-1);
}