#include<bits/stdc++.h>

using namespace std;

int grid[100][100];

int main() {
    for(int i=0; i<10; i++) grid[i][0] = grid[0][i] = 1;
    for(int i=1; i<10; i++) {
        for(int j=1; j<10; j++) {
            grid[i][j] = grid[i-1][j] + grid[i][j-1];
        }
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) printf("%6d", grid[i][j]);
        cout << endl;
    }
}
