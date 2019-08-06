#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 5e4+100;
int prime[maxn], v[maxn], mu[maxn];

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
    for(int i = 1; i <= 100; i ++){
        printf("%d %d %d\n", i, prime[i], mu[i]);
    }
}

int main()
{
    sieze(maxn-10);

    return 0;
}
/**
200
4 5 2
6 4 3

**/
