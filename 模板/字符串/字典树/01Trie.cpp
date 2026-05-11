// https://codeforces.com/contest/2093/submission/314669100
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

constexpr int N = 200000 * 31;

int tot;
int trie[N][2];
int cnt[N];

int newNode()
{
    int x = ++tot;
    trie[x][0] = trie[x][1] = 0;
    cnt[x] = 0;
    return x;
}

void init()
{
    tot = 0;
    newNode();
}

void add(int x, int t)
{
    int o = 1;
    for (int i = 30; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        int &p = trie[o][bit];
        if (!p)
            p = newNode();
        o = p;
        cnt[o] += t;
    }
}

int query(int x)
{
    int o = 1;
    int ans = 0;
    for (int i = 30; i >= 0; i--)
    {
        int d = (x >> i) & 1;
        if (cnt[trie[o][d ^ 1]])
        {
            d ^= 1;
            ans |= (1 << i);
        }
        o = trie[o][d];
    }
    return ans;
}

// https://www.luogu.com.cn/problem/P10471
// 两个数的最大异或和
const int N = 1e5 * 31 + 10;
int tot;
int Trie[N][2];
void add(int x, int t)
{
    int p = 0;
    for (int i = 30; i >= 0; i--)
    {
        int j = (x >> i) & 1;
        if (!Trie[p][j])
            Trie[p][j] = ++tot;
        p = Trie[p][j];
    }
}
int query(int x)
{
    int p = 0;
    int res = 0;
    for (int i = 30; i >= 0; i--)
    {
        int j = (x >> i) & 1;
        if (Trie[p][j ^ 1])
        {
            res += 1 << i;
            p = Trie[p][j ^ 1];
        }
        else
            p = Trie[p][j];
    }
    return res;
}
// https://ac.nowcoder.com/acm/contest/116435/B
// 查询异或和小于k的个数
ll query(int x, int k)
{
    int o = 1;
    ll res = 0;
    for (int i = 30; i >= 0 && o; --i)
    {
        int xb = (x >> i) & 1;
        int kb = (k >> i) & 1;
        if (kb == 1)
        {
            int child = trie[o][xb];
            if (child)
                res += cnt[child];
            o = trie[o][xb ^ 1];
        }
        else
        {
            o = trie[o][xb];
        }
    }
    return res;
}