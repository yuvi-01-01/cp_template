class DSU {
    vector<int> parent, size;
    int components;  // Tracks number of disjoint sets (useful for quick checks)
public:
    
    DSU(int n) {
        size.assign(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
        components = n; // Initially, each node is its own component
    }

    // Finds the ultimate parent of a node (with path compression)
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Unites two sets by size (smaller set merges into larger one)
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return; // Already in same set

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }

        components--; // One less distinct component after union
    }

    // Returns true if all nodes are in one connected component
    bool allConnected() const {
        return components == 1;
    }

    // Returns true if u and v belong to the same component
    bool sameSet(int u, int v) {
        return findUPar(u) == findUPar(v);
    }

    // Returns the size of the component containing u
    int getSize(int u) {
        return size[findUPar(u)];
    }

    // Returns how many components currently exist
    int getComponents() const {
        return components;
    }
};


