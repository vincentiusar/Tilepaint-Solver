#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

typedef vector< int > vl;
typedef vector< vector<int> > vll;
typedef vector< vector< pair<int, bool> > > vlb;
typedef vector< vector<bool> > vbb;

auto timeStart = high_resolution_clock::now();
int N, M;

bool IsValidConf(vlb &CG, vl CC, vl CR) {
    vl coloredCol = vl(M, 0), coloredRow = vl(N, 0);

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) {
            if (CG[i][j].second) {
                coloredCol[j]++;
                coloredRow[i]++;
            }
        }

    for (int j = 0; j < M; j++) {
        if (CC[j] != -1 && coloredCol[j] > CC[j]) {
            return false;
        }
    }
    
    for (int j = 0; j < N; j++) {
        if (CR[j] != -1 && coloredRow[j] > CR[j]) {
            return false;
        }
    }

    return true;
}

bool IsSumEqual(vl CC, vl CR) {
    int sum_row = 0, sum_column = 0;
    for (int item : CC) {
        if (item == -1) return true;
        sum_column += item;
    }

    for (int item : CR) {
        if (item == -1) return true;
        sum_row += item;
    }

    return sum_column == sum_row;
}

bool IsRemainRowUncolored(vlb &CG, vl CR, int n, int now) {
    vl coloredRow = vl(N, 0);

    vl odd_row_remain(N);

    vll row(N, vl(n+1));
    
    for (int i = 0; i < N; i++) {
        if (CR[i] == -1) continue;
        for (int j = 0; j < M; j++) {
            if (CG[i][j].second) {
                coloredRow[i]++;
            }
            row[i][CG[i][j].first]++;
        }

        if (coloredRow[i] % 2 == CR[i] % 2) continue;

        for (int j = 0; j < M; j++) {
            if (row[i][CG[i][j].first] % 2 == 1 && !CG[i][j].second) {
                if (now < CG[i][j].first) {
                    odd_row_remain[i]++;
                    row[i][CG[i][j].first] = 0;
                }
            }
        }

        if (coloredRow[i] % 2 == 0 && CR[i] % 2 == 1 && odd_row_remain[i] < 1) {
            return false;
        }

        if (coloredRow[i] % 2 == 1 && CR[i] % 2 == 0 && odd_row_remain[i] < 1) {
            return false;
        }
    }

    return true;
}

bool IsRemainColUncolored(vlb &CG, vl CC, int n, int now) {
    vl coloredCol = vl(M, 0);

    int odd_col_remain[M] = {0};

    vll col(M, vl(n+1));
    
    for (int i = 0; i < M; i++) {
        if (CC[i] == -1) continue;

        for (int j = 0; j < N; j++) {
            if (CG[j][i].second) {
                coloredCol[i]++;
            }
            col[i][CG[j][i].first]++;
        }

        if (coloredCol[i] % 2 == CC[i] % 2) continue;

        for (int j = 0; j < N; j++) {
            if (col[i][CG[j][i].first] % 2 == 1 && !CG[j][i].second) {
                if (now < CG[j][i].first) {
                    odd_col_remain[i]++;
                    col[i][CG[j][i].first] = 0;
                }
            }
        }

        if (coloredCol[i] % 2 == 0 && CC[i] % 2 == 1 && odd_col_remain[i] < 1) {
            return false;
        }

        if (coloredCol[i] % 2 == 1 && CC[i] % 2 == 0 && odd_col_remain[i] < 1) {
            return false;
        }
    }

    return true;
}

bool ComplyConstraint(vlb &CG, vl CC, vl CR) {

    vl coloredCol = vl(M, 0), coloredRow = vl(N, 0);

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) {
            if (CG[i][j].second) {
                coloredCol[j]++;
                coloredRow[i]++;
            }
        }

    for (int i = 0; i < M; i++) {
        if (CC[i] != -1 && coloredCol[i] != CC[i]) {
            return false;
        }
    }
    
    for (int i = 0; i < N; i++) {
        if (CR[i] != -1 && coloredRow[i] != CR[i]) {
            return false;
        }
    }

    return true;
}

vll solution;
vl conf;

void color(vlb &CG, int tile, int val) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (CG[i][j].first == tile) {
                CG[i][j].second = val;
            }
        }
    }
}

void backtrack(int now, vlb &CG, int n, vl CC, vl CR) {

    if (solution.size()) {
        return;
    }
    
    if (now > n) {
        if (ComplyConstraint(CG, CC, CR)) {
            solution.push_back(conf);
        }
    } else {
        for (int i = 1; i >= 0; i--) {
            color(CG, now, i);
            if (i == 0) {
                backtrack(now+1, CG, n, CC, CR);
            } else {
                conf.push_back(now);
                if ((!IsRemainRowUncolored(CG, CR, n, now) || !IsRemainColUncolored(CG, CC, n, now)) || !IsValidConf(CG, CC, CR)) {
                    color(CG, now, 0);
                    conf.pop_back(); 
                    continue;
                }
                backtrack(now+1, CG, n, CC, CR);
                conf.pop_back();
                color(CG, now, 0);
            }
        }
    }
}

void findPossiblePaint(vlb CG, int n, vl CC, vl CR) {

    if (!IsSumEqual(CC, CR)) {
        cout << "No Solution" << endl;
        return;
    }

    backtrack(1, CG, n, CC, CR);

    if (solution.size() == 0) {
        cout << "No Solution" << endl;
        return;
    }
    cout << "Solution : " << endl;
    for (int i = 0; i < solution.size(); i++) {
        for (int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < solution.size(); i++) {
        for (int k = 0; k < CR.size(); k++) {
            for (int l = 0; l < CC.size(); l++) {
                if (find(solution[i].begin(), solution[i].end(), CG[k][l].first) != solution[i].end()) {
                    cout << 1 << " ";
                } else cout << 0 << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    // ios_base::sync_with_stdio(false);cin.tie(NULL);
    
    cin >> N >> M;
    vl CR(N), CC(M);
    for (int i = 0; i < M; i++) {
        cin >> CC[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> CR[i];
    }

    int t = 0;
    vlb IG(N, (vector< pair<int, bool> >(M, {0, 0})));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> IG[i][j].first;
            t = max(t, IG[i][j].first);
        }
    }

    timeStart = high_resolution_clock::now();

    findPossiblePaint(IG, t, CC, CR);

    auto timeEnd = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(timeEnd - timeStart);

    cout << "Execution Time: " << duration.count() << "ms." << endl;
}