//add here // can directly copy paste inside public in LC
    typedef long long ll;
    static const int MOD = 1e9 + 7;
    const int N_FACT = 1e6;
    vector<ll> fact, invFact;
    //Non-static members: Belong to an object instance. Cannot be used as default arguments.
    //Static members: Belong to the class itself. Can be used as default arguments.
    ll mod_pow(ll a, ll b, ll m = MOD) {
        ll res = 1;
        while (b > 0) {
            if (b & 1) res = (res * a) % m;
            a = (a * a) % m;
            b >>= 1;
        }
        return res;
    }
    ll mod_mul(ll a, ll b, ll m = MOD) {
        a %= m;
        b %= m;
        return (((a * b) % m) + m) % m;
    }
    ll modInverse(ll n) { return mod_pow(n, MOD - 2); }
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
    ll nCr_mod_p(int n, int r) {
        if (r < 0 || r > n) return 0;
        return mod_mul(fact[n], mod_mul(invFact[r], invFact[n - r]));
    }
