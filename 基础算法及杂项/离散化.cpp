

vector<int> tmp(arr);  // tmp 是原数据的一个副本
sort(al(tmp));
tmp.erase(std::unique(al(tmp)), tmp.end());
for (int i=0;i<n;++i)
    arr[i]=lower_bound(al(tmp),arr[i])-tmp.begin();