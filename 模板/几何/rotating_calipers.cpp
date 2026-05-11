//
// Created by elysia on 2025/5/10.
//
// 旋转卡壳
// https://www.luogu.com.cn/problem/P1452
// https://www.luogu.com.cn/problem/P4166
// http://poj.org/problem?id=2079
// https://www.luogu.com.cn/problem/P3187  有点难，没写
vector<Point> Andrew(vector<Point> &p)
{
    sort(all(p), [](const Point &a, const Point &b)
    { return a.x == b.x ? a.y < b.y : a.x < b.x; });
    p.erase(unique(all(p)), p.end());
    int n = p.size();
    if (n <= 1)
        return p;
    vector<Point> st(2 * n + 1);
    int top = 0;
    for (int i = 0; i < n; i++)
    {
        while (top > 1 && cross(st[top - 1], st[top], p[i]) <= 0)
            top--;
        st[++top] = p[i];
    }
    // upper hull
    int t = top;
    for (int i = n - 2; i >= 0; i--)
    {
        while (top > t && cross(st[top - 1], st[top], p[i]) <= 0)
            top--;
        st[++top] = p[i];
    }
    vector<Point> ret(st.begin() + 1, st.begin() + top + 1);
    if (ret.size() > 1)    // 去掉最后一个点
        ret.pop_back();
    return ret;
}
//  模板：给定平面上 n 个点，求凸包直径。
// 距离最远的点一定是凸壳上的两点。
//　双指针枚举，i指针枚举凸壳的边，j指针在前面枚举最远点，优选答案
//　注意，两个指针都是向前走的，保证旋转卡壳时间为O(n)
int rotating_calipers(const vector<Point> &p)
{
    int n = p.size();
    if (n < 2)
        return 0;
    if (n == 2)
        return dist2(p[0], p[1]);
    int res = 0, j = 1;
    for (int i = 0; i < n; i++)
    {
        int ni = (i + 1) % n;
        while (cross(p[i], p[ni], p[j]) < cross(p[i], p[ni], p[(j + 1) % n]))
            j = (j + 1) % n;
        res = max(res, max(dist2(p[i], p[j]), dist2(p[ni], p[j])));
    }
    return res;
}

// n个点，求最大四边形的面积
// 内接四边形的对角线一定是凸包的对角线。枚举凸包的对角线，旋转卡壳求最远点a,b，更新答案
// 如果求三角形，只需要b就行了 http://poj.org/problem?id=2079
double rotating_calipers(const vector<Point> &p)
{
    int n = p.size();
    double ans = 0.0;
    double res = 0;
    int j = 1;
    // 枚举对角线
    for (int i = 0; i < n; i++)
    {
        int a = i, b = i + 1;
        for (int j = i + 1; j < n; j++)
        {
            while (cross(p[i], p[j], p[a + 1]) < cross(p[i], p[j], p[a]))  // 右侧面积为－
                a = (a + 1) % n;
            while (cross(p[i], p[j], p[b + 1]) > cross(p[i], p[j], p[b]))  // 左侧面积为+
                b = (b + 1) % n;
            res = max(res, abs(cross(p[i], p[j], p[a])) + abs(cross(p[i], p[j], p[b])));
        }
    }
    return res / 2;
}

/*

 */
