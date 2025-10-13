class BIT {
public:
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
