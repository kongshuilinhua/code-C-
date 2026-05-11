//
// Created by elysia on 2025/5/15.
//
/*
 * 第二类斯特林数（斯特林子集数）
 * 将n个不同的元素，划分为m个非空集合的方案数
 * n个人进入m个房间，有两种情况
 * 1. 第n个人单独一个房间，前面的n-1个人放到m-1个房间中
 * 2. 第n个人进入已经有人的房间，先让前n-1个人进入m个房间，然后第n个人可以选择m个房间中的任意一个
 * S(n, m) = S(n-1, m-1) + m * S(n-1, m)
 */
// https://www.luogu.com.cn/problem/P3904
// 模板题，n只小猪安置在m个房间且没有房间空闲的方案数。n<=50, m<=50 需要高精度

const int N = 55;
int S[N][N][100], L[N][N];  // S[x][y][i] 存储S[x][y]第i位上的数, L[x][y]表示S[x][y]的位数

void add(int x, int y)
{
    L[x][y] = max(L[x - 1][y - 1], L[x - 1][y]);
    for (int i = 0; i < L[x][y]; i++)
    {
        S[x][y][i] += S[x - 1][y - 1][i] + y * S[x - 1][y][i];
        S[x][y][i + 1] += S[x][y][i] / 10;
        S[x][y][i] %= 10;
    }
    while (S[x][y][L[x][y]])
    {
        S[x][y][L[x][y] + 1] += S[x][y][L[x][y]] / 10;
        S[x][y][L[x][y]] %= 10;
        L[x][y]++;
    }
}
void solve()
{
    int n, m;
    cin >> n >> m;
    S[0][0][0] = 1;
    L[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            add(i, j);
    if (!L[n][m])   // 可能方案是0
        cout << 0;
    for (int i = L[n][m] - 1; i >= 0; i--)
        cout << S[n][m][i];
}
