
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvi vector<vector<int>>
#define vvpii vector<vpii>
#define int long long

template <class T1, class T2>
ostream &operator<<(ostream &cout, const pair<T1, T2> &a) { return cout << a.first << ' ' << a.second; }
template <class T1, class T2>
ostream &operator<<(ostream &cout, const vector<pair<T1, T2>> &a)
{
    for (auto &x : a)
        cout << x << '\n';
    return cout;
}
template <class T1>
ostream &operator<<(ostream &cout, vector<T1> a)
{
    int n = a.size();
    if (!n)
        return cout;
    cout << a[0];
    for (int i = 1; i < n; i++)
        cout << ' ' << a[i];
    return cout;
}

template <class T1>
ostream &operator<<(ostream &cout, const vector<vector<T1>> &a)
{
    int n = a.size();
    if (!n)
        return cout;
    cout << a[0];
    for (int i = 1; i < n; i++)
        cout << '\n'
             << a[i];
    return cout;
}

using lll = __int128;
istream &operator>>(istream &cin, lll &x)
{
    bool flg = 0;
    x = 0;
    static string s;
    cin >> s;
    if (s[0] == '-')
        flg = 1, s = s.substr(1);
    for (char c : s)
        x = x * 10 + (c - '0');
    if (flg)
        x = -x;
    return cin;
}
ostream &operator<<(ostream &cout, lll x)
{
    static char s[60];
    if (x < 0)
        cout << '-', x = -x;
    int tp = 1;
    s[0] = '0' + (x % 10);
    while (x /= 10)
        s[tp++] = '0' + (x % 10);
    while (tp--)
        cout << s[tp];
    return cout;
}

template <class T1>
basic_string<T1> operator*(const basic_string<T1> &s, int m)
{
    if (m <= 0)
        return basic_string<T1>(); // 处理m<=0的情况

    basic_string<T1> r;
    r.reserve(s.size() * m); // 预分配空间提高效率

    for (int i = 0; i < m; ++i)
    {
        r += s;
    }
    return r;
}

// 支持 print(a, b, c...) 自动空格分隔 + 换行
void print() { cout << '\n'; } // 无参数时直接换行

template <typename T, typename... Args>
void print(T &&first, Args &&...args)
{
    cout << first;
    if constexpr (sizeof...(args) > 0)
    {
        cout << ' ';                        // 用空格分隔
        print(std::forward<Args>(args)...); // 递归处理剩余参数
    }
    else
    {
        cout << '\n'; // 最后一个参数后换行
    }
}

int pow(int base, int exp, int mod)
{
    if (mod == 1)
        return 0; // 任何数模1都是0
    int result = 1;
    base = base % mod; // 先对base取模，防止后续乘法溢出

    while (exp > 0)
    {
        // 如果exp是奇数，乘以base
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        // 现在exp一定是偶数
        exp = exp >> 1;             // exp /= 2
        base = (base * base) % mod; // base平方
    }

    return result;
}

class SparseTable
{
public:
    int n;
    vector<vector<int>> st;
    vector<int> logVal;

    SparseTable(const vector<int> &a)
    {
        // 假设 a 下标从 1 开始，共 n 个有效元素（a[0] 为哨兵）
        n = a.size() - 1;
        logVal.resize(n + 2);
        for (int i = 2; i <= n + 1; i++)
            logVal[i] = logVal[i / 2] + 1;

        int K = logVal[n] + 1;
        st.resize(K, vector<int>(n + 1));

        // 初始化第0层：直接复制 a[1..n]
        for (int i = 1; i <= n; i++)
        {
            st[0][i] = a[i];
        }
        for (int k = 1; k < K; k++)
        {
            for (int i = 1; i + (1 << k) - 1 <= n; i++)
            {
                st[k][i] = gcd(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    // 查询区间 [L, R] 的最大值，要求 1 <= L <= R <= n
    int query(int L, int R)
    {
        int j = logVal[R - L + 1];
        return gcd(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

class UnionFind
{
public:
    vector<int> parent;

    UnionFind(int n) : parent(n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int a)
    {
        int acopy = a;
        while (a != parent[a])
        {
            a = parent[a];
        }
        while (acopy != a)
        {
            int next = parent[acopy];
            parent[acopy] = a;
            acopy = next;
        }
        return a;
    }

    void merge(int a, int b)
    {
        parent[find(b)] = find(a);
    }
};

class FenwickTree
{
private:
    vector<int> tree;
    int size;

public:
    FenwickTree(int n) : size(n)
    {
        tree.resize(n + 2, 0);
    }

    void update(int index, int delta)
    {
        while (index <= size)
        {
            tree[index] += delta;
            index += index & -index;
        }
    }

    int query(int index)
    {
        int res = 0;
        while (index > 0)
        {
            res += tree[index];
            index -= index & -index;
        }
        return res;
    }
};

vi dx = {0, 1, 0, -1};
vi dy = {1, 0, -1, 0};
const int mod = 998244353;
const int inf = 1e18;
// const int mod = 1e9 + 7;
void solve()
{
    int n;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
