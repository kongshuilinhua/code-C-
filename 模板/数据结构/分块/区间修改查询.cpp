#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

constexpr int N = 5e4 + 10;
int a[N], sum[N], lazy[N], id[N], len, n;

void add(int l, int r, int x){
    int sid = id[l], eid = id[r];
    for(int i = l; i <= min(sid * len, r); i++){
        a[i] += x;
        sum[sid] += x;
    }
    if (sid != eid){
        for(int i = (eid - 1) * len + 1; i <= r; i++){
            a[i] += x;
            sum[eid] += x;
        }
    }
    for(int i = sid + 1; i < eid; i++){
        lazy[i] += x;
        sum[i] += len * x;
    }
}

int query(int l, int r, int p){
    int res = 0;
    int sid = id[l], eid = id[r];
    for(int i = l; i <= min(sid * len, r); i++){
        res = (res + lazy[sid] + a[i]) % p;
    }
    if (sid != eid){
        for(int i = (eid - 1) * len + 1; i <= r; i++) 
        res = (res + lazy[eid] + a[i]) % p;
    }
    for(int i = sid + 1; i < eid; i++) res = (res + sum[i]) % p;
    return res;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    len = sqrt(n);
    int op, l, r, x;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> op >> l >> r >> x;
        if (op == 0) add(l, r, x);
        else cout << query(l, r, x + 1) << endl;
    }
    return 0;
}