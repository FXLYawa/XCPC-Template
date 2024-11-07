
    
    int l = 1, r = n;
    auto calc = [&] (int x) {
        
    };
    while(l < r) {
        ll lmid = l + (r - l) / 3;
        ll rmid = r - (r - l) / 3;
        if(calc(lmid) <= calc(rmid))	l = lmid + 1;
        else r = rmid - 1;
    }
    cout << max(calc(l), calc(r)) << endl;