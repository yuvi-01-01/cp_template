// --- Snippet for Binary Lifting ---

class BinaryLifting {
    int n, LOG;
    vector<vector<int>> kthParent;
    vector<int> depth;
    vector<vector<int>> adj;

public:
    BinaryLifting(int num_nodes) {
        n = num_nodes;
        LOG = ceil(log2(n)) + 1;
        kthParent.assign(n + 1, vector<int>(LOG, 0));
        depth.assign(n + 1, 0);
        adj.assign(n + 1, {});
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS to set depths and immediate parents (k=0)
    void dfs(int v, int p) {
        kthParent[v][0] = p;
        for (int u : adj[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v);
            }
        }
    }

    // Precomputes the kthParent table for all nodes
    void preprocess(int root = 1) {
        // Step 1: Run DFS to set depths and parent pointers.
        // Assuming root is at depth 0, and its parent is a dummy node 0.
        depth[root] = 0;
        dfs(root, 0);

        // Step 2: Fill the rest of the kthParent table using DP.
        // kthParent[i][j] = 2^j-th parent of i
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                if (kthParent[i][j - 1] != 0) {
                    kthParent[i][j] = kthParent[kthParent[i][j - 1]][j - 1];
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {
        for (int j = LOG - 1; j >= 0; j--) {
            if (k & (1 << j)) {
                node = kthParent[node][j];
                if (node == 0) break; // Reached above the root
            }
        }
        return node;
    }

    int LCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        u = getKthAncestor(u, depth[u] - depth[v]);

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (kthParent[u][j] != 0 && kthParent[u][j] != kthParent[v][j]) {
                u = kthParent[u][j];
                v = kthParent[v][j];
            }
        }
        return kthParent[u][0];
    }
    
    int dist(int u, int v) {
        int lca_node = LCA(u,v);
        return depth[u] + depth[v] - 2 * depth[lca_node];
    }
};

/*
// -------------------- HOW TO USE BINARY LIFTING --------------------
//
// Inside your solve() function:
//
// 1. Get the number of nodes
//    int n;
//    cin >> n;
//
// 2. Create an instance of the class
//    BinaryLifting bl(n);
//
// 3. Add all the edges to build the tree
//    for (int i = 0; i < n - 1; ++i) {
//        int u, v;
//        cin >> u >> v;
//        bl.addEdge(u, v);
//    }
//
// 4. CRITICAL: Run the preprocessing step. THIS MUST BE DONE BEFORE ANY QUERIES.
//    bl.preprocess(); // Assuming root is 1. Or bl.preprocess(your_root_node);
//
// 5. Now you can make queries freely.
//    // Find the Lowest Common Ancestor of nodes 5 and 7
//    int lca_node = bl.LCA(5, 7);
//    cout << "LCA of 5 and 7 is: " << lca_node << endl;
//
//    // Find the 3rd ancestor of node 10
//    int ancestor = bl.getKthAncestor(10, 3);
//    cout << "3rd ancestor of 10 is: " << ancestor << endl;
//
//    // Find distance between two nodes
//    int distance = bl.dist(5, 7);
//    cout << "Distance between 5 and 7 is: " << distance << endl;
*/
