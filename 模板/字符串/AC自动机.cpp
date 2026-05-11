//
// Created by elysia on 2025/5/15.
//
// https://www.luogu.com.cn/problem/P3808
/*
 * 给定 n 个模式串 si和一个文本串 t，求有多少个不同的模式串在文本串里出现过。两个模式串不同当且仅当他们编号不同。
 */
const int N = 1e6 + 10;
// 回跳边指向父节点的回跳边所指结点的儿子 （四边形）  回跳边所指结点一定是当前结点的最长后缀
// 转移边指向当前节点回跳边所指结点的儿子  （三角形） 转移边所指结点一定是当前结点的最短路  yasherhshe  she转移到her
int ch[N][26]; // ch[u][i] 结点u树边的终点（有儿子） 或 结点u转移边的终点（没儿子）
int cnt[N];
int ne[N]; // ne[v]: 结点v的回跳边的终点
int tot;
void insert(string &s)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = s[i] - 'a';
        if (!ch[p][j])
            ch[p][j] = ++tot;
        p = ch[p][j];
    }
    cnt[p]++;
}

void build()
{
    queue<int> q;
    // 根节点的儿子们入队
    for (int i = 0; i < 26; i++)
    {
        if (ch[0][i])
            q.push(ch[0][i]);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        // 枚举u的26个儿子
        for (int i = 0; i < 26; i++)
        {
            int v = ch[u][i];
            // 如果儿子存在，父亲帮儿子建立回跳边，并且儿子入队
            if (v)
            {
                ne[v] = ch[ne[u]][i]; // 指向父亲的回跳边的儿子
                q.push(v);
            }
            else
            {
                ch[u][i] = ch[ne[u]][i]; // 儿子不存在，父亲自建转移边
            }
        }
    }
}

int query(string &s)
{
    int res = 0;
    int i = 0;
    // 扫描主串，依次取出s[k]
    for (int k = 0; k < s.size(); k++)
    {
        i = ch[i][s[k] - 'a']; // i指针走树边或转移边
        // j指针沿着回跳边搜索，把所有后缀模式串全搜一遍
        for (int j = i; j != 0 && cnt[j] != -1; j = ne[j])
        {
            res += cnt[j];
            cnt[j] = -1; // 清空标记
        }
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    string s, t;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        insert(s);
    }
    cin >> t;
    build();
    print(query(t));
}
// https://www.luogu.com.cn/problem/P3796
/*
 * 有 N 个由小写字母组成的模式串以及一个文本串 T。每个模式串可能会在文本串中出现多次。你需要找出哪些模式串在文本串 T 中出现的次数最多。
 */
const int N = 150 * 70 + 10;
// 回跳边指向父节点的回跳边所指结点的儿子 （四边形）  回跳边所指结点一定是当前结点的最长后缀
// 转移边指向当前节点回跳边所指结点的儿子  （三角形） 转移边所指结点一定是当前结点的最短路  yasherhshe  she转移到her
int ch[N][26]; // ch[u][i] 结点u树边的终点（有儿子） 或 结点u转移边的终点（没儿子）
int cnt[N];
int ne[N]; // ne[v]: 结点v的回跳边的终点
int tot;
unordered_map<int, int> mp;
unordered_map<int, int> freq;
int insert(string &s)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = s[i] - 'a';
        if (!ch[p][j])
            ch[p][j] = ++tot;
        p = ch[p][j];
    }
    cnt[p]++;
    return p;
}

void build()
{
    queue<int> q;
    // 根节点的儿子们入队
    for (int i = 0; i < 26; i++)
    {
        if (ch[0][i])
            q.push(ch[0][i]);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        // 枚举u的26个儿子
        for (int i = 0; i < 26; i++)
        {
            int v = ch[u][i];
            // 如果儿子存在，父亲帮儿子建立回跳边，并且儿子入队
            if (v)
            {
                ne[v] = ch[ne[u]][i]; // 指向父亲的回跳边的儿子
                q.push(v);
            }
            else
            {
                ch[u][i] = ch[ne[u]][i]; // 儿子不存在，父亲自建转移边
            }
        }
    }
}

int query(string &s)
{
    int res = 0;
    int i = 0;
    // 扫描主串，依次取出s[k]
    for (int k = 0; k < s.size(); k++)
    {
        i = ch[i][s[k] - 'a']; // i指针走树边或转移边
        // j指针沿着回跳边搜索，把所有后缀模式串全搜一遍
        for (int j = i; j != 0 && cnt[j] != -1; j = ne[j])
        {
            freq[mp[j]]++;
        }
    }
    return res;
}

void init()
{
    tot = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 26; j++)
            ch[i][j] = 0;
        ne[i] = cnt[i] = 0;
    }
    mp.clear();
    freq.clear();
}
void solve()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        init();
        string s, t;
        vector<string> a(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            mp[insert(a[i])] = i;
        }
        cin >> t;
        build();
        query(t);
        int mx = 0;
        for (auto &[k, v] : freq)
            if (1 <= k && k <= n)
                mx = max(mx, v);
        print(mx);
        for (int i = 1; i <= n; i++)
            if (freq[i] == mx)
                print(a[i]);
    }
}

// https://www.luogu.com.cn/problem/P5357
// 给你一个文本串 S 和 n 个模式串 T1∼n请你分别求出每个模式串 Ti 在 S 中出现的次数。
const int N = 2e5 + 10;
// ch[u][i] 结点u树边的终点（有儿子） 或 结点u转移边的终点（没儿子）
int ch[N][26];
int cnt[N];
int in[N];
int ne[N]; // ne[v] 表示结点v的fail指针
int tot;
unordered_map<int, int> mp;
unordered_map<int, int> freq;
unordered_map<int, int> flag;
int res[N];

int insert(string &s, int idx)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = s[i] - 'a';
        if (!ch[p][j])
            ch[p][j] = ++tot;
        p = ch[p][j];
    }
    cnt[p]++;
    if (!flag[p])
        flag[p] = idx;
    mp[idx] = flag[p];
    return p;
}

void build()
{
    queue<int> q;
    // 根节点的儿子们入队
    for (int i = 0; i < 26; i++)
    {
        if (ch[0][i])
            q.push(ch[0][i]);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        // 枚举u的26个儿子
        for (int i = 0; i < 26; i++)
        {
            int v = ch[u][i];
            // 如果儿子存在，建立fail指针，并且儿子入队
            if (v)
            {
                ne[v] = ch[ne[u]][i]; // 指向父节点fail的儿子
                in[ne[v]]++;
                q.push(v);
            }
            else
            {
                ch[u][i] = ch[ne[u]][i]; // 儿子不存在，设为父节点fail的转移
            }
        }
    }
}

void topu()
{
    queue<int> q;
    for (int i = 1; i <= tot; i++)
        if (in[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        freq[flag[u]] = res[u];
        int v = ne[u];
        in[v]--;
        res[v] += res[u];
        if (in[v] == 0)
            q.push(v);
    }
}

void query(string &s)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        p = ch[p][s[i] - 'a'];
        res[p]++;
    }
}

void init()
{
    tot = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 26; j++)
            ch[i][j] = 0;
        ne[i] = cnt[i] = 0;
        res[i] = 0;
    }
    mp.clear();
    freq.clear();
}

void solve()
{
    int n;
    cin >> n;
    init();
    string s, t;
    vector<string> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        insert(a[i], i);
    }
    cin >> t;
    build();
    query(t);
    topu();
    for (int i = 1; i <= n; i++)
        print(freq[mp[i]]);
}