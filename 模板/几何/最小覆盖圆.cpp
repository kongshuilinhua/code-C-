//
// Created by elysia on 2025/5/15.
//
// https://www.luogu.com.cn/problem/P1742
// 给出 N 个点，让你画一个最小的包含所有点的圆。
// 随机增量法，复杂度O(n)
/*
假设圆 O 是前 𝑖−1 个点的最小覆盖圆，加入第 𝑖 个点，如果在圆内或边上则什么也不做。否则，新得到的最小覆盖圆肯定经过第 𝑖 个点
然后以第 𝑖 个点为基础（半径为0），加入第 𝑗 个点（𝑗<𝑖），若第 𝑗 个点在圆外，则最小覆盖圆必经过 𝑖,𝑗 两个点
然后以 𝑖,𝑗 两点为基础，加入第 𝑘 个点（𝑘<𝑗<𝑖），若第 𝑘 个点在圆外，则最小覆盖圆必经过 𝑖,𝑗,𝑘 三个点
遍历完所有点之后，所得到的圆就是覆盖所有点得最小圆
 */

#define x first
#define y second
using namespace std;

const int N = 100010;
const double PI = acos(-1);
int n;
struct Point
{
    double x, y;
} p[N];
struct Circle
{
    Point p;
    double r;
} C;

Point operator+(Point a, Point b)
{
    return {a.x + b.x, a.y + b.y};
}
Point operator-(Point a, Point b)
{
    return {a.x - b.x, a.y - b.y};
}
Point operator*(Point a, double t)
{
    return {a.x * t, a.y * t};
}
Point operator/(Point a, double t)
{
    return {a.x / t, a.y / t};
}
double operator*(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}
// 旋转向量 a，逆时针旋转角度 b（弧度），返回旋转后的向量
Point rotate(Point a, double b)
{
    // x' = x*cosθ - y*sinθ
    // y' = x*sinθ + y*cosθ
    return {a.x * cos(b) - a.y * sin(b),
            a.x * sin(b) + a.y * cos(b)};
}

// 计算两点 a、b 之间的欧氏距离
double dis(Point a, Point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 计算两条无限直线的交点
// 直线1：点 a，方向向量 u；直线2：点 b，方向向量 v
Point cross(Point a, Point u, Point b, Point v)
{
    // 解方程 a + u*t 与 直线2 (b + v*s) 相交
    // (a + u*t - b) × v = 0 => t = ((a - b) × v) / (v × u)
    double t = (a - b) * v / (v * u);
    return a + u * t; // 返回交点坐标
}

// 计算线段 ab 的中垂线：
// 返回值.first = 中点，.second = 方向向量（垂直于 ab）
pair<Point, Point> midperp(Point a, Point b)
{
    Point mid = (a + b) / 2;           // 中点
    Point dir = rotate(b - a, PI / 2); // (b - a) 逆时针旋转 90° 得到垂直向量
    return {mid, dir};
}

// 构造覆盖两点 a、b 的最小圆：
// 圆心为中点，半径为两点距离的一半
Circle cover(Point a, Point b)
{
    Point center = (a + b) / 2;    // 两点中点
    double radius = dis(a, b) / 2; // 半径
    return {center, radius};
}

// 构造覆盖三点 a、b、c 的最小圆（外接圆）
// 1. 取 ab 和 ac 的中垂线
// 2. 计算两中垂线的交点作为圆心
// 3. 半径为圆心到 a（或 b、c）距离
Circle cover(Point a, Point b, Point c)
{
    auto u = midperp(a, b);
    auto v = midperp(a, c);
    Point center = cross(u.first, u.second, v.first, v.second);
    double radius = dis(center, a);
    return {center, radius};
}

// 增量法（Welzl 算法的随机版本）求最小覆盖圆
void increment()
{
    // 初始：用第一点 p[1] 构造半径为 0 的圆
    C = {p[1], 0};

    // 依次加入第 i 个点
    for (int i = 2; i <= n; i++)
    {
        // 如果第 i 个点在当前圆外
        if (C.r < dis(C.p, p[i]))
        {
            // 以 p[i] 为圆心，半径 0 重置
            C = {p[i], 0};

            // 遍历之前的所有点 j < i
            for (int j = 1; j < i; j++)
            {
                // 若 p[j] 也在当前圆外，则用 p[i], p[j] 重构圆
                if (C.r < dis(C.p, p[j]))
                {
                    C = cover(p[i], p[j]);
                    // 再次遍历 k < j，若 p[k] 在新圆外，则用三点外接圆重构
                    for (int k = 1; k < j; k++)
                    {
                        if (C.r < dis(C.p, p[k]))
                            C = cover(p[i], p[j], p[k]);
                    }
                }
            }
        }
    }
}
void solve()
{
    cout << fixed << setprecision(10);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;
    random_shuffle(p + 1, p + n + 1);
    increment();
    print(C.r);
    print(C.p.x, C.p.y);
}

// https://www.luogu.com.cn/problem/P4288
// 给出 n 个点，长轴方向和扩大倍数，求一个覆盖所有点的最小椭圆
// 把坐标系逆时针旋转 a 度，让 x 轴沿长轴方向，沿 x 轴把椭圆压缩成圆。 这等价于所有点都顺时针旋转 a 度，再把所有点的 x 坐标变为原来的 1/b
//最后跑一个最小圆覆盖即可

void solve()
{
    cout << fixed << setprecision(3);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;
    double a, b;
    cin >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        p[i] = rotate(p[i], -a / 180 * PI);
        p[i].x /= b; // 椭圆压缩成圆
    }
    random_shuffle(p + 1, p + n + 1);
    increment();
    print(C.r);
}
