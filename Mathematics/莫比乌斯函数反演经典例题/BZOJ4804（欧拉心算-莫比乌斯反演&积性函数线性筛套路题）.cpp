
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)


const int maxn = 1e7+100;
int prime[maxn], phi[maxn], v[maxn], low[maxn];
ll f[maxn];
int m;

void sieze(int n){
    m = 0; mes(v, 0); phi[1] = f[1] = 1;
    for(int i = 2; i <= n; i ++){
        if(!v[i]){
            prime[++m] = i; v[i] = i; phi[i] = i - 1; f[i] = phi[i] - 1; low[i] = i;
        }
        for(int j = 1; j <= m && i * prime[j] <= n; j ++){
            v[i*prime[j]] = 1;

            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                if(low[i] == i){
                    f[i * prime[j]] = phi[i * prime[j]]- phi[i];
                }
                else {
                    f[i * prime[j]] = f[i / low[i]] * f[low[i] * prime[j]];
                }
                low[i * prime[j]] = low[i] * prime[j];
                break;
            }

            phi[i * prime[j]] = phi[i] * (prime[j]-1);
            f[i * prime[j]] = f[i] * f[prime[j]];
            low[i * prime[j]] = prime[j];


        }
    }
    for(int i = 2; i <= n; i ++){
        f[i] = (f[i]+f[i-1]);
    }
}

ll solve(int n, int m){
    int mi = min(n, m);
    ll ans = 0;
    for(int l = 1, r = 0; l <= mi; l = r + 1){
        r = min(n/(n/l), m/(m/l));
        ans += 1ll*(n/l)*(m/l)*(f[r]-f[l-1]);
    }
    return ans;
}

int main()
{
    sieze(maxn-10);
    int T; scanf("%d", &T);
    while(T --){
        int n; scanf("%d", &n);
        ll ans = solve(n, n);
        printf("%lld\n", ans);
    }
    return 0;
}
