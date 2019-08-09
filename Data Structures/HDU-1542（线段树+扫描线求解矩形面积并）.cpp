#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define inf 0x3f3f3f3f
#define mes(a, val ) memset(a, val, sizeof a)
#define mec(b, a) memcpy(b, a, sizeof a)

const int maxn = 120+10;
int n;
double a[maxn*4];
struct node{
    double l, r, h;   ///左右区间
    int flag;       ///上边1，下边-1
}L[maxn*4];
bool cmp(const node &A, const node &B){
    return A.h < B.h;
}
struct SegmentTree{
    int l, r, s;    ///左右区间、区间是否完整
    double len; ///有效长度
    #define l(p) tree[p].l
    #define r(p) tree[p].r
    #define s(p) tree[p].s
    #define len(p) tree[p].len
}tree[maxn*4];
void push(int p){
    if(s(p)){
        len(p) = a[r(p) + 1] - a[l(p)];
    }
    else if(l(p) == r(p)){
        len(p) = 0;
    }
    else {
        len(p) = len(p<<1) + len(p<<1|1);
    }
}
void build(int l, int r, int p){
    l(p) = l; r(p) = r; s(p) = 0; len(p) = 0.0;
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p<<1);
    build(mid+1, r, p<<1|1);
}
void change(int l, int r, int p, int d){
    if(l <= l(p) && r >= r(p)){
        s(p) += d;
        push(p);
        return;
    }
    int mid = (l(p) + r(p)) >> 1;
    if(mid >= l) change(l, r, p<<1, d);
    if(mid < r) change(l, r, p<<1|1, d);
    push(p);
}
int main(){
    int Case = 0;
    while(scanf("%d", &n) && n){
        int num = 0;
        for(int i = 1; i <= n;  i++){
            double x1, x2, y1, y2;
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            L[++num].l = x1; L[num].r = x2; L[num].h = y1; L[num].flag = 1; a[num] = x1;
            L[++num].l = x1; L[num].r = x2; L[num].h = y2; L[num].flag = -1; a[num] = x2;
        }
        sort(L + 1, L + num + 1, cmp);
        sort(a + 1, a + num + 1);
        double ans = 0.0;
        int pos = unique(a + 1, a + num + 1) - a;
        build(0, pos, 1);
        for(int i = 1; i < num; i ++){
            int l = lower_bound(a+1, a+pos, L[i].l)-a;
            int r = lower_bound(a+1, a+pos, L[i].r)-a-1;
            change(l, r, 1, L[i].flag);
            ans += (L[i+1].h - L[i].h)*len(1);
        }
        printf("Test case #%d\n", ++ Case);
		printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}

