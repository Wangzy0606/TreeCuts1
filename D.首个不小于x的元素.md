### 翻译任务D：
**任务D. 首个不小于X的元素**

**输入文件名**：标准输入  
**输出文件名**：标准输出  
**时间限制**：1秒  
**内存限制**：256 MB  

在这道题中，你需要在线段树中实现一个操作：对于给定的x和l，找到满足j ≥ l且a[j] ≥ x的最小索引j。

**输入格式**：
- 第一行包含两个整数n和m（1 ≤ n, m ≤ 10^5）
- 第二行包含n个整数a_i（0 ≤ a_i ≤ 10^9）
- 接下来m行描述操作：
  - `1 i v`：将a[i]修改为v
  - `2 x l`：查询满足j ≥ l且a[j] ≥ x的最小索引j

**输出格式**：
对于每个查询操作（类型2），输出满足条件的最小索引j（如果没有则输出-1）

**示例**：
| 标准输入 | 标准输出 |
|----------|----------|
| 5 7      | 1        |
| 1 3 2 4 3 | 3        |
| 2 3 0    | 2        |
| 2 3 2    | -1       |
| 2 5 2    | 3        |
| 2 4 1    |          |
| 1 2 5    |          |
| 2 4 1    |          |
| 1 3 7    |          |
| 2 6 1    |          |

### C++代码实现：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int size;
    const int INF = 1e9 + 7;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2*node+1, start, mid);
        build(arr, 2*node+2, mid+1, end);
        tree[node] = max(tree[2*node+1], tree[2*node+2]);
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
        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }

    int query(int node, int start, int end, int l, int r, int x) {
        if (r < start || end < l) return -1;
        if (tree[node] < x) return -1;
        if (start == end) return start;
        
        int mid = (start + end) / 2;
        int left = query(2*node+1, start, mid, l, r, x);
        if (left != -1) return left;
        return query(2*node+2, mid+1, end, l, r, x);
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

    int query(int x, int l) {
        return query(0, 0, size-1, l, size-1, x);
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
            int x, l;
            cin >> x >> l;
            int res = st.query(x, l);
            cout << res << "\n";
        }
    }

    return 0;
}
```

### 代码说明：
1. **线段树结构**：
   - 每个节点存储区间的最大值
   - 支持单点更新和区间查询

2. **核心操作**：
   - `build()`：递归构建线段树
   - `update()`：递归更新指定位置的值
   - `query()`：递归查询满足条件的最小索引

3. **查询优化**：
   - 优先搜索左子树（保证找到最小的j）
   - 利用最大值剪枝（如果区间最大值<x则直接返回-1）

4. **时间复杂度**：
   - 构建：O(n)
   - 更新和查询：O(logn)每次操作

这个实现能够高效处理题目要求的大规模数据查询，满足时间限制要求。
