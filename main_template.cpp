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
//set<int> posns; multiset<int> lengths;
// auto it = posns.lower_bound(light); // first >= light int right = *it; it--; int left = *it; --> can do like this
//lengths.erase(lengths.find(right - left));---> remove one occurence, without .find removes all occurences
//*lengths.rbegin() --> accessing last element of any set/multiset/oset
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
