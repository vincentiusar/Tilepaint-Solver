#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

typedef long long ll;
typedef vector< ll > vl;
typedef vector< vector<ll> > vll;
typedef vector< vector< pair<ll, bool> > > vlb;
typedef vector< vector<bool> > vbb;

ll N, M;
auto timeStart = high_resolution_clock::now();

bool checkSum(vl CC, vl CR) {
    ll sum_row = 0, sum_column = 0;
    for (ll item : CC) {
        if (item == -1) return true;
        sum_column += item;
    }

    for (ll item : CR) {
        if (item == -1) return true;
        sum_row += item;
    }

    return sum_column == sum_row;
}
 
bool checkIfMatch(vlb &cell, vl CC, vl CR) {

    vl coloredCol = vl(M, 0), coloredRow = vl(N, 0);

    for (ll i = 0; i < N; i++) 
        for (ll j = 0; j < M; j++) {
            if (cell[i][j].second) {
                coloredCol[j]++;
                coloredRow[i]++;
            }
        }

    for (ll j = 0; j < M; j++) {
        if (CC[j] != -1 && coloredCol[j] != CC[j]) {
            return false;
        }
    }
    
    for (ll j = 0; j < N; j++) {
        if (CR[j] != -1 && coloredRow[j] != CR[j]) {
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

void findPossiblePaint(vlb &cell, ll N, vl CC, vl CR) {

    // BRUTE FORCE
    ll nilai = (1 << N);
    for (ll bitmask = 0; bitmask <= nilai; bitmask++) {
        if (duration_cast<milliseconds>(high_resolution_clock::now() - timeStart).count() > 600000) {
            cout << "TOO SLOW" << endl;
            return;
        }
        
        for (int k = 0; k < N; k++) {
            if (((1 << k) & bitmask) > 0) {
                color(cell, k+1, 1);
            }
        }

        if (checkIfMatch(cell, CC, CR)) {
            cout << "FOUND VALID COMBINATION! : " << endl;
            for (int k = 0; k < N; k++) {
                if (((1 << k) & bitmask) > 0) {
                    cout << k + 1 << " ";
                }
            }
            cout << endl;
            return;
        }
        for (int k = 0; k < N; k++) {
            if (((1 << k) & bitmask) > 0) {
                color(cell, k+1, 0);
            }
        }
    }
    cout << "NO SOLUTION" << endl;
}

int main() {
    cin >> N >> M;
    vl CR(N), CC(M);
    for (int i = 0; i < M; i++) {
        cin >> CC[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> CR[i];
    }

    ll t = 0;
    vlb cell(N, (vector< pair<ll, bool> >(M, {0, 0})));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> cell[i][j].first;
            t = max(t, cell[i][j].first);
        }
    }

    if (N >= 12 && M >= 12) { cout << "too large"; return 0; }
    
    timeStart = high_resolution_clock::now();

    findPossiblePaint(cell, t, CC, CR);

    auto timeEnd = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(timeEnd - timeStart);

    cout << "Execution Time: " << duration.count() << "ms." << endl;
}