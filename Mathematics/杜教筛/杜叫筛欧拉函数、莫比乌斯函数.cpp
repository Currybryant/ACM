#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
using namespace std::tr1;

#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 5000000;
tr1::unordered_map<int, ll> sumphi;
tr1::unordered_map<int, ll> summu;
bool v[maxn+5];
int prime[maxn+5];
ll phi[maxn+5], mu[maxn+5];
ll n;
int m;
void sieze(int n){///线性筛莫比乌斯与欧拉函数
    m = 0; v[1] = true; mu[1] = 1; phi[1] = 1;
    mes(v, 0);
    for(int i = 2 ; i <= n; i ++){
        if(!v[i]){
            prime[++m] = i; mu[i] = -1; phi[i] = i - 1;
        }
        for(int j = 1; j <= m;  j ++){
            if(prime[j]*i > n)break;
            v[i*prime[j]] = true;
            if(i % prime[j] == 0){
                phi[i*prime[j]] = phi[i]*prime[j];
                mu[i*prime[j]] = 0;break;
            }
            else {
                phi[i*prime[j]] = phi[i]*(prime[j]-1);
                mu[i*prime[j]] = -mu[i];
            }
        }
    }
    mu[0] = phi[0] = 0;
    for(int i = 1; i <= n; i ++){
        mu[i] += mu[i-1]; phi[i] += phi[i-1];
    }
}
ll djsmu(int n){
    if(n <= maxn) return mu[n];
    if(summu[n]) return summu[n];
    ll ans = 0;
    for(int l = 2, r; r < 2147483647 && l <= n; l = r + 1){
        r = n/(n/l);
        ans += (r - l + 1) * djsmu(n/l);
    }
    summu[n] = (ll)1 - ans;
    return summu[n];
}
ll djsphi(int n){
    if(n <= maxn) return phi[n];
    if(sumphi[n]) return sumphi[n];
    ll ans = 0;
    for(int l = 2, r; r < 2147483647 && l <= n; l = r + 1){
        r = n/(n/l);
        ans += (r - l + 1) * djsphi(n/l);
    }
    sumphi[n] = (ull)(n+1ll)*n/2ll - ans;
    return sumphi[n];
}
int main()
{
    sieze(maxn);
    scanf("%lld", &n);
    printf("%lld\n", djsphi(n));
    return 0;
}

