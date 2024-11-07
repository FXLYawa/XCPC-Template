#include <bits/stdc++.h>
using namespace std;
//z[i]表示s[0……z[i]-1]=s[i……i+z[i]-1]
//特别的且z[0]=0
//维护l，r使s[i……r]=s[i-l……r-l]
vector<int> z_function(string &s) {//base 0
    int n=(int)s.size();
    vector<int> z(n);
    for (int i=1,l=0,r=0;i<n;++i) {
        if (i<=r&&z[i-l]<r-i+1) {
            z[i]=z[i-l];//利用前缀
        } 
        else{//朴素拓展
            z[i]=max((int)0,r-i+1);
            while(i+z[i]<n&&s[z[i]]==s[i+z[i]])++z[i];
        }
        if(i+z[i]-1>r)l=i,r=i+z[i]-1;
    }
    return z;
}