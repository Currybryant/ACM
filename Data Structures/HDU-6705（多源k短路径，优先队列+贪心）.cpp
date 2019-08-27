#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b,a) memcpy(b,a, sizeof a)
/**
    优先队列贪心

    对于当前边(u, v, w)考虑两种扩展情况：
    一、 扩展以 u 为起点的下一条边权值较小的边
    二、 扩展以 v 为起点的第一条边权值最小的边

**/
const int maxn = 1e5+100;
int n, m, q, mx, tot;
int a[maxn];
ll ans[maxn];
struct Edge{
    int to;
    ll w;
    bool operator < (const Edge& A){
        return w < A.w;
    }
};
vector<Edge>G[maxn];
struct Node{
    int from, to, pos;
    ll w;
    Node(int from = 0, int to = 0, int pos = 0, ll w = 0):from(from), to(to), pos(pos),w(w){}
    friend bool operator < (const Node& A, const Node& B){
        return A.w > B.w;
    }
};
priority_queue<Node>que;

void solve(){
    while(que.size()){
        Node P = que.top(); que.pop();
        int u = P.from, v = P.to, pos = P.pos;
        ll w = P.w;
        ans[++ tot] = w;
        if(tot >= mx) return;
        if(pos + 1 < G[u].size()){
            que.push(Node{u, G[u][pos+1].to, pos+1, w + G[u][pos+1].w - G[u][pos].w });
        }
        if(G[v].size()){
            que.push(Node{v, G[v][0].to, 0, w + G[v][0].w });
        }
    }
}
int main()
{
    int T; scanf("%d", &T);
    while(T --){
        scanf("%d %d %d", &n, &m, &q);
        for(int i = 0; i <= n + 5; i ++){
            G[i].clear();
        }
        while(que.size())que.pop();


        for(int i = 1; i <= m; i ++){
            int x, y; ll z; scanf("%d %d %lld", &x, &y, &z);
            G[x].push_back(Edge{y, z});
        }
        for(int i = 1; i <= n; i ++){
            sort(G[i].begin(), G[i].end());
            if(G[i].size()){
                que.push(Node{i, G[i][0].to, 0, G[i][0].w});

            }
        }
        mx = tot = 0;
        for(int i = 1; i <= q; i ++){
            scanf("%d", &a[i]);
            mx = max(mx, a[i]);
        }
        solve();
        for(int i = 1; i <= q; i ++){
            printf("%lld\n", ans[a[i]]);
        }
    }
    return 0;
}
/**
100
2 2 7
1 2 1
2 1 2
1
2
3
4
5
6
7
**/

