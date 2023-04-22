#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <omp.h>

using namespace std;

const int MAXN = 100;
const int MAXK = 400;

bitset<MAXN> D[MAXK + 1];

bool is_dominating_set(const bitset<MAXN>& Dk, const vector<vector<int>>& G, int k) {
    bool all_adjacent = true;
    for (int v = 0; v < G.size() && all_adjacent; v++) {
        if (!Dk.test(v)) {
            all_adjacent = any_of(G[v].begin(), G[v].end(), [&](int u) {
                return Dk.test(u);
            });
        }
    }
    return all_adjacent;
}

void minimum_dominating_set(int N, const vector<vector<int>>& G) {
    int mink = N;
    for (int v = 0; v < N; v++) {
        vector<int> remaining_vertices;
        for (int u = 0; u < N; u++) {
            if (u != v && !G[v][u]) {
                remaining_vertices.push_back(u);
            }
        }
        int d = remaining_vertices.size();
        if (d <= MAXK) {
            bitset<MAXN> Dk;
            Dk.reset();
            for (int u : remaining_vertices) {
                Dk.set(u);
            }
            Dk.set(v);
            D[d] = Dk;
            if (d < mink) {
                mink = d;
            }
        } else if (d < mink) {
            mink = d;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Failed to open input file: " << argv[1] << '\n';
        return 1;
    }

    ofstream fout(argv[2]);
    if (!fout) {
        cerr << "Failed to open output file: " << argv[2] << '\n';
        return 1;
    }

    int N, E;
    fin >> N >> E;
    vector<vector<int>> G(N);
    for (int i = 0; i < E; i++) {
        int u, v;
        fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    fin.close();

    omp_set_num_threads(12);
    minimum_dominating_set(N, G);

    int mink = 1;
    for (int k = 2; k <= MAXK && k <= N; k++) {
        if (D[k].any()) {
            mink = k;
            break;
        }
    }

    fout << mink << ":";
    for (int i = 0; i < N; i++) {
        if (D[mink].test(i)) {
            fout << "1";
        } else {
            fout << "0";
        }
    }

    fout.close();
    return 0;
}
