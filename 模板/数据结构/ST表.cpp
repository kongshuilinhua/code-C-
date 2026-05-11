//
// Created by elysia on 2025/5/29.
//

template <typename T, class F>
class SparseTable
{
public:
    int n, K;
    vector<int> logVal;
    vector<vector<T>> st;
    F merge;

    // 构造：传入数组 a（0-based，下标 [0..n-1]），以及一个二元合并操作 merge(x,y)
    SparseTable(const vector<T> &a, F mergeOp)
            : n((int)a.size()), merge(mergeOp)
    {
        logVal.resize(n + 1);
        logVal[1] = 0;
        for (int i = 2; i <= n; i++)
            logVal[i] = logVal[i / 2] + 1;

        K = logVal[n] + 1;
        st.assign(K, vector<T>(n));
        // 第0层直接拷贝
        for (int i = 0; i < n; i++)
            st[0][i] = a[i];
        // 其余层
        for (int k = 1; k < K; k++)
        {
            int len = 1 << (k - 1);
            for (int i = 0; i + (1 << k) <= n; i++)
            {
                st[k][i] = merge(st[k - 1][i], st[k - 1][i + len]);
            }
        }
    }

    // 查询区间 [L, R]（0-based，含端点）的合并结果
    T query(int L, int R) const
    {
        int j = logVal[R - L + 1];
        return merge(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

SparseTable<int, function<int(int, int)>> ST(
        a, [](int x, int y)
{ return std::gcd(x, y); });