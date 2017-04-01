/* Florin Chirica
   Somer
   University of Bucharest
*/
  
#include <bits/stdc++.h>
#define point pair <long double, long double>
#define x first
#define y second
  
using namespace std;
  
const int kNMAX = 51;
const int sign = 1;
const int INF = 1e7 + 7;
const long double eps = 0.000000001;
  
vector <pair <int, int > > G[kNMAX];
int dep[kNMAX];
bool vis[kNMAX];
int father[kNMAX];
int cost_to_father[kNMAX];
  
struct restriction {
    int A;
    int B;
    int C;
    int sign;
} R[2 * kNMAX * kNMAX];
  
int LCA(int nod1, int nod2) {
    int lev1 = dep[nod1];
    int lev2 = dep[nod2];
    if (lev1 < lev2) {
        swap(lev1, lev2);
        swap(nod1, nod2);
    }
    while (dep[nod1] != lev2) {
        nod1 = father[nod1];
    }
    while (nod1 != nod2) {
        nod1 = father[nod1];
        nod2 = father[nod2];
    }
    return nod1;
}
  
int get_dist(int x, int y) {
    int cost = 0;
    while (x != y) {
        cost += cost_to_father[x];
        x = father[x];
    }
    return cost;
}
  
void dfs_levels(int nod) {
    vector <pair <int, int> > :: iterator it;
    vis[nod] = 1;
    for (it = G[nod].begin(); it != G[nod].end(); ++it)
        if (!vis[it -> first]) {
            dep[it -> first] = dep[nod] + 1;
            father[it -> first] = nod;
            cost_to_father[it -> first] = it -> second;
            dfs_levels(it -> first);
        }
}
  
point previous[4 * kNMAX * kNMAX], current[2 * kNMAX * kNMAX];
int nn;
point x[2 * kNMAX * kNMAX];
  
long double det(long double A, long double B, long double C, long double D) {
    return A * D - B * C;
}
  
point intersect(restriction A, point C, point D) {
    long double A1 = A.A; long double B1 = A.B; long double C1 = -A.C;
    long double A2 = C.y - D.y; long double B2 = D.x - C.x; long double C2 = -C.x * D.y + C.y * D.x;
    long double xint, yint;
    xint = det(C1, B1, C2, B2) / det(A1, B1, A2, B2);
    yint = det(A1, C1, A2, C2) / det(A1, B1, A2, B2);
    pair <long double, long double> puirla = make_pair(1.0 * xint, 1.0 * yint);
    return puirla;
}
  
int evaluate(restriction A, point B) {
    long double foo = (long double)A.A * B.x + (long double)A.B * B.y + (long double)A.C;
    if (fabs(foo) <= eps)
        return 0;
    if (foo > eps)
        return 1;
    return -1;
}
  
int previousCnt = 4;
  
void precalc(int cnt) {
    previous[1] = make_pair(-INF, -INF);
    previous[2] = make_pair(INF, -INF);
    previous[3] = make_pair(INF, INF);
    previous[4] = make_pair(-INF, INF);
    previous[5] = previous[1];
  
    int i, j;
    for (i = 1; i <= cnt; ++i) {
        int currentCnt = 0;
        if (previousCnt == 1) {
            if (evaluate(R[i], previous[1]) < 0)
                previousCnt = 0;
            else
                continue;
        }
        for (j = 1; j <= previousCnt; ++j) {
            int m_sign = evaluate(R[i], previous[j]);
            if (m_sign >= 0) {
                current[++currentCnt] = previous[j];
                if (m_sign > 0) {
                    int next_sign = evaluate(R[i], previous[j + 1]);
                    if (next_sign < 0) {
                        current[++currentCnt] = intersect(R[i], previous[j], previous[j + 1]);
                        if (currentCnt >= 2 && fabs(current[currentCnt].x - current[currentCnt - 1].x) <= eps && fabs(current[currentCnt].y - current[currentCnt - 1].y) <= eps)
                            --currentCnt;
                    }
                }
            }
            if (m_sign < 0) {
                int next_sign = evaluate(R[i], previous[j + 1]);
                if (next_sign > 0) {
                    current[++currentCnt] = intersect(R[i], previous[j], previous[j + 1]);
                    if (currentCnt >= 2 && fabs(current[currentCnt].x - current[currentCnt - 1].x) <= eps && fabs(current[currentCnt].y - current[currentCnt - 1].y) <= eps)
                            --currentCnt;
                }
            }
        }
        previousCnt = currentCnt;
        for (j = 1; j <= previousCnt; ++j)
            previous[j] = current[j];
        if (previousCnt > 1 && fabs(previous[1].x - previous[previousCnt].x) <= eps && fabs(previous[1].y - previous[previousCnt].y) <= eps)
            previousCnt--;
        previous[previousCnt + 1] = previous[1];
    }
}
  
inline bool sgn (point A, point B, point C)
{
    long double cc;
    cc = (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
    if (cc < -eps)
        return 0;
    return 1;
}
  
inline long double ccw(point A, point B, point C) {
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
}
  
inline long double dist(point A, point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
  
int solve(point P) {
    if (nn == 1) {
        if (fabs(P.x - x[1].x) <= eps && fabs(P.y - x[1].y) <= eps)
            return 1;
        return 0;
    }
    int st = 2, dr = nn;
    int ret = -1;
    while (st <= dr) {
        int med = (st + dr) / 2;
        if (ccw(x[1], x[med], P) < -eps)
            dr = med - 1;
        else if (ccw(x[1], x[med + 1], P) > eps)
            st = med + 1;
        else {
            ret = med;
            dr = med - 1;
        }
    }
    if (ret == -1)
        return 0;
    point A = x[ret];
    point B = x[ret + 1];
    point C = x[1];
    point D = P;
    if (fabs(ccw(A, B, D)) < eps) {
        if (fabs(dist(A, D) + dist(D, B) - dist(A, B)) <= eps)
            return 1;
        return 0;
    }
    if (fabs(ccw(A, C, D)) < eps) {
        if (fabs(dist(A, D) + dist(D, C) - dist(A, C)) <= eps)
            return 1;
        return 0;
    }
    if (fabs(ccw(B, C, D)) < eps) {
        if (fabs(dist(B, D) + dist(D, C) - dist(B, C)) <= eps)
            return 1;
        return 0;
    }
    if (sgn (A, B, D) == sgn (B, C, D) && sgn (B, C, D) == sgn (C, A, D))
        return 1;
    return 0;
}
  
int main() {
    freopen("copacsmenar.in", "r", stdin);
    freopen("copacsmenar.out", "w", stdout);
  
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    assert(1 <= n && n <= 50);
    assert(1 <= m && m <= n * (n - 1));
    assert(1 <= q && q <= 100000);
  
    for (int i = 1; i < n; ++i) {
        int xx, yy, cc;
        scanf("%d%d%d", &xx, &yy, &cc);
        assert(1 <= xx && xx <= n);
        assert(1 <= yy && yy <= n);
        assert (xx != yy) ;
        assert(-1000 <= cc && cc <= 1000);
        G[xx].push_back(make_pair(yy, cc));
        G[yy].push_back(make_pair(xx, cc));
  
    }
    dfs_levels(1);
    int nr_noduri = 0;
    for (int i = 1; i <= n; ++i)
        nr_noduri += vis[i];
    assert(nr_noduri == n);
    int cnt = 0;
    map <pair <int, int>, bool> M;
    for (int i = 1; i <= m; ++i) {
        int nod1, nod2, vmin, vmax;
        scanf("%d%d%d%d", &nod1, &nod2, &vmin, &vmax);
        int L = LCA(nod1, nod2);
        assert (nod1 != nod2) ;
        assert(1 <= nod1 && nod1 <= n);
        assert(1 <= nod2 && nod2 <= n);
        assert(-10000000 <= vmin && vmin <= 10000000);
        assert(-10000000 <= vmax && vmax <= 10000000);
        pair <int, int> par = make_pair(nod1, nod2);
        assert (M.find(par) == M.end());
        M[par] = 1;
        int dist1 = get_dist(nod1, L);
        int dist2 = get_dist(nod2, L);
        ++cnt;
        R[cnt].A = dist1;
        R[cnt].B = dist2;
        R[cnt].C = -vmin;
        ++cnt;
        R[cnt].A = -dist1;
        R[cnt].B = -dist2;
        R[cnt].C = vmax;
    }
  
    precalc(cnt);
    for (int i = previousCnt + 1; i <= 2 * previousCnt; ++i)
        previous[i] = previous[i - previousCnt];
    int idx = 1;
    for (int i = 2; i <= previousCnt; ++i)
        if (previous[idx].y - previous[i].y > eps || (fabs(previous[idx].y - previous[i].y) < eps && previous[idx].x - previous[i].x > eps))
            idx = i;
    for (int i = 1; i <= previousCnt; ++i)
        x[i] = previous[idx + i - 1];
    x[previousCnt + 1] = x[1];
    nn = previousCnt;
    for (int i = 1; i <= q; ++i) {
        int xx, yy;
        scanf("%d%d", &xx, &yy);
        assert(-10000000 <= xx && xx <= 10000000);
        assert(-10000000 <= yy && yy <= 10000000);
        printf("%d\n", solve(make_pair(xx, yy)));
    }
    return 0;
}