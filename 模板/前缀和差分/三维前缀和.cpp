//
// Created by elysia on 2025/5/7.
//
// https://atcoder.jp/contests/abc366/tasks/abc366_d
const int N = 105;
int a[N][N][N], s[N][N][N];
void solve()
{
    int n, q;
    cin >> n;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                cin >> s[i][j][k];

    // Prefix-sum for 3rd dimension.
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                s[i][j][k] += s[i][j][k - 1];

    // Prefix-sum for 2nd dimension.
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                s[i][j][k] += s[i][j - 1][k];

    // Prefix-sum for 1st dimension.
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                s[i][j][k] += s[i - 1][j][k];

    cin >> q;
    while (q--)
    {
        int lx, rx, ly, ry, lz, rz;
        cin >> lx >> rx >> ly >> ry >> lz >> rz;
        int ans =
                s[rx][ry][rz] - s[lx - 1][ry][rz] - s[rx][ly - 1][rz] - s[rx][ry][lz - 1] + s[lx - 1][ly - 1][rz] + s[lx - 1][ry][lz - 1] + s[rx][ly - 1][lz - 1] - s[lx - 1][ly - 1][lz - 1];
        print(ans);
    }
}
