#include <bits/stdc++.h>
using namespace std;
constexpr int maxn=100000;
int mxcnt=0;
int trie[maxn][26]; 
int exist[maxn];
void insert(string& s){
    int l=s.size();
    int p=0;int c;
    for(int i=0;i<l;i++){
        c=s[i]-'0';
        if(!trie[p][c])
            trie[p][c]=++mxcnt;
        p=trie[p][c];
    }
    exist[p]=1;
}
bool find(string& s){
    int l=s.size();
    int p=0;int c;
    for(int i=0;i<l;i++){
        c=s[i]-'0';
        if(!trie[p][c])return false;
        p=trie[p][c];
    }
    return exist[p];
}