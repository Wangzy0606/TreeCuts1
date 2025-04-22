### 任务F：逆序对三元组计数

#### 问题描述
给定一个包含n个整数的数组，计算满足i < j < k且a[i] > a[j] > a[k]的三元组(i,j,k)的数量。

#### 输入格式
- 第一行：整数n（3 ≤ n ≤ 10^5）
- 第二行：n个整数a_i（1 ≤ a_i ≤ 10^9）

#### 输出格式
- 输出满足条件的三元组数量

#### 示例
输入：
```
4
10 8 3 1
```
输出：
```
4
```

### C++代码实现
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int size;

public:
    FenwickTree(int n) : size(n), tree(n + 2) {}

    void update(int pos, int val) {
        for (; pos <= size; pos += pos & -pos)
            tree[pos] += val;
    }

    int query(int pos) {
        int res = 0;
        for (; pos > 0; pos -= pos & -pos)
            res += tree[pos];
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    // 坐标压缩
    vector<int> temp = a;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    map<int, int> rank;
    for (int i = 0; i < temp.size(); ++i)
        rank[temp[i]] = i + 1;

    // 计算每个元素右边比它小的元素个数
    vector<int> right_smaller(n);
    FenwickTree ft1(temp.size());
    for (int i = n - 1; i >= 0; --i) {
        int r = rank[a[i]] - 1;
        right_smaller[i] = ft1.query(r);
        ft1.update(rank[a[i]], 1);
    }

    // 计算每个元素左边比它大的元素个数，并累加结果
    long long res = 0;
    FenwickTree ft2(temp.size());
    for (int i = 0; i < n; ++i) {
        int r = rank[a[i]];
        int left_larger = ft2.query(temp.size()) - ft2.query(r);
        res += 1LL * left_larger * right_smaller[i];
        ft2.update(r, 1);
    }

    cout << res << "\n";
    return 0;
}
```

### 代码说明

1. **坐标压缩**：
   - 将原始数据映射到紧凑的整数范围，便于树状数组处理
   - 使用排序和去重，然后建立值到排名的映射

2. **树状数组类**：
   - 支持单点更新和前缀查询
   - 用于高效计算逆序对数量

3. **计算右边较小元素**：
   - 从右向左遍历数组
   - 使用树状数组统计已处理元素中比当前元素小的数量
   - 结果存储在right_smaller数组中

4. **计算左边较大元素并累加结果**：
   - 从左向右遍历数组
   - 使用另一个树状数组统计已处理元素中比当前元素大的数量
   - 将左边较大元素数量与右边较小元素数量相乘，累加到最终结果

5. **复杂度分析**：
   - 时间复杂度：O(n log n)（主要来自排序和树状数组操作）
   - 空间复杂度：O(n)

该实现能够高效处理最大规模的数据，满足题目要求的性能约束。
