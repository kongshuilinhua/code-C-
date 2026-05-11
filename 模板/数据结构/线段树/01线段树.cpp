#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;
#define int long long
#define endl "\n"
#define lc o << 1
#define rc o << 1 | 1

// https://www.luogu.com.cn/problem/P3870
int lazy[4 * N], sum[4 * N];
// 维护0的数量,翻转的时候总和减一下就是1的数量了
void pushup(int o)
{
    sum[o] = sum[lc] + sum[rc];
}

void pushdown(int o, int l, int r)
{
    if(lazy[o]){
        lazy[lc] ^= 1;
        lazy[rc] ^= 1;
        int mid = l + r >> 1;
        sum[lc] = (mid - l + 1) - sum[lc];
        sum[rc] = (r - mid) - sum[rc];
        lazy[o] = 0;
    }
}

void update(int o, int l, int r, int L, int R)
{
    if (l >= L and r <= R) {
        sum[o] = (r - l + 1) - sum[o];
        lazy[o] ^= 1;
        return ;
    }
    pushdown(o, l, r);
    int mid = l + r >> 1;
    if (L <= mid) update(lc, l, mid, L, R);
    if (R > mid) update(rc, mid + 1, r, L, R);
    pushup(o);
}

int query(int o, int l, int r, int L, int R)
{
    if (l >= L and r <= R) return sum[o];
    pushdown(o, l, r);
    int res = 0;
    int mid = l + r >> 1;
    if (L <= mid) res += query(lc, l, mid, L, R);
    if (R >  mid) res += query(rc, mid + 1, r, L, R);
    return res;
}

int n, m, op, l, r;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        cin >> op >> l >> r;
        if (op == 0) update(1, 1, n, l, r);
        else cout << query(1, 1, n, l, r) << endl;
    }
    
    return 0;
}