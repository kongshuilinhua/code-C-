//
// Created by elysia on 2025/8/4.
//
// 0<=i<n
// https://www.luogu.com.cn/problem/P2455
int gauss(vector<vector<double>> &matrix)
{
    int n = matrix.size();
    int c, r;
    // 枚举主元
    for (c = 0, r = 0; c < n; c++)
    {
        int t = r;
        // 找绝对值最大的行
        for (int i = r; i < n; i++)
            if (fabs(matrix[i][c]) > fabs(matrix[t][c]))
                t = i;
        if (fabs(matrix[t][c]) < eps)
            continue;
        // 将绝对值最大的行换到上面
        swap(matrix[t], matrix[r]);
        // 把该行主元系数变成1（倒序枚举，最后再处理这个系数）
        for (int i = n; i >= c; i--)
            matrix[r][i] /= matrix[r][c];
        // 用当前行将下面所有的列消成0
        for (int i = r + 1; i < n; i++)
            if (fabs(matrix[i][c]) > eps)
                for (int j = n; j >= c; j--)
                    matrix[i][j] -= matrix[r][j] * matrix[i][c];
        r++;
    }
    if (r < n)
    {
        // 存在x=0，b!=0无解，x=0,b=0则有无穷多解
        for (int i = r; i < n; i++)
            if (fabs(matrix[i][n]) > eps)
                return 2; // 无解
        return 1;         // 无穷多解
    }
    // 倒序带入，答案存入matrix[i][n]
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            matrix[i][n] -= matrix[i][j] * matrix[j][n];
    return 0; // 有唯一解
}