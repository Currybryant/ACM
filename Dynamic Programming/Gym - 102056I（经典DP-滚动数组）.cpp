#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 102;
ll dp[2][maxn][maxn*maxn];
int n;
ll a[maxn], b[maxn], c[maxn];
int main()
{
    int T;  scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
        }
        mes(dp[0], -1);
        int id = 1;
        dp[0][0][0] = 0;
        ll ans = 0;
        for(int i = n; i >= 1; i --, id ^= 1){
            mes(dp[id], -1);
            for(int j = 0; j <= n - i; j ++){
                for(int k = 0; k <= n * n ; k ++){
                    if(dp[id^1][j][k] != -1){
                        dp[id][j+1][k+i] = max(dp[id][j+1][k+i], dp[id^1][j][k]+a[i]);
                        ans = max(ans, dp[id][j+1][k+i]);
                        dp[id][j][k] = max(dp[id][j][k], dp[id^1][j][k] + (k-i*j)*b[i]);
                        dp[id][j][k] = max(dp[id][j][k], dp[id^1][j][k] + j*c[i]);
                        ans = max(ans, dp[id][j][k]);
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
/**

3
2
3 1 2
3 1 2
3
3 1 2
3 1 2
3 1 2
5
3 1 2
3 1 2
3 1 2
3 1 2
3 1 2

**/

/**
Answer
6
10
24

**/

