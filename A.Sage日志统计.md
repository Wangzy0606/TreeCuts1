### 翻译任务A：
**任务A. Sage日志统计**

**输入文件名**：标准输入  
**输出文件名**：标准输出  
**时间限制**：1秒  
**内存限制**：256 MB  

在T-Bank的Sage日志监控系统中，需要统计不同时间段内的日志数量。系统需要支持以下两种操作：
1. 修改某个时间点的日志数量
2. 查询某个时间区间的日志总数

**输入格式**：
- 第一行：n m（1 ≤ n, m ≤ 10^5），表示时间点数量和操作次数
- 第二行：n个整数a_i（0 ≤ a_i ≤ 10^9），表示初始各时间点的日志数
- 接下来m行操作：
  - `1 i v`：将第i个时间点的日志数改为v（0 ≤ i < n，0 ≤ v ≤ 10^9）
  - `2 l r`：查询[l,r)区间内的日志总数（0 ≤ l < r ≤ n）

**输出格式**：
对每个查询操作输出区间日志总数

**示例**：
| 标准输入 | 标准输出 |
|----------|----------|
| 5 5      | 11       |
| 5 4 2 3 5 | 8        |
| 2 0 3    | 14       |
| 1 1 1    |          |
| 2 0 3    |          |
| 1 3 1    |          |
| 2 0 5    |          |

### C++代码实现：
```cpp
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<long long> tree;
    int size;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2*node+1, start, mid);
        build(arr, 2*node+2, mid+1, end);
        tree[node] = tree[2*node+1] + tree[2*node+2];
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2*node+1, start, mid, idx, val);
        } else {
            update(2*node+2, mid+1, end, idx, val);
        }
        tree[node] = tree[2*node+1] + tree[2*node+2];
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return query(2*node+1, start, mid, l, r) + 
               query(2*node+2, mid+1, end, l, r);
    }

public:
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4*size);
        build(arr, 0, 0, size-1);
    }

    void update(int idx, int val) {
        update(0, 0, size-1, idx, val);
    }

    long long query(int l, int r) {
        return query(0, 0, size-1, l, r-1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree st(arr);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, v;
            cin >> i >> v;
            st.update(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << "\n";
        }
    }

    return 0;
}
```

### 代码说明：
1. **线段树实现**：
   - 使用数组存储线段树节点
   - 每个节点存储对应区间的和
   - 支持O(logn)时间的单点更新和区间查询

2. **核心功能**：
   - `build()`：递归构建线段树
   - `update()`：更新指定位置的日志数
   - `query()`：查询区间日志总数

3. **优化措施**：
   - 使用快速输入输出（ios_base::sync_with_stdio）
   - 使用long long防止求和溢出
   - 线段树空间预分配为4*n

4. **时间复杂度**：
   - 构建：O(n)
   - 更新和查询：O(logn)每次操作

该实现能够高效处理题目要求的大规模数据操作，完全符合题目要求的时间限制。
