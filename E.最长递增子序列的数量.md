### 翻译任务E：
**任务E. 最长递增子序列的数量**

**输入文件名**：标准输入  
**输出文件名**：标准输出  
**时间限制**：1秒  
**内存限制**：256 MB  

给定一个长度为n的整数序列，需要计算其最长递增子序列（LIS）的数量。由于结果可能很大，请输出其对10^9+7取模的结果。

**输入格式**：
- 第一行：n（1 ≤ n ≤ 10^5）
- 第二行：n个整数a_i（|a_i| ≤ 10^9）

**输出格式**：
- 输出最长递增子序列的数量（模10^9+7）

**示例**：
| 标准输入 | 标准输出 |
|----------|----------|
| 5        | 1        |
| 1 2 3 4 5 |          |
| 6        | 8        |
| 1 1 2 2 3 3 |          |

### C++代码实现：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MOD = 1e9 + 7;

struct Node {
    int len;    // LIS长度
    int cnt;    // 数量
    Node() : len(0), cnt(0) {}
    Node(int l, int c) : len(l), cnt(c) {}
};

class FenwickTree {
private:
    vector<Node> tree;
    int size;

    Node merge(Node a, Node b) {
        if (a.len == b.len) {
            return a.len == 0 ? Node(0, 0) : Node(a.len, (a.cnt + b.cnt) % MOD);
        }
        return a.len > b.len ? a : b;
    }

    void update(int pos, Node val) {
        for (; pos <= size; pos += pos & -pos) {
            tree[pos] = merge(tree[pos], val);
        }
    }

    Node query(int pos) {
        Node res;
        for (; pos > 0; pos -= pos & -pos) {
            res = merge(res, tree[pos]);
        }
        return res;
    }

public:
    FenwickTree(int n) : size(n), tree(n + 1) {}

    void update(int pos, int len, int cnt) {
        update(pos, Node(len, cnt));
    }

    pair<int, int> query(int pos) {
        Node res = query(pos);
        return {res.len, res.cnt};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 坐标压缩
    vector<int> temp = a;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    map<int, int> rank;
    for (int i = 0; i < temp.size(); ++i) {
        rank[temp[i]] = i + 1;
    }

    FenwickTree ft(temp.size());
    vector<pair<int, int>> dp(n);  // {length, count}

    for (int i = 0; i < n; ++i) {
        int r = rank[a[i]] - 1;
        auto [len, cnt] = r > 0 ? ft.query(r) : make_pair(0, 0);
        if (len == 0) {
            dp[i] = {1, 1};
        } else {
            dp[i] = {len + 1, cnt};
        }
        ft.update(rank[a[i]], dp[i].first, dp[i].second);
    }

    auto [max_len, total] = ft.query(temp.size());
    cout << (max_len == 0 ? 0 : total) << "\n";

    return 0;
}
```

### 代码说明：
1. **算法思路**：
   - 使用动态规划结合树状数组
   - 首先对数据进行坐标压缩（离散化）
   - 树状数组维护以当前值为结尾的LIS信息

2. **关键数据结构**：
   - `FenwickTree`：树状数组，存储{长度,数量}对
   - `Node`结构体：存储LIS长度和对应数量

3. **处理流程**：
   - 坐标压缩处理大范围数据
   - 遍历数组，查询比当前值小的最大LIS信息
   - 更新当前值的LIS信息到树状数组
   - 最后查询全局最大值对应的数量

4. **复杂度分析**：
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)

该实现能够高效处理题目要求的大规模数据，满足时间限制要求。
