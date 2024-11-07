#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(string s){ //base0
    int n=s.size();
    vector<int> nxt(n+1);
    for(int i=1,j=0;i<n;i++){
        while(j&&s[i]!=s[j])j=nxt[j];
        j+=(s[i]==s[j]);
        nxt[i+1]=j;
    }
    return nxt;
}