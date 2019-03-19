#include <bits/stdc++.h>

#include "tsuffixtree.h"
using namespace std;
int main() {
    TSuffixTree tree;

    ios::sync_with_stdio(false);
    string str;
    cin >> str;

    tree.Build(str);

    size_t cnt = 1;
    while (cin >> str) {
        vector<size_t> result;
        tree.Find(str, result);

        if (!result.empty()) {
            cout << cnt << ": ";

            for (size_t i = 0; i < result.size() - 1; ++i) {
                cout << result[i] + 1 << ", ";
            }

            cout << result[result.size() - 1] + 1 << "\n";
        }

        ++cnt;
    }
}
