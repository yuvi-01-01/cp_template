class BIT {
public:
//// Initialize BIT with array --> for(int i=1;i<=n;i++) bit.update(i, a[i]); for range sum query and point update
    int n;
    vl tree;
    BIT(int size){
        n=size+2; //safe
        tree.assign(n,0);
    }
    void update(int idx,ll delta){
        while(idx<n){
            tree[idx] += delta;
            idx += rsb(idx);
        }
    }
    ll presum(int idx){
        ll res=0;
        while(idx > 0){
            res += tree[idx];
            idx -= rsb(idx);
        }
        return res;
    }
    ll query(int l,int r){
        return presum(r)-presum(l-1);
    }
    int rsb(int i){
        return (i & (-i));
    }  
};

class BIT_PointQueryRangeUpdate {
public:
    int n;
    vl tree;
    BIT_PointQueryRangeUpdate(int size) {
        n = size + 2; // safe
        tree.assign(n, 0);
    }
    // Internal: least significant bit
    int rsb(int i) {
        return i & -i;
    }
    // Point update in BIT
    void update(int idx, ll delta) {
        while (idx < n) {
            tree[idx] += delta;
            idx += rsb(idx);
        }
    }
    // Prefix sum query
    ll presum(int idx) {
        ll res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= rsb(idx);
        }
        return res;
    }
    // Range update [l,r] += delta
    void range_update(int l, int r, ll delta) {
        update(l, delta);
        update(r + 1, -delta);
    }
    // Point query at idx
    ll point_query(int idx) {
        return presum(idx);
    }
};

//int n = 8; BIT bit(n);
//for (int i = 1; i <= 8; i++)  bit.range_update(i, i, a[i]);
// Initial array vl a = {0, 3, 2, 4, 5, 1, 1, 5, 3}; // 1-based, 0 ignore
// Query type 1: range update [2,5] += 1   --> bit.range_update(2, 5, 1);
// Query type 2: point query at index 4--> ll val = a[4] + bit.point_query(4); // val = 5 + 1 = 6 
