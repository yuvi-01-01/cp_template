#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <sstream>

// For Advanced Data Structures (Policy-Based)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// Compiler Optimizations
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")

// Namespaces
using namespace std;
using namespace __gnu_pbds;

// ---------------------------------- MACROS & TYPEDEFS --------------------------------- //

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
typedef vector<string> vs;

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define fo(i, n) for (ll i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define f first
#define s second
#define oset tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

// -------------------------------------- CONSTANTS ------------------------------------- //

const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const ld PI = acos(-1.0);
const int N_MAX = 1e6 + 5; // General purpose max N for all precomputation
const int N_SIEVE = 1e6 + 5;
const int N_FACT = 1e6 + 5;

// --------------------------------- DEBUGGING TEMPLATE --------------------------------- //

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) { cerr << t; } void _print(int t) { cerr << t; } void _print(string t) { cerr << t; } void _print(char t) { cerr << t; } void _print(ld t) { cerr << t; } void _print(double t) { cerr << t; }
template <class T, class V> void _print(pair<T, V> p) { cerr << "{"; _print(p.f); cerr << ","; _print(p.s); cerr << "}"; }
template <class T> void _print(vector<T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T> void _print(set<T> v) { cerr << "[ "; for (T i : v) { _print(i); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print(map<T, V> v) { cerr << "[ "; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }

// --------------------------- BASIC UTILITY FUNCTIONS ---------------------------------- //

ll mod_add(ll a, ll b, ll m = MOD) { a = a % m; b = b % m; return (((a + b) % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m = MOD) { a = a % m; b = b % m; return (((a * b) % m) + m) % m; }
ll mul(ll a,ll b) {return a*b;}
ll power(ll base, ll exp) { ll res = 1; base %= MOD; while (exp > 0) { if (exp % 2 == 1) res = mod_mul(res, base); base = mod_mul(base, base); exp /= 2; } return res; }
ll power_no_mod(ll base,ll exp) { ll res = 1;  while (exp > 0) { if (exp % 2 == 1) res = mul(res, base); base = mul(base, base); exp /= 2; } return res; }
ll modInverse(ll n) { return power(n, MOD - 2); }
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll compute_mex(const vl& a) { set<ll> s(all(a)); ll mex = 0; while (s.count(mex)) mex++; return mex; }
// How to use compute_mex:
// vl my_numbers = {0, 1, 3, 4};
// ll mex_value = compute_mex(my_numbers); // mex_value will be 2
