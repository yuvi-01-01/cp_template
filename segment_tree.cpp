
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

/*-------------------------------------------------------------
    SEGMENT TREE TEMPLATE (SUM, MIN, MAX VARIANTS)
    -----------------------------------------------
    -> Build Time: O(n)
    -> Query / Update Time: O(log n)
--------------------------------------------------------------*/

class SegmentTreeSum {
public:
    int n;
    vl tree;

    SegmentTreeSum(int size) {
        n = size;
        tree.assign(4 * n, 0);
    }

    // Build the tree from an array
    void build(vl &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Point Update: set arr[idx] = val
    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Range Query: sum in [l, r]
    ll query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;          // No overlap
        if (l <= start && end <= r) return tree[node]; // Complete overlap
        int mid = start + (end - start) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }
};

/*-------------------------------------------------------------
    SEGMENT TREE FOR MIN QUERY
--------------------------------------------------------------*/
class SegmentTreeMin {
public:
    int n;
    vl tree;

    SegmentTreeMin(int size) {
        n = size;
        tree.assign(4 * n, LLONG_MAX);
    }

    void build(vl &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    ll query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return LLONG_MAX;    // No overlap
        if (l <= start && end <= r) return tree[node];  // Complete overlap
        int mid = start + (end - start) / 2;
        return min(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }
};

/*-------------------------------------------------------------
    SEGMENT TREE FOR MAX QUERY
--------------------------------------------------------------*/
class SegmentTreeMax {
public:
    int n;
    vl tree;

    SegmentTreeMax(int size) {
        n = size;
        tree.assign(4 * n, LLONG_MIN);
    }

    void build(vl &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    ll query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return LLONG_MIN;    // No overlap
        if (l <= start && end <= r) return tree[node];  // Complete overlap
        int mid = start + (end - start) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }
};

/*-------------------------------------------------------------
    HOW TO USE (Example for SUM segment tree)
    ------------------------------------------
    vl arr = {1, 2, 3, 4, 5};
    int n = arr.size();

    SegmentTreeSum seg(n);
    seg.build(arr, 1, 0, n-1);   // Build tree for indices [0..n-1]

    cout << seg.query(1, 0, n-1, 1, 3); // sum of arr[1..3] = 2+3+4 = 9

    seg.update(1, 0, n-1, 2, 10);       // arr[2] = 10
    cout << seg.query(1, 0, n-1, 1, 3); // now 2+10+4 = 16

    ----------------------------------------------------------
    WHEN TO USE 0..n-1 vs 1..n:
    - If your array is 0-indexed (typical in C++), use start=0, end=n-1.
    - If your array is 1-indexed (like some competitive problems),
      use start=1, end=n.
    -> Just make sure you stay consistent in all calls (build, update, query).

    WHEN TO CALL build():
    - If you already have an initial array and want to build the tree from it.
    - If you plan to insert elements later manually, you can skip build()
      and rely on update() calls to initialize values one by one.
--------------------------------------------------------------*/
class SegmentTreeRangeUpdatePointQuery {
public:
    int n;          // size of array
    vl tree, lazy;  // tree stores values, lazy stores pending updates

    SegmentTreeRangeUpdatePointQuery(int size) {
        n = size;
        tree.assign(4*n, 0);  // segment tree requires 4*n nodes
        lazy.assign(4*n, 0);  // lazy array to store pending updates
    }

    // Lazy propagation: push pending updates to children
    void push(int node, int start, int end) {
        if(lazy[node] != 0) {
            tree[node] += lazy[node]; // apply pending increment
            if(start != end) { // propagate to children if not a leaf
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0; // clear current node's lazy value
        }
    }

    // Range update: add 'val' to all elements in [l, r]
    void range_update(int node, int start, int end, int l, int r, ll val) {
        push(node, start, end); // ensure current node is up-to-date

        if(r < start || end < l) return; // no overlap
        if(l <= start && end <= r) {     // complete overlap
            lazy[node] += val;           // store in lazy
            push(node, start, end);      // immediately apply it
            return;
        }

        // partial overlap: recur for children
        int mid = (start + end) / 2;
        range_update(2*node, start, mid, l, r, val);
        range_update(2*node+1, mid+1, end, l, r, val);
    }

    // Point query at index 'idx'
    ll point_query(int node, int start, int end, int idx) {
        push(node, start, end); // apply pending updates

        if(start == end) return tree[node]; // leaf node reached

        int mid = (start + end)/2;
        if(idx <= mid) return point_query(2*node, start, mid, idx);
        else return point_query(2*node+1, mid+1, end, idx);
    }
};

/*
int n = 8;
vl a = {0, 3, 2, 4, 5, 1, 1, 5, 3}; // 1-based indexing // Step 1: Initialize the segment tree -> SegmentTreeRangeUpdatePointQuery seg(n);
// Step 2: Set initial array values
// Treat each a[i] as a range update [i,i] += a[i]
for(int i = 1; i <= n; i++) seg.range_update(1, 1, n, i, i, a[i]);
// Step 3: Range update query
// Add 2 to all elements in range [2,5]
seg.range_update(1, 1, n, 2, 5, 2);
// Step 4: Point query
// Get value at index 4 ll val = seg.point_query(1, 1, n, 4);  // returns updated value cout << val << endl;
*/

