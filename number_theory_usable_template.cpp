// can directly copy-paste inside public: in LeetCode class
// includes modular arithmetic, nCr, Lucas Theorem, and CRT (Chinese Remainder Theorem)

typedef long long ll;
static const int MOD = 1e9 + 7;
const int N_FACT = 1e6;
vector<ll> fact, invFact;

// -------------------- BASIC MODULAR UTILITIES --------------------

// Fast modular exponentiation: computes (a^b) % m
ll mod_pow(ll a, ll b, ll m = MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// Modular multiplication (handles negatives safely)
ll mod_mul(ll a, ll b, ll m = MOD) {
    a %= m;
    b %= m;
    return (((a * b) % m) + m) % m;
}

// Modular inverse using Fermat’s Little Theorem (works only when m is prime)
ll modInverse(ll n) { return mod_pow(n, MOD - 2); }

// -------------------- FACTORIAL PRECOMPUTATION --------------------
//
// Precomputes factorials and inverse factorials up to N_FACT
// Must call once before using nCr_mod_p()

void precompute_factorials() {
    fact.resize(N_FACT);
    invFact.resize(N_FACT);
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < N_FACT; i++) {
        fact[i] = mod_mul(fact[i - 1], i);
        invFact[i] = modInverse(fact[i]);
    }
}

// -------------------- nCr MOD PRIME --------------------
//
// Computes nCr % MOD assuming MOD is prime
// Uses precomputed factorials

ll nCr_mod_p(int n, int r) {
    if (r < 0 || r > n) return 0;
    return mod_mul(fact[n], mod_mul(invFact[r], invFact[n - r]));
}

// -------------------- LUCAS THEOREM --------------------
//
// Used to compute nCr % p when n and r are very large (n > p)
// Works only if p is prime
// Breaks n and r into base-p digits and applies nCr on each level

ll lucas(ll n, ll r, ll p) {
    if (r == 0) return 1;
    ll ni = n % p;
    ll ri = r % p;
    return (lucas(n / p, r / p, p) * nCr_mod_p(ni, ri)) % p;
}

// -------------------- EXTENDED GCD --------------------
//
// Helper function for CRT to find modular inverses when moduli are not coprime
// Returns gcd(a,b) and coefficients x,y such that a*x + b*y = gcd(a,b)

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// -------------------- CHINESE REMAINDER THEOREM (CRT) --------------------
//
// Solves system of equations:
//   x ≡ a1 (mod m1)
//   x ≡ a2 (mod m2)
//   x ≡ a3 (mod m3) ...
//
// Works for both coprime and non-coprime moduli
//
// Returns {x, lcm}:
//   → x   = smallest non-negative integer that satisfies all given congruences
//   → lcm = combined modulus (LCM of all m[i])
//
// Meaning: all other solutions are of the form x + k * lcm
//
// Example:
//   x ≡ 2 (mod 3)
//   x ≡ 3 (mod 5)
//   Output: {8, 15}
//   → 8 is the smallest x satisfying both
//   → 15 = 3 * 5 is the combined modulus
//   → All valid x are of form 8 + 15*k

pair<ll, ll> CRT(vector<ll> a, vector<ll> m) {
    ll x = a[0];   // current solution
    ll lcm = m[0]; // current combined modulus

    for (int i = 1; i < (int)a.size(); i++) {
        ll a1 = x, m1 = lcm;
        ll a2 = a[i], m2 = m[i];
        ll x1, y1;
        ll g = ext_gcd(m1, m2, x1, y1);

        // if not consistent (no solution)
        if ((a2 - a1) % g != 0) return {-1, -1};

        ll mod = m1 / g * m2; // lcm
        ll diff = (a2 - a1) / g;
        ll mult = (x1 * diff) % (m2 / g);

        x = (a1 + mult * m1) % mod;
        if (x < 0) x += mod;
        lcm = mod;
    }

    return {x, lcm};
}

// -------------------- HOW TO USE --------------------
//
// 1️⃣ Precompute factorials (once):
//        precompute_factorials();
//
// 2️⃣ Compute nCr mod prime (simple):
//        nCr_mod_p(10, 3);  // -> 120 mod MOD
//
// 3️⃣ Lucas theorem (for large n > MOD):
//        lucas(1000, 900, 7); // -> nCr mod 7
//
// 4️⃣ Combine modular equations using CRT:
//        vector<ll> a = {2, 3};
//        vector<ll> m = {3, 5};
//        auto [x, mod] = CRT(a, m);
//        // Output: {8, 15} → x ≡ 8 (mod 15)
//
// Example usecase of Lucas + CRT:
// Suppose we want nCr mod (p1 * p2), where p1 and p2 are primes.
//    ll n=1000, r=900;
//    ll p1=3, p2=5;
//    ll val1 = lucas(n, r, p1);
//    ll val2 = lucas(n, r, p2);
//    auto [res, mod] = CRT({val1, val2}, {p1, p2});
//    // res is nCr mod 15 (since 3*5=15)

