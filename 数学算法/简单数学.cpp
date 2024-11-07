#include <bits/stdc++.h>

using namespace std;


int gcd(int a,int b){
    int k;
    while(k=a%b){
        a=b;b=k;
    }
    return b;
}

int lcm(int a,int b){
    return a/gcd(a,b)*b;
}