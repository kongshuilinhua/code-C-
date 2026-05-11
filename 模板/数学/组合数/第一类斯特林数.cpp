//
// Created by elysia on 2025/5/15.
//
// 第一类斯特林数（斯特林轮转数）
/*
 * n个不同的物品划分为m个非空圆排列的方案数   ->(非空圆排列：A(n, n) / n = (n - 1)!    例如1234、2341、3412、4123都是一个圆排列)
 * 第n个人放到m个集合中，分为两种情况
 * 1. 第n个人单独一个集合，前面的n-1个人放到m-1个集合中
 * 2. 第n个人放到m个集合中的一个，前面的n-1个人放到m个集合中，此时第n个人可以放到n-1个人中任意一个的左边
 * S(n, m) = S(n-1, m-1) + (n-1) * S(n-1, m)
 *
 */

// https://www.luogu.com.cn/problem/P4609
// 数轴上n个建筑,高度为[1, n]之间的整数。从最左边可以看见a个建筑，从最右边可以看见b个建筑。问满足上述条件的建筑方案数？
/*
 * 思路：最高的建筑是分水岭，左边有a-1个建筑群，右边有b-1个建筑群。
 * 每个建筑群构成一个圆排列，共计a+b-2个圆排列。即把n-1个建筑分成a+b-2个圆排列, S(n-1,a+b-2),然后a-1个放到n左边 C(a+b-2,a-1)
 */

const int inf = 1e18;
const int mod = 1e9 + 7;
const int N = 50010, M = 210;
long long S[N][M], C[M][M];

void init()
{
    S[0][0] = 1;
    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++)
            S[i][j] = (S[i - 1][j - 1] + (i - 1) * S[i - 1][j]) % mod;
    for (int i = 0; i < M; i++)
        C[i][0] = 1;
    for (int i = 1; i < M; i++)
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
}
void solve()
{
    int q;
    cin >> q;
    init();
    while (q--)
    {
        int n, a, b;
        cin >> n >> a >> b;
        print(S[n - 1][a + b - 2] * C[a + b - 2][a - 1] % mod);
    }
}