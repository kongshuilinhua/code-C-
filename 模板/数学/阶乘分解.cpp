//
// Created by elysia on 2025/5/12.
//
// https://www.luogu.com.cn/problem/P2043
/*
 * 对于N以内的质数P，出现的次数为[N/P] + [N/P^2] + [N/P^3] + …… + [N/P^(log(P)N)]
 首先P的倍数有1个质因子P，P平方的倍数有2个质因子P，由于P平方的倍数一定是P的倍数，所以先前已经计入过一次，就只需再计入一次，P立方等等也是同理。
 */
void solve()
{
    int n;
    cin >> n;
    vi f(n + 1, 1);
    vi prime;
    for (int i = 2; i <= n; i++)
    {
        if (f[i])
        {
            for (int j = 2 * i; j <= n; j += i)
                f[j] = 0;
            prime.push_back(i);
        }
    }

    for (auto i : prime)
    {
        int j = i;
        int cnt = 0;
        while (j <= n)
        {
            cnt += n / j;
            j *= i;
        }
        print(i, cnt);
    }
}
