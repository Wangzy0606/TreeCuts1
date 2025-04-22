### 翻译任务C：
**任务C. 第K个1的位置**

**输入文件名**：标准输入  
**输出文件名**：标准输出  
**时间限制**：1秒  
**内存限制**：256 MB  

在这道题中，你需要在线段树中实现一个操作：找到数组中第K个1的位置（索引从0开始计数）。

**输入格式**：  
第一行包含两个整数n和m（1 ≤ n, m ≤ 10^5），分别表示数组大小和操作次数。  
第二行包含n个整数a_i（a_i ∈ {0,1}），表示数组的初始状态。  
接下来m行描述操作，每行格式如下：  
- `1 i`：将索引为i的元素取反（0变1，1变0）  
- `2 k`：查询第k个1的位置（保证数组中至少有k+1个1）

**输出格式**：  
对于每个查询操作（类型2），输出第k个1的索引。

**示例**：
| 标准输入 | 标准输出 |
|----------|----------|
| 5 7      | 0        |
| 1 1 0 1 0 | 1        |
| 2 0      | 3        |
| 2 1      | 3        |
| 2 2      | 1        |
| 1 2      |          |
| 2 3      |          |
| 1 0      |          |
| 2 0      |          |

### C++代码实现：
```cpp
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
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

    void update(int node, int start, int end, int idx) {
        if (start == end) {
            tree[node] ^= 1; // Flip the bit
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2*node+1, start, mid, idx);
        } else {
            update(2*node+2, mid+1, end, idx);
        }
        tree[node] = tree[2*node+1] + tree[2*node+2];
    }

    int query(int node, int start, int end, int k) {
        if (start == end) {
            return start;
        }
        int mid = (start + end) / 2;
        if (k < tree[2*node+1]) {
            return query(2*node+1, start, mid, k);
        } else {
            return query(2*node+2, mid+1, end, k - tree[2*node+1]);
        }
    }

public:
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4*size);
        build(arr, 0, 0, size-1);
    }

    void flip(int idx) {
        update(0, 0, size-1, idx);
    }

    int findKthOne(int k) {
        return query(0, 0, size-1, k);
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
            int i;
            cin >> i;
            st.flip(i);
        } else {
            int k;
            cin >> k;
            cout << st.findKthOne(k) << "\n";
        }
    }

    return 0;
}
```

### 代码说明：
1. **线段树结构**：
   - 使用数组实现线段树，每个节点存储子树的1的个数
   - 支持两种操作：翻转某个位置的bit和查询第k个1的位置

2. **核心操作**：
   - `build()`：递归构建线段树
   - `update()`：递归更新指定位置的bit值
   - `query()`：递归查询第k个1的位置

3. **优化**：
   - 使用快速输入输出（ios_base::sync_with_stdio）
   - 线段树空间预分配为4*n大小

4. **时间复杂度**：
   - 构建：O(n)
   - 更新和查询：O(logn)每次操作

这个实现完全符合题目要求，能够高效处理大规模数据。
