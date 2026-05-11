//
// Created by elysia on 2025/9/5.
//
// https://codeforces.com/contest/990/problem/G
struct RollbackDSU
{
    vector<int> parent, sz;
    vector<array<int, 4>> st;
    RollbackDSU(int n = 0) { init(n); }
    void init(int n)
    {
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            sz[i] = 1;
        }
        st.clear();
    }
    int find(int x)
    {
        while (x != parent[x])
            x = parent[x];
        return x;
    }
    bool merge(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        st.push_back({b, parent[b], a, sz[a]});
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
    int snapshot() { return (int)st.size(); }
    void rollback(int snap)
    {
        while ((int)st.size() > snap)
        {
            auto rec = st.back();
            st.pop_back();
            int b = rec[0], prev_parent_b = rec[1], a = rec[2], prev_size_a = rec[3];
            parent[b] = prev_parent_b;
            sz[a] = prev_size_a;
        }
    }
};