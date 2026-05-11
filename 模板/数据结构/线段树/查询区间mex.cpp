//
// Created by elysia on 2025/5/15.
//
// 离线做法
#include <bits/stdc++.h>

using namespace std;
const int N = 300005;
struct ASK {
    int l, r, id, mex;
};
int n, m;
int a[N];
ASK Q[N];

struct Seg_tree1  {
    struct Tree {
        int l, r;
        int v;
    } seg[N << 2];
    void pushup(int k)
    {
        seg[k].v = min(seg[k << 1].v, seg[k << 1 | 1].v);
    }
    void build(int k, int l, int r)
    {
        seg[k] = {l, r, 0};
        if(l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(k << 1, l, mid);
        build(k << 1 | 1, mid + 1, r);
    }
    void modify(int k, int pos, int x)
    {
        int l = seg[k].l, r = seg[k].r;
        if(l == r) {
            seg[k].v = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid)
            modify(k << 1, pos, x);
        else
            modify(k << 1 | 1, pos, x);
        pushup(k);
    }
    int query(int k, int pos)
    {
        int l = seg[k].l, r = seg[k].r;
        if(l == r) {
            return seg[k].l;
        }
        if(seg[k << 1].v < pos)
            return query(k << 1, pos);
        else
            return query(k << 1 | 1, pos);
    }
};

Seg_tree1 T1;

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &a[i]), a[i] ++;
        a[i] = min(a[i], n + 2);
    }
    T1.build(1, 1, n + 2);

    for(int i = 1; i <= m; i ++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        Q[i] = {l, r, i, 0};
    }

    sort(Q + 1, Q + m + 1, [](ASK a, ASK b) {return a.r < b.r;});

    for(int i = 1, j = 1; i <= n; i ++)
    {
        T1.modify(1, a[i], i);
        while(j <= m && Q[j].r == i)
        {
            Q[j].mex = T1.query(1, Q[j].l);
            j ++;
        }
    }

    sort(Q + 1, Q + m + 1, [](ASK a, ASK b) {return a.id < b.id;});
    for(int i = 1; i <= m; i ++)
        printf("%d\n", Q[i].mex - 1);
}

// 在线做法 主席树
#include <bits/stdc++.h>

using namespace std;
const int N = 200005;

int tot = 0;
struct node {
    int ls, rs;
    int v;
} seg[N * 24];
int rt[N], a[N];
int n, m;

void pushup(int k)
{
    seg[k].v = min(seg[seg[k].ls].v, seg[seg[k].rs].v);
}
int modify(int old, int l, int r, int pos, int v)
{
    int p = ++tot;
    seg[p] = seg[old];
    if (l == r)
    {
        seg[p].v = v;
        return p;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        seg[p].ls = modify(seg[old].ls, l, mid, pos, v);
    else
        seg[p].rs = modify(seg[old].rs, mid + 1, r, pos, v);
    pushup(p);
    return p;
}
int query(int p, int l, int r, int pos)
{
    if (l == r)
    {
        return l;
    }
    int mid = (l + r) >> 1;
    if (seg[seg[p].ls].v < pos)
        return query(seg[p].ls, l, mid, pos);
    else
        return query(seg[p].rs, mid + 1, r, pos);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        rt[i] = modify(rt[i - 1], 0, n, a[i], i);
    }
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << query(rt[r], 0, n, l) << '\n';
    }
}
