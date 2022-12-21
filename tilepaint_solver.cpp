#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector< ll > vl;
typedef vector< vector<ll> > vll;
typedef vector< vector< pair<ll, bool> > > vlb;
typedef vector< vector<bool> > vbb;


ll N = 6, M = 7;

bool validConf(vlb cell, vll mustPaint) {
    vll match(2);
    match[0] = (vl(M, 0));
    match[1] = (vl(N, 0));

    for (ll i = 0; i < N; i++) 
        for (ll j = 0; j < M; j++) {
            if (cell[i][j].second) {
                match[0][j]++;
                match[1][i]++;
            }
        }

    for (ll j = 0; j < M; j++) {
        if (mustPaint[0][j] != -1 && match[0][j] > mustPaint[0][j]) {
            return false;
        }
    }
    
    for (ll j = 0; j < N; j++) {
        if (mustPaint[1][j] != -1 && match[1][j] > mustPaint[1][j]) {
            return false;
        }
    }

    return true;
}

bool checkSum(vll mustPaint) {
    int sum_row = 0, sum_column = 0;
    for (int item : mustPaint[0]) {
        if (item == -1) return true;
        sum_column += item;
    }

    for (int item : mustPaint[1]) {
        if (item == -1) return true;
        sum_row += item;
    }

    return sum_column == sum_row;
}

bool checkOddEvenRowRemain(vlb cell, vll mustPaint, int n, vl painted) {
    vll match(2);
    match[0] = (vl(M, 0));
    match[1] = (vl(N, 0));

    for (ll i = 0; i < N; i++) {
        int total_odd_row_remain = 0;
        int row[n+1] = {0};
        
        for (ll j = 0; j < M; j++) {
            if (cell[i][j].second) {
                match[0][j]++;
                match[1][i]++;

            }
            row[cell[i][j].first]++;
        }
        for (int j = 0; j < n+1; j++) {
            if (row[j] % 2 == 1) total_odd_row_remain++;
        }

        for (int j = 0; j < painted.size(); j++) {
            if (row[painted[j]] % 2 == 1) total_odd_row_remain--;
        }

        if (match[1][i] % 2 == 0 && mustPaint[1][i] % 2 == 1 && total_odd_row_remain < 1) {
            return false;
        }

        if (match[1][i] % 2 == 1 && mustPaint[1][i] % 2 == 0 && total_odd_row_remain < 1) {
            return false;
        }
    }
    return true;
}
 
bool checkIfMatch(vlb cell, vll mustPaint) {

    vll match(2);
    match[0] = (vl(M, 0));
    match[1] = (vl(N, 0));

    for (ll i = 0; i < N; i++) 
        for (ll j = 0; j < M; j++) {
            if (cell[i][j].second) {
                match[0][j]++;
                match[1][i]++;
            }
        }

    // cout << "MATCH COUNT : " << endl;
    // for (ll j = 0; j < M; j++) {
    //     cout << match[0][j] << " ";
    // }
    // cout << endl;
    // cout << "MATCH COUNT : " << endl;
    // for (ll j = 0; j < N; j++) {
    //     cout << match[1][j] << " ";
    // }
    // cout << endl << endl;

    // cout << "MUST Paint Count : " << endl;
    // for (ll j = 0; j < M; j++) {
    //     cout << mustPaint[0][j] << " ";
    // }
    // cout << endl;
    
    // cout << "MUST PAINT COUNT : " << endl;
    // for (ll j = 0; j < N; j++) {
    //     cout << mustPaint[1][j] << " ";
    // }
    // cout << endl;

    for (ll j = 0; j < M; j++) {
        if (mustPaint[0][j] != -1 && match[0][j] != mustPaint[0][j]) {
            return false;
        }
    }
    
    for (ll j = 0; j < N; j++) {
        if (mustPaint[1][j] != -1 && match[1][j] != mustPaint[1][j]) {
            return false;
        }
    }

    return true;
}

vll solution;

void color(vlb &cell, int tile, int val) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (cell[i][j].first == tile) {
                cell[i][j].second = val;
            }
        }
    }
}

void backtrack(int now, vlb &cell, ll n, vll &mustPaint, vl &conf) {
    
    if (!validConf(cell, mustPaint))
        return;

    if (!checkOddEvenRowRemain(cell, mustPaint, n, conf))
        return;

    if (now > n) {      // kalau daerah now udah di luar n (number of tiles in grid)
        if (checkIfMatch(cell, mustPaint)) {
            solution.push_back(conf);
        }
    } else {
        for (int i = 0; i < 2; i++) {
            color(cell, now, i);
            if (i == 1) conf.push_back(now);    // kalau tile now diwarnai, masukan ke configuration
            backtrack(now+1, cell, n, mustPaint, conf);
            if (i == 1) conf.pop_back();    // kalau tadi diwarnai, pop back supaya tile tadi gada di configuration
            color(cell, now, 0);        // color balik klo ternyata gbs
        }
    }
}

void findPossiblePaint(vlb cell, ll N, vll mustPaint) {

    // BACKTRACK
    vl conf;
    if (!checkSum(mustPaint)) {
        cout << "No Solution" << endl;
        return;
    }

    backtrack(1, cell, N, mustPaint, conf);

    for (int i = 0; i < solution.size(); i++) {
        for (int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }
    if (solution.size() == 0) {
        cout << "No Solution" << endl;
    }

    // BRUTE FORCE
    // ll nilai = (1 << N);
    // for (ll bitmask = 0; bitmask <= nilai; bitmask++) {
    //     vl taken;
    //     // cout << "JALAN " << bitmask << " ";
    //     for (int k = 0; k < N; k++) {
    //         if (((1 << k) & bitmask) > 0) {
    //             color(cell, k+1, 1);
    //         }
    //     }

    //     for (auto item : taken) {
    //         cout << item << " ";
    //     }
    //     cout << endl;

    //     cout << " ";

    //     cout << endl;
    //     for (ll x : taken) {
    //         for (ll i = 0; i < N; i++) {
    //             for (ll j = 0; j < M; j++)
    //                 if (cell[i][j].first == x) cell[i][j].second = 1;
    //         }
    //     }

    //     if (checkIfMatch(cell, mustPaint, taken)) {
    //         cout << "FOUND VALID COMBINATION! : " << endl;
    //         for (auto item : taken) {
    //             cout << item << " ";
    //         }
    //         cout << endl;
    //         // return;
    //     }
    //     for (int k = 0; k < N; k++) {
    //         if (((1 << k) & bitmask) > 0) {
    //             color(cell, k+1, 0);
    //         }
    //     }
    // }
    // cout << "NO SOLUTION" << endl;
}

int main() {
    //solution color
    // 1 3 4 7 10 11 14 15 17 18 20
    // ans 2 5 8 9 11

    ll p = -1;
    vll mustPaint = 
        {
            // {3, 3, 3, 5, 4, 2, 5},
            // {5, 5, 3, 3, 5, 4},
            {4, 3, 2, 3, 5, 5, 4},
            {4, 5, 5, 3, 4, 5},
            // {8, 5, p, p, 3, p, p, p, p, p},
            // {7, p, 3, p, 4, 6, p, 7, 4, p},
            // {1, 4, 1, 2},
            // {1, 2, 3, 2}
        };

    ll a = 10, b = 11, c = 12, d = 13, e = 14, f = 15, g = 16, h = 17, i = 18, j = 19, k = 20, l = 21, m = 22, n = 23;
    vlb cell =
        {
            // {1, 2, 2, 2, 2, 3, 4},
            // {1, 2, 5, 5, 2, 3, 4},
            // {1, 1, 5, 5, 3, 3, 4},
            // {6, 7, 8, 8, 8, 9, 4},
            // {6, 7, 8, 9, 9, 9, 9},
            // {6, 6, a, b, b, c, c},
            {{1, 0}, {1, 0}, {2, 0}, {2, 0}, {2, 0}, {3, 0}, {3, 0}},
            {{4, 0}, {4, 0}, {4, 0}, {5, 0}, {5, 0}, {6, 0}, {6, 0}},
            {{7, 0}, {7, 0}, {8, 0}, {8, 0}, {9, 0}, {9, 0}, {9, 0}},
            {{a, 0}, {a, 0}, {a, 0}, {b, 0}, {b, 0}, {b, 0}, {c, 0}},
            {{d, 0}, {e, 0}, {e, 0}, {e, 0}, {f, 0}, {f, 0}, {g, 0}},
            {{h, 0}, {h, 0}, {i, 0}, {i, 0}, {j, 0}, {k, 0}, {k, 0}},
            // {1, 1, 2, 2, 2, 3, 3, 3, 4, 4},
            // {1, 1, 5, 2, 2, 2, 6, 6, 4, 4},
            // {7, 8, 5, 9, 9, a, 6, 6, 6, 4},
            // {7, 8, 5, 9, a, a, a, a, b, b},
            // {7, 8, 5, c, c, d, d, e, e, b},
            // {8, 8, 5, f, f, f, f, e, g, b},
            // {8, m, m, n, n, f, f, e, g, b},
            // {h, i, i, i, i, i, g, g, g, b},
            // {h, h, j, j, j, k, k, l, l, l},
            // {h, h, j, j, j, k, k, l, l, l},
            // {1, 2, 3, 4},
            // {5, 2, 6, 6},
            // {7, 8, 8, 9},
            // {a, b, c, 9},
        };

    // findPossiblePaint(cell, colored, 23, mustPaint);
    findPossiblePaint(cell, 20, mustPaint);
    // findPossiblePaint(cell, colored, 12, mustPaint);
    // for (ll i = 0; i < N; i++) {
    //     for (ll j = 0; j < M; j++)
    //         cout << colored[i][j] << " ";
    //     cout << endl;
    // }
}