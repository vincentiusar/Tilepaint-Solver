#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector< ll > vl;
typedef vector< vector<ll> > vll;
typedef vector< vector< pair<ll, bool> > > vlb;
typedef vector< vector<bool> > vbb;

ll N = 6, M = 7;

bool IsSumEqual(vl CC, vl CR) {
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
 
bool ComplyConstraint(vlb CG, vl CC, vl CR) {

    vl coloredCol = vl(M, 0), coloredRow = vl(N, 0);

    for (ll i = 0; i < N; i++) 
        for (ll j = 0; j < M; j++) {
            if (CG[i][j].second) {
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

bool IsAllSame(vlb CG, int p) {
    int colored[p+1] = {0}, cellTotal[p+1] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cellTotal[CG[i][j].first]++; 
            if (CG[i][j].second) colored[CG[i][j].first]++;
        }
    }
    
    for (int i = 0; i < p+1; i++) {
        if (colored[i] != cellTotal[i] && colored[i]) return false;
    }

    return true;
}

bool mainValidation(vlb CG, vl CC, vl CR, int n) {
    bool rule1 = IsSumEqual(CC, CR);
    bool rule2 = IsAllSame(CG, n);
    bool rule3 = ComplyConstraint(CG, CC, CR);

    cout << "rule 1 : " << rule1 << endl;
    cout << "rule 2 : " << rule2 << endl;
    cout << "rule 3 : " << rule3 << endl;
    return rule1 && rule2 && rule3;
}

int main() {
    ll p = -1;
    
    // input
    cin >> N >> M;
    vl CR(N), CC(M);
    for (int i = 0; i < M; i++) {
        cin >> CC[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> CR[i];
    }

    ll t = 0;
    vlb IG(N, (vector< pair<ll, bool> >(M, {0, 0})));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> IG[i][j].first;
            t = max(t, IG[i][j].first);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> IG[i][j].second;
        }
    }

    cout << mainValidation(IG, CC, CR, t);
}