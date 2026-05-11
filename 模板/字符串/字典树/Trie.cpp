
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int tot;
int trie[N][26]; // 结点p沿着j这条边走到的子节点
int cnt[N];

void add(string &s, int t)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = s[i] - '0';
        if (!trie[p][j])
            trie[p][j] = ++tot;
        p = trie[p][j];
    }
    cnt[p] += t;
}

int query(string &s)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = s[i] - '0';
        if (!trie[p][j])
            return 0;
        p = trie[p][j];
    }
    return cnt[p];
}