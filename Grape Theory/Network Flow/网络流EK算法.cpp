#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b,a) memcpy(b,a, sizeof a)

const int maxn = 1e3+100;
int n, m, tot;
int ver[maxn], head[maxn], Next[maxn], edge[maxn];
int incf[maxn], pre[maxn];
int s, t, maxflow;
bool vis[maxn];
void addedge(int x, int y, int z){
    ver[++tot] = y; edge[tot] = z; Next[tot] = head[x]; head[x] = tot;
}
bool bfs(){
    mes(vis, 0);
    queue<int> q;
    q.push(s); vis[s] = 1;
    incf[s] = inf;
    while(q.size()){
        int x = q.front(); q.pop();
        for(int i = head[x]; i; i = Next[i]){
            if(edge[i]){
                int y = ver[i];
                if(vis[y]) continue;
                incf[y] = min(incf[x], edge[i]);
                pre[y] = i;
                q.push(y), vis[y] = 1;
                if(y == t) return 1;
            }
        }
    }
    return 0;
}

void EK(){
    int x = t;
    while(x != s){
        int i = pre[x];
        edge[i] -= incf[t];
        edge[i^1] += incf[t];
        x = ver[i^1];
    }
    maxflow += incf[t];
}


int main()
{
    while(scanf("%d %d", &m, &n) != EOF){
        mes(head, 0); s = 1, t = n;
        tot = 1; maxflow = 0;
        for(int i = 1; i <= m; i ++){
            int x, y, z; scanf("%d %d %d", &x, &y, &z);
            addedge(x, y, z); addedge(y, x, 0);
        }
        while(bfs()) EK();
        printf("%d\n", maxflow);
    }

    return 0;
}
