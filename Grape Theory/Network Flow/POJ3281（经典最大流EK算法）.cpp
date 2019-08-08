//#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val) memset(a, val, sizeof a)
#define mec(b,a) memcpy(b,a, sizeof a)
/**
    Nͷţ��F��ʳ�D������
    �ڵ� 1~F ��ʾ ʳ��
    �ڵ�F+1~F+2*N��ʾţ ���ｫһͷţ��ֳ������ڵ㣬
    �ڵ�F+2*N+1��ʾ����

    ����һ��Դ�� s = 0, һ����� t = F+2*N+D+1
    ��һ����Դ��s�����t����������Ǵ�

**/
const int maxn = 5e3+100;

int F, D, N, n, tot;
int ver[maxn], head[maxn], Next[maxn], edge[maxn];
int incf[maxn], pre[maxn];
int s, t, maxflow;
bool vis[maxn];

void init(){
    tot = 1; maxflow = 0;
    mes(head, 0);
}
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
    while(scanf("%d %d %d", &N, &F, &D) != EOF){
        init();
        n = F + D + 2 * N + 1;
        s = 0, t = n;
/**  **************  ��ʼ������  ************************   **/
        ///Դ�㵽����ʳ�ｨ��
        for(int i = 1; i <= F; i ++){
            addedge(s, i, 1); addedge(i, s, 0);
        }
        ///�������ϵ���㽨��
        for(int i = F+2*N+1; i <= F+2*N+D; i ++){
            addedge(i, t, 1); addedge(t, i, 0);
        }
        ///ţ��ֳ������㲢����
        for(int i = 1; i <= N; i ++){
            int x = F+2*i-1, y = F+2*i;
            addedge(x, y, 1); addedge(y, x, 0);
        }
/**  **************  ��ʼ������  ************************   **/
        for(int i = 1; i <= N; i ++){
            int k1, k2; scanf("%d %d", &k1, &k2);
            while(k1 --){
                int x; scanf("%d", &x);
                addedge(x, F+2*i-1, 1); addedge(F+2*i-1, x, 0);
            }
            while(k2 --){
                int x; scanf("%d", &x);
                addedge(F+2*i, x+F+2*N, 1); addedge(x+F+2*N, F+2*i, 0);
            }
        }
        while(bfs()) EK();
        printf("%d\n", maxflow);
     }
    return 0;
}
/**
4 3 3
2 2 1 2 3 1
2 2 2 3 1 2
2 2 1 3 1 2
2 1 1 3 3

**/
