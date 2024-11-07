#include <bits/stdc++.h>

using namespace std;


string minexp(string s){                        //str min expression
    int n=s.length();s=s+s;
    int i=0,j=1;
    while(i<n&&j<n){
        int k=0;
        while(s[i+k]==s[j+k])k++;
        if(k==n)return s.substr(min(i,j)+k,n);
        else if(s[i+k]>s[j+k]){
            i=i+k+1;
            if(i==j)i++;
        }
        else{
            j=j+k+1;
            if(i==j)j++;
        }
    }
    return s.substr(min(i,j),n);
}