//
// Created by elysia on 2025/5/15.
//
// https://www.luogu.com.cn/problem/P3369
const int N = 1e5 + 10;

// 结点结构体：表示 Treap 的节点
struct node
{
    int l, r; // 左右子节点索引
    int val;  // 键值
    int rnd;  // 随机优先级（维持堆性质）
    int size; // 以该节点为根的子树大小
} tr[N];

int root = 0, idx = 0; // root: 根节点索引，idx: 已使用节点数

// 创建新节点，并初始化
void newnode(int &x, int v)
{
    x = ++idx;          // 分配一个新节点编号
    tr[x].val = v;      // 设置节点的键值
    tr[x].rnd = rand(); // 随机优先级，保证平衡
    tr[x].size = 1;     // 新节点子树大小为1
}

// 向上更新节点 p 的子树大小
void pushup(int p)
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

// 分裂操作：将以 p 为根的 Treap 分裂成两棵树 x, y
// 满足 x 中所有节点值 <= v，y 中所有节点值 > v
void split(int p, int v, int &x, int &y)
{
    if (!p)
    {
        x = y = 0;
        return;
    }
    if (tr[p].val <= v)
    {
        x = p;
        split(tr[x].r, v, tr[x].r, y);
        pushup(x);
    }
    else
    {
        y = p;
        split(tr[y].l, v, x, tr[y].l);
        pushup(y);
    }
}

// 合并操作：将两棵 Treap x, y 合并成一棵
// 要求 x 中所有节点值 <= y 中所有节点值
int merge(int x, int y)
{
    if (!x || !y)
        return x + y; // 有一棵空，直接返回另一棵
    if (tr[x].rnd < tr[y].rnd)
    {
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

// 插入操作：向 Treap 中插入键值 v
void insert(int v)
{
    int x, y, z;
    split(root, v, x, y); // 把 <= v 和 > v 分开
    newnode(z, v);        // 新建节点 z
    root = merge(merge(x, z), y);
}

// 删除操作：从 Treap 中删除键值 v 的一个节点
void remove(int v)
{
    int x, y, z;
    split(root, v, y, z);  // y: <=v, z: >v
    split(y, v - 1, x, y); // x: <v, y: =v
    // 将 y 的左右子树合并（等于 v 的节点被舍弃）
    y = merge(tr[y].l, tr[y].r);
    root = merge(merge(x, y), z);
}

// 查询操作：获取键值 v 的排名（第几小）
int getrank(int v)
{
    int x, y;
    split(root, v - 1, x, y); // x: <v, y: >=v
    int ans = tr[x].size + 1; // 第 tr[x].size+1 小
    root = merge(x, y);
    return ans;
}

// 根据排名 k 获取第 k 小的键值
int getval(int rt, int k)
{
    int ls = tr[rt].l;
    if (k == tr[ls].size + 1)
        return tr[rt].val;
    else if (k <= tr[ls].size)
        return getval(tr[rt].l, k);
    else
        return getval(tr[rt].r, k - tr[ls].size - 1);
}

// 获取前驱：小于 v 的最大键值
int getpre(int v)
{
    int x, y;
    split(root, v - 1, x, y);
    int s = tr[x].size;
    int ans = getval(x, s); // x 中第 s 小，即最大
    root = merge(x, y);
    return ans;
}

// 获取后继：大于 v 的最小键值
int getnxt(int v)
{
    int x, y;
    split(root, v, x, y);
    int ans = getval(y, 1); // y 中第 1 小
    root = merge(x, y);
    return ans;
}
/*
向 M 中插入一个数 x。
从 M 中删除一个数 x（若有多个相同的数，应只删除一个）。
查询 M 中有多少个数比 x 小，并且将得到的答案加一。
查询如果将 M 从小到大排列后，排名位于第 x 位的数。
查询 M 中 x 的前驱（前驱定义为小于 x，且最大的数）。
查询 M 中 x 的后继（后继定义为大于 x，且最小的数）。
 */
void solve()
{
    int n, op, v;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op >> v;
        if (op == 1)
            insert(v);
        else if (op == 2)
            remove(v);
        else if (op == 3)
            print(getrank(v));
        else if (op == 4)
            print(getval(root, v));
        else if (op == 5)
            print(getpre(v));
        else
            print(getnxt(v));
    }
}

// 文艺平衡树，多次区间翻转操作
// https://www.luogu.com.cn/problem/P3391
mt19937 rnd(time(nullptr));
const int N = 100010;

// 每个节点的信息
struct node
{
    int l, r; // 左、右孩子在 tr[] 数组中的下标
    int val;  // 节点保存的值（序列中的元素）
    int key;  // 随机优先级（堆的键），保证树高度期望为 O(log n)
    int size; // 以该节点为根的子树的节点数量
    int tag;  // 反转懒标记：0 表示正常，1 表示该子树需要翻转
} tr[N];

int root = 0; // 当前 Treap 的根节点下标
int idx = 0;  // 已分配的节点总数，用于 newnode 分配新节点

// 创建并返回一个新节点，值为 v
int newnode(int v)
{
    tr[++idx].val = v;         // 设置节点存储的值
    tr[idx].key = rnd();       // 随机优先级
    tr[idx].size = 1;          // 新节点子树大小为 1
    tr[idx].l = tr[idx].r = 0; // 尚无左右孩子
    tr[idx].tag = 0;           // 无反转标记
    return idx;                // 返回新节点在 tr[] 中的下标
}

// 根据孩子的 size 更新当前节点 p 的 size
void pushup(int p)
{
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

// 下推反转懒标记到孩子节点，保证子树结构正确
void pushdown(int p)
{
    if (!p || !tr[p].tag)
        return; // 空节点或无标记时跳过
    // 交换左右孩子，完成子树反转
    swap(tr[p].l, tr[p].r);
    // 将反转标记传递给左右孩子
    tr[tr[p].l].tag ^= 1;
    tr[tr[p].r].tag ^= 1;
    // 清除当前节点的标记
    tr[p].tag = 0;
}

// split：将以 p 为根的树分成两棵，左树有前 k 个节点
// 参数：p（原树根），k（左子树节点个数）
// 返回：x（左子树根），y（右子树根）
void split(int p, int k, int &x, int &y)
{
    if (!p)
    {
        x = y = 0;
        return;
    }
    pushdown(p); // 先下推，保证孩子关系正确
    if (k > tr[tr[p].l].size)
    {
        // 当前根属于左子树
        k -= tr[tr[p].l].size + 1;
        x = p;
        split(tr[p].r, k, tr[p].r, y);
    }
    else
    {
        // 当前根及右子树全部属于右子树
        y = p;
        split(tr[p].l, k, x, tr[p].l);
    }
    pushup(p); // 维护 p 的 size
}

// merge：将两棵符合 BST 性质的 Treap 合并成一棵
// x、y 分别是两棵树的根，且任意 x 中所有值 ≤ y 中所有值
int merge(int x, int y)
{
    if (!x || !y)
        return x + y; // 一方空则返回另一方
    if (tr[x].key < tr[y].key)
    {
        // x 的优先级更高，x 作为根
        pushdown(x);
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        // y 作为根
        pushdown(y);
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

// 区间反转操作：将序号区间 [l, r] 对应的子序列翻转
void reverse(int l, int r)
{
    int x, y, z;
    // 1. 按前 r 个节点分割为 x(1..r) 和 z(r+1..end)
    split(root, r, x, z);
    // 2. 再把 x 分成 x(1..l-1) 和 y(l..r)
    split(x, l - 1, x, y);
    // 3. 对 y 标记反转
    tr[y].tag ^= 1;
    // 4. 合并回原树：先合并 x 和 y，再合并 z
    root = merge(merge(x, y), z);
}

// 中序遍历输出整棵树中的值，即当前序列
void output(int p)
{
    if (!p)
        return;
    pushdown(p);     // 保证先把懒标记下推
    output(tr[p].l); // 输出左子树
    printf("%d ", tr[p].val);
    output(tr[p].r); // 输出右子树
}

void solve()
{
    int n, m;
    cin >> n >> m;
    // 初始化序列为 1..n 的 Treap
    for (int i = 1; i <= n; i++)
    {
        root = merge(root, newnode(i));
    }
    // 处理每次区间翻转
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        reverse(l, r);
    }
    // 输出最终序列
    output(root);
}
