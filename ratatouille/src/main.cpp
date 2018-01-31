#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "ratatouille.h"

using namespace std;

//#define DEBUG

int number_of_kits(vector<int>& R, vector<vector<int>>& Q) {
#ifdef DEBUG
    cout << endl;
#endif
    int kits = 0;
    vector<vector<int>::iterator> next(R.size());
    for(size_t i = 0; i < R.size(); i++)
        next[i] = Q[i].begin();

    int servings = 1;
    while(1) {
        bool canKit = true;
#ifdef DEBUG
        stringstream packed;
#endif
        for(size_t i = 0; i < R.size(); i++) {
            int const Rs = servings * R[i];
            int const q_max = 110 * Rs / 100;
            int const q_min = 90 * Rs / 100;

            next[i] = find_if(
                next[i],
                Q[i].end(),
                [&q_min](int q) {
                    return (q >= q_min);
                }
            );
            if(next[i] == Q[i].end()) {
                goto out;
            }
            if(*next[i] > q_max) {
                canKit = false;
                servings++;
                break;
            }
#ifdef DEBUG
            packed << " " << *next[i];
#endif
        }
        if(canKit) {
#ifdef DEBUG
            cout << servings << ":" << packed.str() << endl;
#endif
            kits++;
            for(size_t i = 0; i < R.size(); i++)
                next[i]++;
        }
    }
out:
    return kits;
}

int main(int argc, char *argv[]) {
    int T;
    cin >> T;
    for(int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";

        int N, P;
        cin >> N >> P;

        vector<int> R;
        R.resize(N);

        for(int n = 0; n < N; n++) {
            cin >> R[n];
        }

        vector<vector<int>> Q;
        Q.resize(N);

        for(int i = 0; i < N; i++) {
            Q[i].resize(P);
            for(int j = 0; j < P; j++) {
                cin >> Q[i][j];
            }
            sort(Q[i].begin(), Q[i].end());
        }
        cout << number_of_kits(R, Q) << endl;
    }

    return 0;
}
