// ---------------------------- ALGORITHMIC HELPERS ----------------------------------- //
set<ll> get_all_subarray_ors(const vl& arr) {
    set<ll> total_ors; set<ll> current_ors;
    for (ll x : arr) {
        set<ll> next_ors; next_ors.insert(x);
        for (ll val : current_ors) { next_ors.insert(val | x); }
        current_ors = next_ors;
        for (ll val : current_ors) total_ors.insert(val);
    } return total_ors;
}
set<ll> get_all_subarray_ands(const vl& arr) {
    set<ll> total_ands; set<ll> current_ands;
    for (ll x : arr) {
        set<ll> next_ands; next_ands.insert(x);
        for (ll val : current_ands) { next_ands.insert(val & x); }
        current_ands = next_ands;
        for (ll val : current_ands) total_ands.insert(val);
    } return total_ands;
}
// How to use Subarray Bitwise Helpers:
// Finds all unique values from bitwise OR/AND of all contiguous subarrays.
// vl my_arr = {6, 1, 3, 7};
// set<ll> results = get_all_subarray_ors(my_arr); // results will contain {1, 3, 6, 7}

ll countSetBitsUptoN(ll n) {
    if (n < 0) return 0; if (n == 0) return 0;
    ll x = floor(log2(n)); ll ans = (x * (1LL << (x - 1))) + (n - (1LL << x) + 1) + countSetBitsUptoN(n - (1LL << x));
    return ans;
}
// How to use countSetBitsUptoN:
// Counts total number of set bits in all numbers from 1 to N.
// ll total_bits = countSetBitsUptoN(5); // 1(1) + 2(1) + 3(2) + 4(1) + 5(2) -> 7

/*
// ---- How to iterate all submasks of a mask ----
for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
    // do stuff with submask
}
// ---- How to iterate all masks and their submasks ----
for (int mask = 0; mask < (1 << n); mask++) {
    for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
        // do stuff
    }
}
*/

// ---------------------------- BIT MANIPULATION UTILS -------------------------------- //
ll countSetBits(ll n) { return __builtin_popcountll(n); }
ll getMSB(ll n) { return (n == 0) ? -1 : (63 - __builtin_clzll(n)); }
ll getLSB(ll n) { return (n == 0) ? -1 : __builtin_ctzll(n); }
bool isPowerOfTwo(ll n) { return (n > 0) && ((n & (n - 1)) == 0); }
ll removeLastSetBit(ll n) { return n & (n - 1); }
ll setKthBit(ll n, int k) { return n | (1LL << k); }
ll clearKthBit(ll n, int k) { return n & ~(1LL << k); }
ll toggleKthBit(ll n, int k) { return n ^ (1LL << k); }
bool isKthBitSet(ll n, int k) { return (n >> k) & 1; }
ll getLastSetBit(ll n) { return n & -n; }
// How to use getLastSetBit:
// ll num = 12; // Binary: 1100
// ll res = getLastSetBit(num); // res is 4 (0100)

// ---------------------------- CUSTOM COMPARATORS ------------------------------------ //
bool comparePairs(const pii& a, const pii& b) {
    if (a.f != b.f) return a.f < b.f;
    return a.s < b.s;
}
// vpi vec = {{1, 5}, {1, 2}, {2, 3}};
// sort(all(vec), comparePairs); // Sorts to {{1,2}, {1,5}, {2,3}}

bool comparePairsBySecond(const pii& a, const pii& b) { return a.s < b.s; }
// vpi vec = {{3, 5}, {1, 2}, {4, 3}};
// sort(all(vec), comparePairsBySecond); // Sorts to {{1,2}, {4,3}, {3,5}}

bool sortByStringLength(const string& a, const string& b) { return a.size() < b.size(); }
// vs s_vec = {"abc", "a", "ab"};
// sort(all(s_vec), sortByStringLength); // Sorts to {"a", "ab", "abc"}

//probability based coding
ll modpow ( ll a , ll b ) {ll res = 1;a %= MOD ; while ( b > 0) { if ( b & 1) res = ( res * a ) % MOD ; a = ( a * a ) % MOD ; b >>= 1; } return res ;}
ll modinv ( ll q ) { return modpow (q , MOD - 2) ; }
/*
double p = 5 , q = 7;
 double prob = p / q ;
 cout << fixed << setprecision (6) << prob << endl ;
    */
