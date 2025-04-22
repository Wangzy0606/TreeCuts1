#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct SegmentTreeNode {
    int min_val;
    int count;
    SegmentTreeNode() : min_val(INT_MAX), count(0) {}
    SegmentTreeNode(int val) : min_val(val), count(1) {}
};

class SegmentTree {
private:
    vector<SegmentTreeNode> tree;
    int size;

    SegmentTreeNode merge(const SegmentTreeNode& left, const SegmentTreeNode& right) {
        SegmentTreeNode res;
        if (left.min_val < right.min_val) {
            res.min_val = left.min_val;
            res.count = left.count;
        } else if (left.min_val > right.min_val) {
            res.min_val = right.min_val;
            res.count = right.count;
        } else {
            res.min_val = left.min_val;
            res.count = left.count + right.count;
        }
        return res;
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = SegmentTreeNode(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node + 1, start, mid);
        build(arr, 2 * node + 2, mid + 1, end);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = SegmentTreeNode(val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node + 1, start, mid, idx, val);
        } else {
            update(2 * node + 2, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    SegmentTreeNode query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return SegmentTreeNode();
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        SegmentTreeNode left = query(2 * node + 1, start, mid, l, r);
        SegmentTreeNode right = query(2 * node + 2, mid + 1, end, l, r);
        return merge(left, right);
    }

public:
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size);
        build(arr, 0, 0, size - 1);
    }

    void update(int idx, int val) {
        update(0, 0, size - 1, idx, val);
    }

    pair<int, int> query(int l, int r) {
        SegmentTreeNode res = query(0, 0, size - 1, l, r - 1);
        return {res.min_val, res.count};
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
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            auto [min_val, count] = st.query(l, r);
            cout << min_val << " " << count << "\n";
        }
    }

    return 0;
}
