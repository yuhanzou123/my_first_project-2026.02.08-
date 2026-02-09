#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) cin >> a[i][j];
    }

    // If start or end is blocked, no path
    if (a[0][0] != 0 || a[m-1][n-1] != 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<vector<int>> dist(m, vector<int>(n, 0));
    queue<pair<int,int>> q;
    dist[0][0] = 1; // distance as number of nodes along path (count start as 1)
    q.push({0,0});
    int dr[4] = {0,1,0,-1};
    int dc[4] = {1,0,-1,0};

    while (!q.empty()) {
        auto [r,c] = q.front(); q.pop();
        if (r==m-1 && c==n-1) break; // reached
        for (int k=0;k<4;++k) {
            int nr=r+dr[k], nc=c+dc[k];
            if (nr>=0 && nr<m && nc>=0 && nc<n && a[nr][nc]==0 && dist[nr][nc]==0) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr,nc});
            }
        }
    }

    cout << dist[m-1][n-1] << '\n';
    return 0;
}
