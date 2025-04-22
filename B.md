### 翻译任务B：
**任务B. 区间最小值及其出现次数**

**输入文件名**：标准输入  
**输出文件名**：标准输出  
**时间限制**：1秒  
**内存限制**：256 MB  

现在需要修改线段树的代码，使其能够统计区间内最小值及其出现的次数。

**输入格式**：  
第一行包含两个整数 \( n \) 和 \( m \)（\( 1 \leq n, m \leq 10^5 \)），分别表示数组的大小和操作的数量。  
第二行包含 \( n \) 个整数 \( a_i \)，表示数组的初始状态（\( 0 \leq a_i \leq 10^9 \)）。  
接下来的 \( m \) 行描述操作，每行的格式如下：  
- `1 i v`：将索引为 \( i \) 的元素值修改为 \( v \)（\( 0 \leq i < n \)，\( 0 \leq v \leq 10^9 \)）。  
- `2 l r`：查询区间 \([l, r-1]\) 内的最小值及其出现次数（\( 0 \leq l < r \leq n \)）。  

**输出格式**：  
对于每个查询操作（类型2），输出两个整数：区间内的最小值和该最小值出现的次数。  

**示例**：  
| 标准输入 | 标准输出 |  
|----------|----------|  
| 5 5      | 3 2      |  
| 3 4 3 5 2 | 2 1      |  
| 2 0 3    | 2 3      |  
| 1 1 2    |          |  
| 2 0 3    |          |  
| 1 0 2    |          |  
| 2 0 5    |          |  

---

### Python代码实现：
```python
import sys

def main():
    input = sys.stdin.read().split()
    ptr = 0
    n, m = map(int, input[ptr:ptr+2])
    ptr += 2
    arr = list(map(int, input[ptr:ptr+n]))
    ptr += n

    # 构建线段树
    size = 1
    while size < n:
        size <<= 1
    min_val = [float('inf')] * (2 * size)
    count = [0] * (2 * size)

    # 初始化叶子节点
    for i in range(n):
        min_val[size + i] = arr[i]
        count[size + i] = 1
    for i in range(size - 1, 0, -1):
        left = min_val[2 * i]
        right = min_val[2 * i + 1]
        if left < right:
            min_val[i] = left
            count[i] = count[2 * i]
        elif left > right:
            min_val[i] = right
            count[i] = count[2 * i + 1]
        else:
            min_val[i] = left
            count[i] = count[2 * i] + count[2 * i + 1]

    # 更新操作
    def update(pos, value):
        pos += size
        min_val[pos] = value
        pos >>= 1
        while pos >= 1:
            left = min_val[2 * pos]
            right = min_val[2 * pos + 1]
            if left < right:
                min_val[pos] = left
                count[pos] = count[2 * pos]
            elif left > right:
                min_val[pos] = right
                count[pos] = count[2 * pos + 1]
            else:
                min_val[pos] = left
                count[pos] = count[2 * pos] + count[2 * pos + 1]
            pos >>= 1

    # 查询操作
    def query(l, r):
        res_min = float('inf')
        res_count = 0
        l += size
        r += size
        while l < r:
            if l % 2 == 1:
                if min_val[l] < res_min:
                    res_min = min_val[l]
                    res_count = count[l]
                elif min_val[l] == res_min:
                    res_count += count[l]
                l += 1
            if r % 2 == 1:
                r -= 1
                if min_val[r] < res_min:
                    res_min = min_val[r]
                    res_count = count[r]
                elif min_val[r] == res_min:
                    res_count += count[r]
            l >>= 1
            r >>= 1
        return (res_min, res_count)

    # 处理操作
    output = []
    for _ in range(m):
        parts = input[ptr:ptr+3]
        if parts[0] == '1':
            i, v = map(int, parts[1:3])
            update(i, v)
            ptr += 3
        elif parts[0] == '2':
            l, r = map(int, parts[1:3])
            res_min, res_count = query(l, r)
            output.append(f"{res_min} {res_count}")
            ptr += 3
    print('\n'.join(output))

if __name__ == "__main__":
    main()
```

### 代码说明：
1. **线段树构建**：使用数组实现线段树，每个节点存储区间内的最小值和出现次数。
2. **更新操作**：修改指定位置的值，并向上更新父节点的信息。
3. **查询操作**：查询指定区间的最小值和出现次数，通过合并左右子区间的结果得到最终答案。
4. **输入输出处理**：读取输入数据，处理更新和查询操作，输出结果。

此代码高效且符合题目要求的时间复杂度（\( O(\log n) \) 每次操作）。
