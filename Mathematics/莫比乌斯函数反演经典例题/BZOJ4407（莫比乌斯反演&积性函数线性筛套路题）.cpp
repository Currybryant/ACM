#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const ll mod = 1e9+7;
const int maxn = 5e6+100;
int prime[maxn], v[maxn], low[maxn], F[maxn], f[maxn];
int m;
int K;
ll ksm(ll a, int n, ll p){
    ll res = 1;
    while(n){
        if(n & 1) res = res * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return res;
}
void sieze(int n){
    m = 0; mes(v, 0); F[1] = 1, f[1] = 1;
    for(int i = 2; i <= n; i ++){
        if(!v[i]){
            prime[++m] = i; v[i] = i;  f[i] = ksm(i, K, mod); F[i] = (f[i]-1+mod)%mod;  low[i] = i;
        }
        for(int j = 1; j <= m && 1ll*i * prime[j] <= 1ll*n; j ++){
            v[i*prime[j]] = 1;
            f[i * prime[j]] = 1ll*f[i] * f[prime[j]] % mod;
            if(i % prime[j] == 0){
                if(low[i] == i) F[i * prime[j]] = 1ll*F[i] * f[prime[j]] % mod;
                else F[i * prime[j]] = 1ll*F[i / low[i]] * F[low[i] * prime[j]] % mod;
                low[i * prime[j]] = low[i] * prime[j];
                break;
            }
            F[i * prime[j]] = 1ll*F[i] * F[prime[j]] % mod;
            low[i * prime[j]] = prime[j];
        }
    }
    for(int i = 2; i <= n; i ++){
        F[i] = 1ll*(F[i]+F[i-1])%mod;
    }
}

ll solve(int n, int m){
    int mi = min(n, m);
    ll ans = 0;
    for(int l = 1, r = 0; l <= mi; l = r + 1){
        r = min(n/(n/l), m/(m/l));
        ll tmp = 1ll*(F[r]-F[l-1]+mod)%mod*(n/l)%mod*(m/l);
        ans = (ans + tmp) % mod;
    }
    ans = ((ans%mod)+mod)%mod;
    return ans;
}


int main()
{
    int T; scanf("%d %d", &T, &K);
    sieze(maxn-10);
    while(T --){
        int n, m; scanf("%d %d", &n, &m);
        ll ans = solve(n, m);
        printf("%lld\n", ans);
    }
    return 0;
}
