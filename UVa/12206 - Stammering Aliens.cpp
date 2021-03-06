/*
Suffix array implementation using bucket sorting + lcp.
Complexity O(n log n), str[] is the target string,
n is its length and suffix[i] contains i'th sorted suffix position.
*/

#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 16;
const int MAXL = 16;

int n, stp, mv, suffix[MAXN], tmp[MAXN];
int sum[MAXN], cnt[MAXN], ranky[MAXL][MAXN];
char str[MAXN];

inline bool equaly(const int &u, const int &v){
    if(!stp) return str[u] == str[v];
    if(ranky[stp-1][u] != ranky[stp-1][v]) return false;
    int a = u + mv < n ? ranky[stp-1][u+mv] : -1;
    int b = v + mv < n ? ranky[stp-1][v+mv] : -1;
    return a == b;
}

void update(){
    int i, rnk;
    for(i = 0; i < n; i++) sum[i] = 0;
    for(i = rnk = 0; i < n; i++) {
        suffix[i] = tmp[i];
        if(i && !equaly(suffix[i], suffix[i-1])) {
            ranky[stp][suffix[i]] = ++rnk;
            sum[rnk+1] = sum[rnk];
        }
        else ranky[stp][suffix[i]] = rnk;
        sum[rnk+1]++;
    }
}

void Sort() {
    int i;
    for(i = 0; i < n; i++) cnt[i] = 0;
    memset(tmp, -1, sizeof tmp);
    for(i = 0; i < mv; i++){
        int idx = ranky[stp - 1][n - i - 1];
        int x = sum[idx];
        tmp[x + cnt[idx]] = n - i - 1;
        cnt[idx]++;
    }
    for(i = 0; i < n; i++){
        int idx = suffix[i] - mv;
        if(idx < 0)continue;
        idx = ranky[stp-1][idx];
        int x = sum[idx];
        tmp[x + cnt[idx]] = suffix[i] - mv;
        cnt[idx]++;
    }
    update();
    return;
}

inline bool cmp(const int &a, const int &b){
    if(str[a]!=str[b]) return str[a]<str[b];
    return false;
}

void SortSuffix() {
    int i;
    for(i = 0; i < n; i++) tmp[i] = i;
    sort(tmp, tmp + n, cmp);
    stp = 0;
    update();
    ++stp;
    for(mv = 1; mv < n; mv <<= 1) {
        Sort();
        stp++;
    }
    stp--;
    for(i = 0; i <= stp; i++) ranky[i][n] = -1;
}

inline int lcp(int u, int v) {
    if(u == v) return n - u;
    int ret, i;
    for(ret = 0, i = stp; i >= 0; i--) {
        if(ranky[i][u] == ranky[i][v]) {
            ret += 1<<i;
            u += 1<<i;
            v += 1<<i;
        }
    }
    return ret;
}

int main() {
//    freopen("12206o.txt", "w", stdout);
    int T;
    int m;
//    scanf("%d", &T);
    while(scanf("%d", &m) && m) {
        scanf("%s", str);
        n = strlen(str);
        int p,q;
//        scanf("%d %d", &p,&q);
        SortSuffix();

//        for(int i=0; i<n; i++) cout << suffix[i] << ' '; cout << endl;

        int ans = 0, sub;
        for(int i=0; i<=n-m; i++) {
//            cout << suffix[i] << ' ' << suffix[i-1] << ' ' << lcp(suffix[i], suffix[i-1]) << ' ' << endl;
            int x = 0;
            x = lcp(suffix[i], suffix[i+m-1]);
//            cout << i << ' ' << i+m-1 << ' ' << x << endl;
            if(x > ans) {
                ans = x;
                sub = 0;
                for(int j=i; j<i+m; j++) sub = max(sub, suffix[j]);
//                sub = max(suffix[i], suffix[i+m-1]);
            }
            else if(x == ans) {
                for(int j=i; j<i+m; j++) sub = max(sub, suffix[j]);
            }
        }
        if(!ans) printf("none\n");
        else printf("%d %d\n", ans, sub );
    }
    return 0;
}
