
class SegmentTree{
public:
    int n;
    vl tree;
    SegmentTree(int size){
        n=size;
        tree.assign(4*n,0);
    }
    void build(vl &arr , int node, int start,int end){
        if(start==end) {
            tree[node]=arr[start];
            return;
        }
        int mid = start + ((end-start)/2) ;
        build(arr,2*node,start,mid);
        build(arr,2*node + 1,mid+1,end);
        tree[node]= tree[2*node] + tree[2*node + 1];
    }
    void update(int node,int start,int end,int idx,int val){
        if(start==end) {
            //reached the node in segment tree corresponding to idx,nothing but in[s].
            tree[node]=val; 
            return;
    //also need to update accordingly the rest of the segment tree after reaching base case,
    //which is nothing but kinda building the segment tree only
        }
        int mid = start + ((end-start)/2) ;
        if(idx<=mid) update(2*node,start,mid,idx,val);
        else update(2*node+1,mid+1,end,idx,val);
        tree[node]= tree[2*node] + tree[2*node + 1];
    }
    ll query(int node,int start,int end,int l,int r){
        if(l<=start && r>=end) return tree[node];
        if(r< start || l >end) return 0;
        int mid = start + ((end-start)/2) ;
        return query(2*node,start,mid,l,r) + query(2*node +1, mid+1,end,l,r);
    }
    
};
