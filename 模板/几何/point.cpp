#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

// const int mod = 1e9 + 7;

struct Point
{
    double x;
    double y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

bool operator==(const Point &a, const Point &b)
{
    return a.x == b.x && a.y == b.y;
}

Point operator+(const Point &a, const Point &b)
{
    return Point(a.x + b.x, a.y + b.y);
}

Point operator-(const Point &a, const Point &b)
{
    return Point(a.x - b.x, a.y - b.y);
}

// 数积
Point operator*(Point a, double t)
{
    return Point(a.x * t, a.y * t);
}

double operator*(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}
/*
叉积  absin(cta) = x1y2-y1x2
1. 判断点线关系
  > 0 点在直线左侧  < 0 点在直线右侧  = 0 三点共线

2.判断线线关系
t = cross(a, b, c) * cross(a, b, d)
t > 0  ab和cd无交点      t <= 0  ab和cd有交点（交点是端点时=0）
*/
double cross(const Point &a, const Point &b, const Point &c)
{

    return (b - a) * (c - a);
}

double dis(const Point &a, const Point &b)
{
    return hypot(a.x - b.x, a.y - b.y);
}

// 求两直线的交点    两点式 -> 点向式
Point getNode(Point a, Point u, Point b, Point v)
{
    double t = (a - b) * v / (v * u); // 面积比值  -> 线段长度比值
    return a + u * t;
}

// 判断<线段>!是否相交
bool intersect(Point a, Point b, Point c, Point d)
{
    if (cross(a, b, c) * cross(a, b, d) > 0)
        return 0;
    if (cross(c, d, a) * cross(c, d, b) > 0)
        return 0;
    return 1;
}

// 直线 (ab) 与线段 (cd) 相交 ⇔ cross(ab, c)·cross(ab, d) ≤ 0
bool intersect_line_seg(Point a, Point b, Point c, Point d)
{
    return cross(a, b, c) * cross(a, b, d) <= 0;
}

// 原点到圆 (c, r) 的两个切点
vector<Point> get_tangents(Point c, double r)
{
    double dx = c.x, dy = c.y;
    double d2 = dx * dx + dy * dy;
    double d = sqrt(d2);
    double l2 = d2 - r * r;
    double f1 = (d2 - r * r) / d2;
    double f2 = r * sqrt(l2) / d2;
    Point base = c * f1;                // (r^2 / |c|^2) * c
    Point perp = Point(-c.y, c.x) * f2; // ± (r√(d^2–r^2)/d^2) * perp(c)
    return {base + perp, base - perp};
}

// 判断线段 ab 是否与圆 (center, r) 相交
bool segment_circle_intersect(Point a, Point b, Point center, double r)
{
    Point ab = b - a;
    Point ac = center - a;
    double t = dot(ac, ab) / dot(ab, ab);
    t = max(0.0, min(1.0, t));
    Point h = a + ab * t;
    return dis(h, center) <= r;
}

// 线段 ab 与圆 (center, r) 的交点（最多两个）
// 返回位于参数 t∈[0,1] 处的交点
vector<Point> segment_circle_points(Point a, Point b, Point center, double r)
{
    Point d = b - a;
    // 求解 |a + t d – center|^2 = r^2
    double A = dot(d, d);
    double B = 2 * dot(a - center, d);
    double C = dot(a - center, a - center) - r * r;
    double disc = B * B - 4 * A * C;
    vector<Point> res;
    if (disc < 0)
        return res; // 无交点
    double sq = sqrt(disc);
    double t1 = (-B + sq) / (2 * A);
    double t2 = (-B - sq) / (2 * A);
    if (0.0 <= t1 && t1 <= 1.0)
        res.push_back(a + d * t1);
    if (disc > 0 && 0.0 <= t2 && t2 <= 1.0)
        res.push_back(a + d * t2);
    return res;
}

// 逆转角。相对于圆心旋转
Point rotate(Point a, double b)
{
    return {a.x * cos(b) - a.y * sin(b), a.x * sin(b) + a.y * cos(b)};
}

// 返回三角形 ABC 的有向面积
double triangle_area(Point A, Point B, Point C) {
    return fabs( (B - A) * (C - A) ) * 0.5;
}

// 返回三角形 ABC 的有向面积
double triangle_area(double x1, double y1,
                     double x2, double y2,
                     double x3, double y3) {
    return fabs(
            x1*(y2-y3) +
            x2*(y3-y1) +
            x3*(y1-y2)
    ) * 0.5;
}

// 多边形有序点 p[0..n) 必须首尾不重复
double polygon_area(const vector<Point>& p) {
    int n = p.size();
    double A = 0;
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        A += cross(p[i], p[j]);
    }
    return fabs(A) * 0.5;
}

// 射线法判断点是否在多边形内部（含边上）
bool point_in_polygon(const vector<Point>& P, const Point& q) {
    bool in = false;
    int n = P.size();
    for (int i = 0, j = n-1; i < n; j = i++) {
        auto &a = P[i], &b = P[j];
        // 边上
        if (fabs(cross(b-a, q-a))<1e-9
            && min(a.x,b.x)<=q.x && q.x<=max(a.x,b.x)
            && min(a.y,b.y)<=q.y && q.y<=max(a.y,b.y))
            return true;
        // 射线交点计数
        bool cond = ((a.y>q.y) != (b.y>q.y))
                    && (q.x < (b.x-a.x)*(q.y-a.y)/(b.y-a.y) + a.x);
        if (cond) in = !in;
    }
    return in;
}

void norm(std::vector<Point> &h)
{
    int i = 0;
    for (int j = 0; j < (h.size()); j++)
    {
        if (h[j].y < h[i].y || (h[j].y == h[i].y && h[j].x < h[i].x))
        {
            i = j;
        }
    }
    std::rotate(h.begin(), h.begin() + i, h.end());
}

int sgn(const Point &a)
{
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 0 : 1;
}
