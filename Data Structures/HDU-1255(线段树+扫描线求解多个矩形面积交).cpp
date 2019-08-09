#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val ) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 2e3+10;
int n;
double a[maxn*4];
struct node{
    double l, r, h;     ///左右区间
    int flag;           ///上边1，下边-1
}L[maxn*4];
bool cmp(const node &A, const node &B){
    return A.h < B.h;
}

struct Seg{
    int l, r, cnt;
    double sum1, sum2;
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define cnt(p) tree[p].cnt
    #define sum1(p) tree[p].sum1
    #define sum2(p) tree[p].sum2
}tree[maxn<<2];

void push_up(int p){
    if(cnt(p) > 0) sum1(p) = a[r(p) + 1] - a[l(p)];
    else {
        if(l(p) == r(p)) sum1(p) = 0.0;
        else sum1(p) = sum1(p<<1) + sum1(p<<1|1);
    }

    if(cnt(p) >= 2) sum2(p) = a[r(p) + 1] - a[l(p)];
    else {
        if(l(p) == r(p)) sum2(p) = 0;
        else if(cnt(p) == 1) sum2(p) = sum1(p<<1) + sum1(p<<1|1);
        else if(cnt(p) == 0) sum2(p) = sum2(p<<1) + sum2(p<<1|1);
    }
}

void build(int l, int r, int p){
    l(p) = l; r(p) = r; sum1(p) = sum2(p) = 0.0; cnt(p) = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, p<<1);
    build(mid+1, r, p<<1|1);
}
void change(int l, int r, int p, int d){
    if(l <= l(p) && r >= r(p)){
        cnt(p) += d;
        push_up(p); return;
    }
    int mid = (l(p) + r(p)) >> 1;
    if(mid >= l) change(l, r, p<<1, d);
    if(mid < r) change(l, r, p<<1|1, d);
    push_up(p);
}

int main()
{
    int T; scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        int num = 0;
        double ans = 0.0;
        for(int i = 1; i <= n; i ++){
            double x1, x2, y1, y2; scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            L[++ num].l = x1; L[num].r = x2; L[num].h = y1; L[num].flag = 1;
            a[num] = x1;
            L[++ num].l = x1; L[num].r = x2; L[num].h = y2; L[num].flag = -1;
            a[num] = x2;
        }
        sort(a + 1, a + num + 1);
        int pos = unique(a + 1, a + num + 1) - a;
        sort(L + 1, L + num + 1, cmp);
        build(0, pos, 1);
        for(int i = 1; i <= num - 1; i ++){
            int l = lower_bound(a+1, a+pos, L[i].l) - a;
            int r = lower_bound(a+1, a+pos, L[i].r) - a-1;
            change(l, r, 1, L[i].flag);
            ans += (L[i+1].h - L[i].h) * sum2(1);
        }
        printf("%.2f\n", ans);
    }
    return 0;
}
/**
102
5
1 1 4 2
1 3 3 7
2 1.5 5 4.5
3.5 1.25 7.5 4
6 3 10 7

3
0 0 1 1
1 0 2 1
2 0 3 1


**/

