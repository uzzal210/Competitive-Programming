#include<bits/stdc++.h>

using namespace std;

int n,m;
char grid[22][22];
int xRow, xCol;
int gold;

int dirR[] = {-1, -1, -1, 0, 0, +1, +1, +1};
int dirC[] = {-1, 0, +1, -1, +1, -1, 0, +1};

int getMin(int uR, int uC, int color[22][22], int mov, int goldCount) {

    if(goldCount == gold) {
        cout << mov << ' ' << max( abs(uR - xRow) , abs(uC - xCol) ) << endl;
        return mov + max(abs(uR - xRow), abs(uC - xCol));
    }
    //int color[22]; memset(color, 0, sizeof(color));
    color[uR][uC] = 1;
    //mov++;

    int ans = INT_MAX;
    for(int i=0; i<8; i++) { ///8 places in directional array
        int newR = uR+dirR[i], newC = uC+dirC[i];
        if(newR >= 0 && newR < n && newC >= 0 && newC < m) {
            if(grid[newR][newC] == 'g' && color[newR][newC] == 0) {
                int newColor[22][22]; for(int p=0; p<n; p++) for(int q=0; q<m; q++) newColor[p][q] = color[p][q];
                cout << "ager ans " << ans << " call jay " << newR << ' ' << newC << " GOLD " << endl;
                ans = min(ans, getMin(newR, newC, newColor, mov+1, goldCount+1));
                cout << "ekhn ans " << ans << " ferot ay " << newR << ' ' << newC << " GOLD " << endl;
            }
            else {
                if(color[newR][newC] == 0) {
                    int newColor[22][22]; for(int p=0; p<n; p++) for(int q=0; q<m; q++) newColor[p][q] = color[p][q];
                    cout << "ager ans " << ans << " call jay " << newR << ' ' << newC << endl;
                    ans = min(ans, getMin(newR, newC, newcolor, mov+1, goldCount) );
                    cout << "ekhn ans " << ans << " ferot ay " << newR << ' ' << newC << endl;
                }
            }
        }
    }
    cout << uR << ' ' << uC << " cell e ans " << ans << endl;
    return ans;
}

int main() {

    int t,T;
    scanf("%d", &T);
    for(t=1; t<=T; t++) {

        gold = 0;

        scanf("%d %d",&n, &m);
        for(int i=0; i<n; i++) {
            getchar();
            for(int j=0; j<m; j++) {
                scanf("%c", &grid[i][j]);
                if(grid[i][j] == 'x') xRow = i, xCol = j, grid[i][j] = '.';
                else if(grid[i][j] == 'g') gold++;
            }
        }

        int color[22][22]; memset(color, 0, sizeof(color));

        printf("Case %d: %d\n", t, getMin(xRow, xCol, color, 0, 0));
        //getMin(xRow, xCol,);
    }
}
