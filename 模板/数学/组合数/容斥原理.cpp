//
// Created by elysia on 2025/5/15.
//
// 一个整数n和m个不同的质数p1,p2,...,pm，求1~n中能被p1,p2,...,pm中至少一个数字整除的数的个数 m<=16 n,pi<=1e9
const int N = 20;
int n, m, prim[N];
// 容斥原理.md
// 集合的并等于集合的交集的交错和（奇正偶负）
int calc()
{
    int res = 0;
    // 枚举每个数字选或者不选
    for (int i = 1; i < 1 << m; i++)
    {
        int t = 1, sign = -1;
        for (int j = 0; j < m; j++) // 过滤状态
            if (i & 1 << j)
            {
                if ((ll)t * prim[j] > n) // 超过了n一定是0
                {
                    t = 0;
                    break;
                }
                t *= prim[j]; // 质数的积
                sign = -sign;
            }
        if (t)
            res += n / t * sign; // 交集的和
    }
    return res;
}


// 集合的交等于全集减去补集的并
// https://www.luogu.com.cn/problem/P1450
/*
 * 4种硬币，面值为ci, n次查询，求每次购买s价值的东西，带了di个i种硬币的方案数。1<=ci,di,s<=1e5, 1<=n<=1000
 */
const int N = 1e5 + 10;
int f[N];
void solve()
{
    int n;
    vi c(4), d(4);
    for (int i = 0; i < 4; i++)
        cin >> c[i];
    cin >> n;
    f[0] = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = c[i]; j < N; j++)
            f[j] += f[j - c[i]];
    }
    auto calc = [&](int s)
    {
        int res = 0;
        for (int i = 1; i < (1 << 4); i++)
        {
            int t = 0, sign = -1;
            for (int j = 0; j < 4; j++)
            {
                if ((i >> j) & 1)
                {
                    t += c[j] * (d[j] + 1);
                    sign *= -1;
                }
            }
            if (s >= t)
                res += sign * f[s - t];
        }
        return f[s] - res;
    };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
            cin >> d[j];
        int s;
        cin >> s;
        print(calc(s));
    }
}