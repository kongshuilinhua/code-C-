//
// Created by elysia on 2025/5/20.
//
// https://ac.nowcoder.com/acm/contest/110312/E
// 返回 [0..n] 中，每个 popcount = k 的个数
vi getPopcountCounts(int n)
{
    vi cnt(64, 0);
    int ones = 0;
    // 从高位往低位
    for (int i = 63; i >= 0; i--)
    {
        if ((n >> i) & 1)
        {
            // 当前选0，低i位随意选择k个1
            for (int k = 0; k <= i; k++)
            {
                cnt[ones + k] += C[i][k];
                cnt[ones + k] %= mod;
            }
            // 选择1
            ones++;
        }
    }
    // 包含本身
    cnt[ones]++;
    return cnt;
}
