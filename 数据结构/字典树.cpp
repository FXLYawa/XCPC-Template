#include <bits/stdc++.h>
using namespace std;


struct trie{
    int mxcnt=0;
    vector<array<int,26>> tr;
    vector<int> exist;
    trie(int n){
        mxcnt=0;tr.resize(n+1);exist.resize(n+1);
    }
    void insert(string& s){
        int l=s.size();
        int p=0;int c;
        for(int i=0;i<l;i++){
            c=s[i]-'0';
            if(!tr[p][c])
                tr[p][c]=++mxcnt;
            p=tr[p][c];
        }
        exist[p]=1;
    }
    bool find(string& s){
        int l=s.size();
        int p=0;int c;
        for(int i=0;i<l;i++){
            c=s[i]-'0';
            if(!tr[p][c])return false;
            p=tr[p][c];
        }
        return exist[p];
    }
};