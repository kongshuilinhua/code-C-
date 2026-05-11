# 扩展中国剩余定理EXCRT
```c++
//
// Created by elysia on 2025/5/15.
//
// https://www.luogu.com.cn/problem/P4777
// // 求解线性同余方程组，没有模数两两互质的条件
using lll = __int128;
lll exgcd(lll a, lll b, lll &x, lll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    lll x1, y1, g;
    g = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return g;
}
lll EXCRT(vector<pair<lll, lll>> a)
{
    lll p, q;
    lll m1 = a[0].first, r1 = a[0].second;
    for (int i = 1; i < a.size(); i++)
    {
        lll m2 = a[i].first, r2 = a[i].second;
        lll d = exgcd(m1, m2, p, q);
        if ((r2 - r1) % d)
        {
            return -1;
        }
        p = p * (r2 - r1) / d; // 特解
        p = (p % (m2 / d) + m2 / d) % (m2 / d);
        r1 = m1 * p + r1;
        m1 = m1 * m2 / d;
    }
    return (r1 % m1 + m1) % m1;
}
```