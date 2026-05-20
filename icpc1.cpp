#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int64 s, m;
        cin >> s >> m;
        // lowbit of m
        int64 g = m & -m;
        if (s % g != 0) {
            cout << -1 << '\n';
            continue;
        }
        int64 s1 = s / g;
        int64 m1 = m / g; // m1 is odd now
        
        // precompute sumBits[i] = sum of 2^j for j<=i where bit j in m1 is 1
        const int MAXB = 62; // enough for 1e18
        vector<unsigned long long> sumBits(MAXB, 0ULL);
        unsigned long long prefix = 0ULL;
        for (int i = 0; i < MAXB; ++i) {
            if ( (m1 >> i) & 1LL ) {
                // add 2^i
                prefix += (1ULL << i);
            }
            sumBits[i] = prefix;
        }
        
        // lower bound for n: ceil(s1 / m1)
        int64 L = (s1 + m1 - 1) / m1;
        if (L < 1) L = 1;
        int64 R = s1; // upper bound
        
        auto feasible = [&](int64 n)->bool {
            // check for each bit position i: n * sumBits[i] >= s1 mod 2^{i+1}
            unsigned long long mask = 0;
            for (int i = 0; i < MAXB; ++i) {
                // compute need = s1 % (1ULL << (i+1))
                unsigned long long mod = ( (i+1) >= 63 ) ? (unsigned long long) s1 : (1ULL << (i+1));
                unsigned long long need;
                if ((i+1) >= 63) {
                    need = (unsigned long long) s1; // s1 fits in 64-bit
                } else {
                    need = (unsigned long long) (s1 & (mod - 1ULL));
                }
                // compute capacity = n * sumBits[i]
                i128 cap = (i128) n * (i128) sumBits[i];
                if (cap < (i128) need) return false;
            }
            return true;
        };
        
        // Binary search minimal n
        int64 ans = -1;
        while (L <= R) {
            int64 mid = L + (R - L) / 2;
            if (feasible(mid)) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        if (ans == -1) cout << -1 << '\n';
        else cout << ans << '\n';
    }
    return 0;
}