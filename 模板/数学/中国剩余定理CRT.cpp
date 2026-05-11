//
// Created by elysia on 2025/5/15.
//
// https://www.luogu.com.cn/problem/P1495
// 求解模数两两互质的线性同余方程组
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, g;
    g = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return g;
}

int CRT(const vector<pair<int, int>> &a)
{
    long long M = 1;
    for (auto [m, r] : a)
        M *= m;
    // 用 __int128 做中间计算, 防止爆ll
    __int128 res = 0;
    for (auto [m, r] : a)
    {
        long long c = M / m;
        int x, y;
        // 求 c 在 mod m 下的逆元
        exgcd(c % m, m, x, y);
        long long inv = (x % m + m) % m;
        // 累加 r * c * inv
        res = (res + (__int128)r * c % M * inv) % M;
    }
    return (res % M + M) % M;
}
