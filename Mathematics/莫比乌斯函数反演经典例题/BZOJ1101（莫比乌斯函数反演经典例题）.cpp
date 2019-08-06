#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 5e4+100;
int prime[maxn], v[maxn], mu[maxn], pre[maxn];

void sieze(int n){
    int m = 0; mes(v, 0); mu[1] = 1;
    for(int i = 2; i <= n; i ++){
        if(!v[i]){
            prime[++m] = i; mu[i] = -1; v[i] = i;
        }
        for(int j = 1; j <= m; j ++){
            if(prime[j] > v[i] || i * prime[j] > n)break;
            v[i*prime[j]] = prime[j];
            if(i % prime[j]) mu[i*prime[j]] = -mu[i];
            else mu[i*prime[j]] = 0;
        }
    }
    pre[0] = 0;
    for(int i = 1; i <= n; i ++){
//        printf("%d %d %d\n", i, prime[i], mu[i]);
        pre[i] = pre[i-1] + mu[i];
    }
}

ll solve(int n, int m){
    ll ans = 0;
    for(int l = 1, r; l <= min(n, m); l = r + 1){
        r = min(n/(n/l), m/(m/l));
        ans += 1ll*(pre[r]-pre[l-1])*(n/l)*(m/l);
    }
    return ans;
}


int main()
{
    sieze(maxn-10);
    int T; scanf("%d", &T);
    while(T --){
        int a, b, c; scanf("%d %d %d", &a, &b, &c);
        ll ans = solve(a/c, b/c);
        printf("%lld\n", ans);
    }
    return 0;
}
/**
200
4 5 2
6 4 3

**/
