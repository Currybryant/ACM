#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b,a) memcpy(b,a, sizeof a)
/**
    节点1~n表示勇士
    节点n+1~n+2*m表示怪物
    构造一个超级源点s = 0,连接所有勇士
    构造一个超级汇点t = n + 2*m + 1，连接所有怪物

    构造另一个小的源点，连接所有勇士，将超级源点连向此源点，赋上权值k
    跑一个从源点到汇点的最大流

**/
const int maxn = 4e4+100;
int n, m, k, tot;
int ver[maxn], head[maxn], Next[maxn], edge[maxn];
int d[maxn];
int s, t, maxflow;
queue<int>q;

void init(){
    tot = 1; mes(head, 0);
    maxflow = 0;
}
void addedge(int x, int y, int z){
    ver[++tot] = y; edge[tot] = z; Next[tot] = head[x]; head[x] = tot;
}

bool bfs(){
    mes(d, 0);
    while(q.size())q.pop();
    q.push(s); d[s] = 1;
    while(q.size()){
        int x = q.front(); q.pop();
        for(int i = head[x]; i; i = Next[i]){
            int y = ver[i], z = edge[i];
            if(z && !d[y]){
                q.push(y);
                d[y] = d[x] + 1;
                if(y == t) return 1;
            }
        }
    }
    return 0;
}
int Dinic(int x, int flow){
    if(x == t) return flow;
    int rest = flow, k;
    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i], z = edge[i];
        if(edge[i] && d[y] == d[x] + 1){
            k = Dinic(y, min(rest, z));
            if(!k) d[y] = 0;
            edge[i] -= k;
            edge[i^1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);
    init();
    s = 0; t = n + 2 * m + 1;
    int tmps = t + 1;
    addedge(s, tmps, k); addedge(tmps, s, 0);
    for(int i = 1; i <= n; i ++){
        addedge(s, i, 1); addedge(i, s, 0);
        addedge(tmps, i, 1); addedge(i, tmps, 0);
    }

    for(int i = n + m + 1; i <= n + 2*m; i ++){
        addedge(i, t, 1); addedge(t, i, 0);
        addedge(i-m, i, 1); addedge(i, i-m, 0);
    }
    for(int i = 1; i <= n; i ++){
        int k; scanf("%d", &k);
        while(k --){
            int x; scanf("%d", &x);
            addedge(i, n+x, 1); addedge(n+x, i, 0);
        }
    }
    int flow = 0;
    while(bfs()){
        while(flow = Dinic(s, inf)) maxflow += flow;
    }
    printf("%d\n", maxflow);


    return 0;
}
/**

3 5 2
4 1 2 3 5
2 2 5
2 1 2


5 10 2
2 3 10
5 1 3 4 6 10
5 3 4 6 8 9
3 1 9 10
5 1 3 6 7 10

**/
