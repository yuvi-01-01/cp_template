// small template
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_set_desc = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
// unordered_map<int, ordered_set<pair<int,int>>> mpp;
//int l = s.order_of_key({startTime, INT_MIN});   // elements < (startTime, -∞)
//int r = s.order_of_key({endTime + 1, INT_MIN}); // elements < (endTime+1, -∞)
//return r - l; // O(log n) //oset<int> s;  s.insert(5); s.insert(2);s.insert(8);
//cout << s.order_of_key(6) << "\n"; // elements < 6 => 2 (2 and 5)-> no_of_elements_less_than_6
//cout << s.find_by_order(1) << "\n"; // 0-based index 1 => 5 -> 1st_element_in_set
// NUMBER OF ELEMENTS B/W S1 and S2 such that S1<=x<=S2 --> int cnt = s.order_of_key(s2 + 1) - s.order_of_key(s1);
// ORDERED_MULTISET just store as pair say {S,i} where i is index and in order_of_key do {s2+1,-1} and {s1,-1}
//set<int> posns; multiset<int> lengths;
// auto it = posns.lower_bound(light); // first >= light int right = *it; it--; int left = *it; --> can do like this
//lengths.erase(lengths.find(right - left));---> remove one occurence, without .find removes all occurences
//*lengths.rbegin() --> accessing last element of any set/multiset/oset
// auto itTop = prev(top.end());  accessing last element, forward iterator to last element can erase directly unlike rbegin
// set<int> st = {1,2,3,4,5,6};auto it = st.begin();
//while (it != st.end()) {
//    if (*it % 2 == 0) it = st.erase(it);  // remove even number
//     else it++;}
// Safe erase while iterating over set/map: erase(it) removes the element at 'it'  AND returns iterator to next element
// ->use: it = st.erase(it);  ->//Never do: st.erase(it); it++;  // 'it' becomes invalid → UB

typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define fo(i, n) for (ll i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define f first
#define s second 
#define oset ordered_set
#define mset multiset
const ll MOD = 1e9 + 7;  const ll INF = 1e18;

// Random number generator (for randomized algorithms, e.g. random sampling in queries)
// mt19937 is a high-quality 32-bit Mersenne Twister PRNG (better than rand())
// chrono::steady_clock ensures different seeds every run
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// To generate a random integer in [L, R]: --> int x = uniform_int_distribution<int>(L, R)(rng);
// Use it inside solve() or any function where you need random sampling --> Example: int idx = uniform_int_distribution<int>(l, r)(rng);
//void solve() { int l = 10, r = 20;int random_index = uniform_int_distribution<int>(l, r)(rng);cout << "Random index = " << random_index << "\n";}

ll mod_add(ll a, ll b, ll m = MOD) { a = a % m; b = b % m; return (((a + b) % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m = MOD) { a = a % m; b = b % m; return (((a * b) % m) + m) % m; }
ll mul(ll a,ll b) {return a*b;}
ll power(ll base, ll exp) { ll res = 1; base %= MOD; while (exp > 0) { if (exp % 2 == 1) res = mod_mul(res, base); base = mod_mul(base, base); exp /= 2; } return res; }
ll power_no_mod(ll base,ll exp) { ll res = 1;  while (exp > 0) { if (exp % 2 == 1) res = mul(res, base); base = mul(base, base); exp /= 2; } return res; }
ll modInverse(ll n) { return power(n, MOD - 2); }
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll compute_mex(const vl& a) { set<ll> s(all(a)); ll mex = 0; while (s.count(mex)) mex++; return mex; }
vl prefixMEX(vl & a) {ll n = a.size();vl seen(n+1, 0), pre_mex(n,0);ll mex = 0;for(int i=0;i<n;i++){if(a[i] <= n) seen[a[i]] = 1;while(mex<=n && seen[mex]) mex++;pre_mex[i] = mex;}return pre_mex;}

void solve() {
  
}
int main() {
    fast;
    int t = 1;
    cin >> t; // Comment this line for single test case problems
    while (t--) {
        solve();
    }
    return 0;
}
