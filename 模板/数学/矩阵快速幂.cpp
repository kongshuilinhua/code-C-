#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

struct Matrix
{
    int n;
    vector<vector<int>> a;
    // 矩阵下标从1开始，构造函数创建 n x n 的矩阵
    Matrix(int n) : n(n), a(n + 1, vector<int>(n + 1, 0)) {}

    Matrix operator*(const Matrix &b) const
    {
        Matrix C(n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    C.a[i][j] = (C.a[i][j] + a[i][k] * b.a[k][j]) % mod;
        return C;
    }
};

Matrix qpow(Matrix A, ll exp)
{
    Matrix res(A.n);
    // 初始化 res 为单位矩阵
    for (int i = 1; i <= A.n; i++)
    {
        res.a[i][i] = 1;
    }
    while (exp)
    {
        if (exp & 1)
            res = res * A;
        A = A * A;
        exp >>= 1;
    }
    return res;
}

//https://codeforces.com/gym/104611/attachments K题
// 起点1~n任意，必须经过k个点至少一次。一共d天，总共的方案数

const int inf = 1e18;
// const int mod = 1e9 + 7;
double eps = 1e-8;
const int mod = 1e9 + 9;
struct Matrix
{
    int n;
    vector<vector<int>> a;
    // 自定义size
    Matrix(int size = 20) : n(size), a(n + 1, vector<int>(n + 1, 0)) {}

    Matrix operator*(const Matrix &b) const
    {
        Matrix C(n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    C.a[i][j] = (C.a[i][j] + a[i][k] * b.a[k][j]) % mod;
        return C;
    }
};
void qpow(Matrix &res, Matrix &A, int b)
{
    while (b)
    {
        if (b & 1)
            res = res * A;
        A = A * A;
        b >>= 1;
    }
}

int n, m, k, d;
int a[25][25];
int s[10];
int calc(int mask)
{
    Matrix e(n), ans(n);
    vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            e.a[i][j] = a[i][j];
        // 任意点都可以是起点
        ans.a[1][i] = 1;
    }
    for (int i = 1; i <= k; i++)
    {
        if (mask & (1 << (i - 1)))
        {
            int x = s[i];
            vis[x] = true;
            for (int j = 1; j <= n; j++)
                e.a[x][j] = e.a[j][x] = 0;
        }
    }
    qpow(ans, e, d - 1);

    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
            sum = (sum + ans.a[1][i]) % mod;
    }
    return sum;
}
void solve()
{

    cin >> n >> m >> k >> d;
    for (int i = 1; i <= k; i++)
    {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
    int res = 0;
    for (int i = 0; i < (1 << k); i++)
    {
        if (__builtin_popcount(i) & 1)
        {
            res = (res - calc(i) + mod) % mod;
        }
        else
            res = (res + calc(i)) % mod;
    }
    print(res);
}
