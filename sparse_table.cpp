class SparseTable {
    vector<vl> st; vl log_table; int n; char type;
    ll merge(ll a, ll b) {
        if (type == 'm') return min(a, b); if (type == 'x') return max(a, b);
        if (type == 'g') return gcd(a, b); return a;
    }
public:
    SparseTable(const vl& v, char op_type) {
        n = v.size(); type = op_type; log_table.resize(n + 1); log_table[1] = 0;
        for (int i = 2; i <= n; i++) log_table[i] = log_table[i / 2] + 1;
        int max_log = log_table[n]; st.assign(n, vl(max_log + 1));
        for (int i = 0; i < n; i++) st[i][0] = v[i];
        for (int j = 1; j <= max_log; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[i][j] = merge(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    ll query(int l, int r) {
        int j = log_table[r - l + 1];
        return merge(st[l][j], st[r - (1 << j) + 1][j]);
    }
};
// How to use SparseTable:
// vl vec = {2, 5, 1, 8, 3, 9};
// SparseTable st(vec, 'm'); // For min query
// ll minimum = st.query(1, 4); // min over {5,1,8,3} -> 1
