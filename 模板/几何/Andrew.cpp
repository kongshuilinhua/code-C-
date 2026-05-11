//
// Created by elysia on 2025/5/10.
//
// https://www.luogu.com.cn/problem/P2742
// https://www.luogu.com.cn/problem/P3829

// 求出凸包上的所有点，第一个点和最后一个点相同
vector<Point> Andrew(vector<Point> &p)
{
    auto cmp = [&](Point &a, Point &b)
    {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }; // 双关键字排序，x升序，y升序
    sort(all(p), cmp);
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n <= 1)
        return p;
    vector<Point> st(2 * n + 1); // 栈模拟
    int top = 0;
    for (int i = 0; i < n; i++)
    {
        // 求下凸包，新的点在栈顶两点构成的有向直线的右侧或者共线，那么弹出旧点。
        // 不能弹出时，新点入栈
        while (top > 1 && cross(st[top - 1], st[top], p[i]) <= 0)
            top--;
        st[++top] = p[i];
    }
    // 第一个点和最后一个点一定是
    // 求上凸包
    int t = top;
    for (int i = n - 2; i >= 0; i--)
    {
        while (top > t && cross(st[top - 1], st[top], p[i]) <= 0)
            top--;
        st[++top] = p[i];
    }
    // 1-top
    vector<Point> ret(st.begin() + 1, st.begin() + top + 1);
    if (ret.size() > 1)    // 去掉最后一个点
        ret.pop_back();
    return ret;
}