//
// Created by elysia on 2025/8/5.
//
//https://leetcode.cn/problems/partition-array-for-maximum-xor-and-and/description/
//https://acm.hdu.edu.cn/showproblem.php?pid=3949
//https://www.luogu.com.cn/problem/P3857
//https://www.luogu.com.cn/problem/P3812
// 高斯消元构造异或线性基，n个整数的子集最大异或和等于线性基最大异或和
struct LinearBasis
{
    static const int MAXB = 60;
    vector<int> a;
    int n, k = 0; // k为基的数量，不同异或和数为2^k
    LinearBasis(const vector<int> &v) : a(v), n(v.size()) {}
    void build()
    {
        for (int i = MAXB; i >= 0; --i)
        {
            int p = -1;
            for (int j = k; j < n; ++j)
            {
                if ((a[j] >> i) & 1)
                {
                    p = j;
                    break;
                }
            }
            if (p == -1)
                continue;
            swap(a[p], a[k]);
            for (int j = 0; j < n; ++j)
            {
                if (j != k && ((a[j] >> i) & 1))
                    a[j] ^= a[k];
            }
            ++k;
            if (k == n)
                break;
        }
    }
    // 子集最大异或和
    int max_xor()
    {
        int res = 0;
        for (int x : a)
            res ^= x;
        return res;
    }
    // 第k小异或和
    int kth_xor(int x)
    {
        // 可以构造出0
        if (k < n)
            x--;
        if (x >= (1LL << k))
            return -1;
        int res = 0;
        for (int i = 0; i < k; i++)
            if ((x >> i) & 1)
                res ^= a[k - i - 1];
        return res;
    }
};