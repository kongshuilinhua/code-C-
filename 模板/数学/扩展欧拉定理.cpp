//
// Created by elysia on 2025/5/12.
//

// https://www.luogu.com.cn/problem/P5091

// 欧拉函数
// 1~n中与n互质的数的个数，记为φ(n)，φ(n)=n*(1-1/p1)*(1-1/p2)*...*(1-1/pk)
// 欧拉定理
// 若gcd(a, m) = 1，则a^(φ(m)) ≡ 1 (mod m)
// 扩展欧拉定理
/*
 * b < φ(m) 时 a^b = a^b     b小的时候，直接快速幂
 * b > φ(m) 时 a^b = a^(b % φ(m) + φ(m))     b很大的时候先降幂
 */
// 求欧拉函数
int get_phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res = res / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        res = res / n * (n - 1);
    return res;
}
// 降幂
int depow(int phi, string s)
{
    int res = 0;
    int f = 0;
    for (auto c : s)
    {
        res = res * 10 + c - '0';
        if (res >= phi)
        {
            f = 1;
            res %= phi;
        }
    }
    if (f)
        res += phi;
    return res;
}
void solve()
{
    int a, m;
    cin >> a >> m;
    string b;
    cin >> b;
    int phi = get_phi(m);
    print(pow(a, depow(phi, b), m));
}