//
// Created by elysia on 2025/5/12.
//
/*
# https://www.acwing.com/solution/content/1393/  这篇题解帮助理解证明
# 裴蜀定理：对于任意的整数a,b,存在整数x,y使得ax+by=gcd(a,b) 并且gcd(a, b)是ax+by的因子
# 推广ax+by=n*gcd(a,b)也成立
# 多个数字a1,a2,...,an的最大公约数gcd(a1,a2,...,an)也可以用扩展欧几里得算法求解

# 解决水壶问题 https://leetcode.cn/problems/water-and-jug-problem/description/
x, y两个容器能否得到体积z return x + y >= z and z % gcd(x, y) == 0
# https://www.luogu.com.cn/problem/P3951
互质的金额x, y（任意数量）不能买到的最贵物品 x*y-x-y

# 进一步的结论, 若a，b互质
# 记 C=ab-a-b。则有结论：对任意的整数 n，n 与 C-n 中有且仅有一个可以被表示。
#即：可表示的数与不可表示的数在区间 [0,C] 对称（关于 C 的一半对称）。0 可被表示，C 不可被表示；负数不可被表示，大于C的数都可被表示。
*/
// 求出gcd(a, b)的同时，求出x和y（满足条件的一组解）
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, g;
    g = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return g;
}