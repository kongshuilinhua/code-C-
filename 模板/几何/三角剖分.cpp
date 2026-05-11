//
// Created by elysia on 2025/5/10.
// http://poj.org/problem?id=2986
// http://poj.org/problem?id=3675
/*
 三角剖分的步骤：
多边形上的每条边都与圆心构成三角形
算出每个三角形与圆的相交面积
根据有向面积的正负累加到答案中

计算每个三角形与圆的相交面积，分为5种情况:
线段与圆心共线：返回0
线段完全在圆内：1个三角形的有向面积
线段完全在圆外：1个扇形的有向面积
线段一端在圆内：1个三角形+1个扇形的有向面积
线段是圆的割线：1个三角形+2个扇形的有向面积
 */
// 给定一个不自交的多边形，求和圆心在原点的圆的面积交。 可以用来求三角形，圆心不在原点只需要平移圆心到原点即可。
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#define x first
#define y second
using namespace std;

typedef pair<double, double> Point;
const int N = 55;
const double eps = 1e-8;
const double PI = acos(-1.0);
int n;
double R;
Point p[N], o; // 顶点和圆心

Point operator+(Point a, Point b)
{ // 向量+
    return Point(a.x + b.x, a.y + b.y);
}
Point operator-(Point a, Point b)
{ // 向量-
    return Point(a.x - b.x, a.y - b.y);
}
Point operator*(Point a, double t)
{ // 数乘
    return Point(a.x * t, a.y * t);
}
Point operator/(Point a, double t)
{ // 数除
    return Point(a.x / t, a.y / t);
}
double operator*(Point a, Point b)
{ // 叉积
    return a.x * b.y - a.y * b.x;
}
double operator&(Point a, Point b)
{ // 点积
    return a.x * b.x + a.y * b.y;
}
double len(Point a)
{ // 模长
    return sqrt(a & a);
}
double dis(Point a, Point b)
{ // 距离
    return len(b - a);
}
Point getNode(Point a, Point u, Point b, Point v)
{ // 直线交点
    double t = (a - b) * v / (v * u);
    return a + u * t;
}
Point rotate(Point a, double b)
{ // 逆转角
    return Point(a.x * cos(b) - a.y * sin(b), a.x * sin(b) + a.y * cos(b));
}
bool onSegment(Point p, Point a, Point b)
{ // p在线段ab上
    return fabs((a - p) * (b - p)) < eps && ((a - p) & (b - p)) <= 0;
}
Point norm(Point a)
{ // 单位向量
    return a / len(a);
}
// d:圆心到线段的最近距离。pa,pb:线段与圆的两交点
void getDP2(Point a, Point b, Point &pa, Point &pb, double &d)
{
    Point e = getNode(a, b - a, o, rotate(b - a, PI / 2)); // 垂足
    d = dis(o, e);
    if (!onSegment(e, a, b))
        d = min(dis(o, a), dis(o, b));
    if (R <= d)
        return;
    double len = sqrt(R * R - dis(o, e) * dis(o, e));
    pa = e + norm(a - b) * len;
    pb = e + norm(b - a) * len;
}
double sector(Point a, Point b)
{                                                   // 扇形面积
    double angle = acos((a & b) / len(a) / len(b)); //[0,Pi]
    if (a * b < 0)
        angle = -angle;
    return R * R * angle / 2;
}
double getArea(Point a, Point b)
{ // 面积的交
    if (fabs(a * b) < eps)
        return 0; // 共线
    double da = dis(o, a), db = dis(o, b);
    if (R >= da && R >= db)
        return a * b / 2; // ab在圆内
    Point pa, pb;
    double d;
    getDP2(a, b, pa, pb, d);
    if (R <= d)
        return sector(a, b); // ab在圆外
    if (R >= da)
        return a * pb / 2 + sector(pb, b); // a在圆内
    if (R >= db)
        return sector(a, pa) + pa * b / 2;              // b在圆内
    return sector(a, pa) + pa * pb / 2 + sector(pb, b); // ab是割线
}
int main()
{
    // 圆心平移到原点
    double ox = 0.0, oy = 0.0;
    while (scanf("%lf%d", &R, &n) != -1)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%lf%lf", &p[i].x, &p[i].y);
            p[i].x -= ox;
            p[i].y -= oy;
        }
        double res = 0;
        for (int i = 0; i < n; i++)
            res += getArea(p[i], p[(i + 1) % n]);
        printf("%.2lf\n", fabs(res)); // 点可能顺时针
    }
    return 0;
}