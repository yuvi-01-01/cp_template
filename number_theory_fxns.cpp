// ---------------------------- NUMBER THEORY ALGORITHMS -------------------------------- //

// --- Sieve-based Precomputation ---
vector<int> spf;
vector<int> primes;
void sieve() {
    spf.assign(N_SIEVE, 0);
    for (int i = 2; i < N_SIEVE; i++) {
        if (spf[i] == 0) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            if (p > spf[i] || (ll)i * p >= N_SIEVE) break;
            spf[i * p] = p;
        }
    }
}
map<int, int> getPrimeFactorization(int n) {
    map<int, int> factors;
    while (n > 1) { factors[spf[n]]++; n /= spf[n]; }
    return factors;
}
// Requires sieve() precomputation.
// map<int, int> factors = getPrimeFactorization(100);

vector<vi> getDistinctPrimeFactorsUptoN(int n) {
    vector<vi> distinct_factors(n + 1);
    for (int i = 2; i <= n; i++) {
        int temp = i;
        while (temp > 1) {
            int p = spf[temp];
            distinct_factors[i].pb(p);
            while (temp > 1 && temp % p == 0) {
                temp /= p;
            }
        }
    }
    return distinct_factors;
}

// Requires sieve() precomputation.
// vector<vi> all_factors = getDistinctPrimeFactorsUptoN(10);
// for(int p : all_factors[10]) cout << p << " "; // Prints 2 5

vector<int> phi;
void precompute_phi() {
    phi.assign(N_MAX, 0); for(int i = 0; i < N_MAX; i++) phi[i] = i;
    for (int i = 2; i < N_MAX; i++) { if (phi[i] == i) { for (int j = i; j < N_MAX; j += i) phi[j] -= phi[j] / i; } }
}

vector<int> nod; // Number of divisors
void precompute_nod() {
    nod.assign(N_MAX, 0);
    for (int i = 1; i < N_MAX; i++) { for (int j = i; j < N_MAX; j += i) nod[j]++; }
}
vector<ll> sod; // Sum of divisors
void precompute_sod() {
    sod.assign(N_MAX, 0);
    for (int i = 1; i < N_MAX; i++) { for (int j = i; j < N_MAX; j += i) sod[j] += i; }
}
// How to use Number Theory Precomputation:
// Call the required function(s) once in main() before the test cases loop.
// e.g., sieve(); precompute_phi();
// Then access values directly: ll result = phi[n];

// --- On-the-fly Calculation for a single number ---
ll getNumberOfDivisors(ll n) {
    ll count = 1;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ll e = 0;
            while (n % i == 0) { n /= i; e++; }
            count *= (e + 1);
        }
    }
    if (n > 1) count *= 2;
    return count;
}
ll gp_sum(ll a, ll r, ll n) { if (n == 0) return 0; ll num = power(r, n) - 1; if(num < 0) num += MOD; ll den = modInverse(r - 1); return mod_mul(a, mod_mul(num, den)); }
ll getSumOfDivisors(ll n) {
    ll total_sum = 1;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ll e = 0;
            while (n % i == 0) { n /= i; e++; }
            total_sum = mod_mul(total_sum, gp_sum(1, i, e + 1));
        }
    }
    if (n > 1) total_sum = mod_mul(total_sum, gp_sum(1, n, 2));
    return total_sum;
}


vector<ll> fact;
vector<ll> invFact;
void precompute_factorials() {
    fact.resize(N_FACT); invFact.resize(N_FACT);
    fact[0] = 1; invFact[0] = 1;
    for (int i = 1; i < N_FACT; i++) {
        fact[i] = mod_mul(fact[i - 1], i);
        invFact[i] = modInverse(fact[i]);
    }
}

// Call precompute_factorials() once in main() for problems involving nCr.

ll nCr_mod_p(int n, int r) {
    if (r < 0 || r > n) return 0;
    return mod_mul(fact[n], mod_mul(invFact[r], invFact[n - r]));
}
// Counts the number of integer solutions to:
// x1 + x2 + ... + xd = s
// where 0 <= xi <= b
// Uses Inclusion-Exclusion principle:
// Unbounded solutions = C(s + d - 1, d - 1)
// Subtract cases where any xi > b by shifting xi' = xi - (b+1) and counting again.
//
// Requires: precompute_factorials() for nCr_mod_p
ll countBoundedSolutions(int d, int s, int b) {
    ll ans = 0;
    for (int k = 0; k <= d; k++) {
        int sum_after_shift = s - k * (b + 1);
        if (sum_after_shift < 0) break;
        ll ways = nCr_mod_p(d, k) * nCr_mod_p(sum_after_shift + d - 1, d - 1) % MOD;
        if (k % 2 == 0) ans = (ans + ways) % MOD; // add when even
        else ans = (ans - ways + MOD) % MOD;     // subtract when odd
    }
    return ans;
}
// Requires precompute_factorials().
// ll combinations = nCr_mod_p(10, 3);


// Calculates the n-th Catalan number modulo p
// Interpretation: Number of valid sequences of n '+1's and n '-1's where no prefix sum is negative.
// (i.e., no initial part of the sequence has more -1s than +1s)
// Other uses: Number of full binary trees with n+1 leaves, Dyck paths, etc.
/*
The Goal: We need to calculate C(n) = (2n C n) / (n + 1) under modulo MOD.
The Problem: We cannot do direct division in modular arithmetic.
The Solution: We replace "division by (n+1)" with "multiplication by the modular inverse of (n+1)".
*/
ll catalan(int n) {  
    // Formula: C(n) = (1/(n+1)) * (2n C n)
    ll C_2n_n = nCr_mod_p(2 * n, n);
    ll inv_n_plus_1 = modInverse(n + 1);
    return mod_mul(C_2n_n, inv_n_plus_1);
}
// How to use catalan:
// Requires precompute_factorials() to be called in main().
// int n = 5;
// ll c5 = catalan(n); // Calculates the 5th Catalan number (42)
vector<ll> catalan_dp;
// Calculates Catalan numbers from 0 to N_MAX-1 using the recurrence C(n) = Σ C(i)*C(n-1-i)
void precompute_catalan() {
    catalan_dp.assign(N_MAX, 0);
    catalan_dp[0] = 1;
    for (int i = 1; i < N_MAX; i++) {
        for (int j = 0; j < i; j++) {
            catalan_dp[i] = mod_add(catalan_dp[i], mod_mul(catalan_dp[j], catalan_dp[i - 1 - j]));
        }
    }
}
// How to use precompute_catalan:
// Call precompute_catalan() once in main().
// Then access values directly: ll c5 = catalan_dp[5];
