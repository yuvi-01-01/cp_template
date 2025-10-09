class MosAlgorithm {
private:
    struct Query {
        int l, r, id, block;
    };

    vector<Query> queries;
    int n;

public:
    // Constructor: Takes the size of the array
    MosAlgorithm(int array_size) {
        n = array_size;
    }
    
    // Add a query for the 0-indexed range [l, r]
    void add_query(int l, int r) {
        int block_size = sqrt(n);
        queries.push_back({l, r, (int)queries.size(), l / block_size});
    }

    // Process all queries and return answers in original order
    vector<int> solve(
        const function<void(int)>& add,
        const function<void(int)>& remove,
        const function<int()>& get_answer
    ) {
        // Sort queries
        sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
            if (a.block != b.block) {
                return a.block < b.block;
            }
            // Serpentine ordering for odd blocks to optimize pointer movement
            if (a.block % 2) {
                return a.r > b.r;
            }
            return a.r < b.r;
        });

        vector<int> answers(queries.size());
        int curL = 0, curR = -1;

        for (const auto& q : queries) {
            while (curL > q.l) add(--curL);
            while (curR < q.r) add(++curR);
            while (curL < q.l) remove(curL++);
            while (curR > q.r) remove(curR--);
            answers[q.id] = get_answer();
        }
        return answers;
    }
};

// ================= How to use MosAlgorithm ===================
//
// Problem: Count distinct elements in ranges on an array 'a'.
//
// // 1. Define state variables and the functions that modify them.
// vector<int> a;
// vector<int> freq;
// int distinct_count = 0;
//
// void add(int idx) {
//     if (freq[a[idx]] == 0) distinct_count++;
//     freq[a[idx]]++;
// }
//
// void remove_fn(int idx) { // Renamed to avoid conflict with std::remove
//     freq[a[idx]]--;
//     if (freq[a[idx]] == 0) distinct_count--;
// }
//
// int get_answer() {
//     return distinct_count;
// }
//
// // 2. In your main logic:
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//
//     int n, q;
//     cin >> n >> q;
//     a.resize(n);
//     for (int i = 0; i < n; ++i) cin >> a[i];
//
//     // Initialize problem-specific state
//     freq.assign(1000001, 0);
//
//     // Create the MosAlgorithm object
//     MosAlgorithm mo(n);
//
//     // Add all your 0-indexed queries
//     for (int i = 0; i < q; ++i) {
//         int l, r;
//         cin >> l >> r; // read 1-indexed
//         mo.add_query(l - 1, r - 1);
//     }
//
//     // Solve and get answers
//     vector<int> answers = mo.solve(add, remove_fn, get_answer);
//
//     // Print answers in their original order
//     for (int ans : answers) {
//         cout << ans << '\n';
//     }
//     return 0;
// }

