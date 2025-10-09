
class DSU {
    vi  parent, size;
public:
    DSU(int n) {
         size.assign(n + 1, 1);
        parent.resize(n + 1); for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u); int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) { parent[ulp_u] = ulp_v; size[ulp_v] += size[ulp_u]; }
        else { parent[ulp_v] = ulp_u; size[ulp_u] += size[ulp_v]; }
    }
   //int getSize(int u) {return size[findUpar(u)];}
    
};
// How to use DSU:
// DSU dsu(10); dsu.unionBySize(1, 2);
