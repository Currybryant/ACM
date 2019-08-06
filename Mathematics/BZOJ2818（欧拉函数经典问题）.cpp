#include <bits/stdc++.h>
using namespace std;
#define mes(a, val) memset(a, val, sizeof(a))
#define mec(b, a) memcpy(b, a, sizeof(a))
#define ll long long
#define inf 0x3f3f3f3f

const int maxn = 1e7+100;
int phi[maxn], v[maxn], prime[maxn];
ll pre[maxn];
int m = 0;
void sieze(int n){
    m = 0; phi[1] = 0; mes(v, 0);
    for(int i = 2; i <= n; i ++){
        if(!v[i]){
            prime[++m] = i; phi[i] = i - 1; v[i] = i;
        }
        for(int j = 1; j <= m; j ++){
            if(prime[j] > v[i] || i*prime[j] > n) break;
            v[i*prime[j]] = prime[j];
            if(i % prime[j] == 0){
                phi[i*prime[j]] = phi[i]*prime[j]; break;
            }
            else phi[i*prime[j]] = phi[i]*(prime[j]-1);
        }
    }
    pre[0] = 0;
    for(int i = 1; i <= n; i ++){
//        printf("%d %d %d\n", i, prime[i], phi[i]);
        pre[i] = pre[i-1] + phi[i];
    }
}

int main(){
    sieze(maxn-10);
    int n; scanf("%d", &n);
    ll ans = 0;
    for(int i = 1; i <= m && prime[i] <= n; i ++){
        ans += (2*pre[n/prime[i]]+1);
    }
    printf("%lld\n", ans);
    return 0;
}
/**

**/

