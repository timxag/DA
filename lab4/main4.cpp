#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdio>

using namespace std;

vector<string> ReadPattern();
void BuildZBlocks(vector<string> pattern, vector<size_t> &z);
void ZFunc(vector<string> &pattern);
void CalculateSP(const vector<size_t> &z, vector<int> &spWeak);
void FailureFunc(vector<int> &sp, vector<int> &fail);

int main() {

    vector<string> pattern = ReadPattern();
    ZFunc(pattern);

    return 0;
}

void ZFunc(vector<string> &pattern) {

    size_t pattSize = pattern.size();

    vector<size_t> z(pattSize);
    BuildZBlocks(pattern, z);

    vector<int> sp(pattSize);
    CalculateSP(z, sp);
    z.clear();

    vector<int> fail(pattSize + 1);
    FailureFunc(sp, fail);
    sp.clear();

    char ch;
    string word;
    bool wordFound = false;

    queue<pair<int, int> > pos;
    pair<int, int> tmp;
    tmp.first = 1;
    tmp.second = 0;

    size_t pattPos = 0;

    do {
        ch = getchar();
        if (ch == ' ' || ch == '\t' || ch == EOF) {
            if (wordFound) {
                ++tmp.second;
                if (pos.size() == pattSize) {
                    pos.pop();
                }
                pos.push(tmp);

                while (pattPos > 0 && pattern[pattPos] != word) {
                    pattPos = fail[pattPos];
                }

                if (pattern[pattPos] == word) {
                    ++pattPos;
                }
                if (pattPos == pattSize) {
                    //вхождение
                    cout << pos.front().first << ", " << pos.front().second << endl;
                    pattPos = fail[pattPos];
                }
            }
            wordFound = false;
        }
        else if (ch == '\n' ) {
            if (wordFound) {
                ++tmp.second;
                if (pos.size() == pattSize) {
                    pos.pop();
                }
                pos.push(tmp);

                while (pattPos > 0 && pattern[pattPos] != word) {
                    pattPos = fail[pattPos];
                }
                if (pattern[pattPos] == word) {
                    ++pattPos;
                }
                if (pattPos == pattSize) {
                    //вхождение
                    cout << pos.front().first << ", " << pos.front().second << endl;
                    pattPos = fail[pattPos];
                }
            }
            ++tmp.first;
            tmp.second = 0;
            wordFound = false;
        }
        else {
            wordFound = true;
            word += tolower(ch);
            continue;
        }
        word.clear();
    } while (ch != EOF);
}

void BuildZBlocks(vector<string> pattern, vector<size_t> &z) {

    size_t pattSize = pattern.size();
    size_t r = 0;
    size_t l = 0;

    for (size_t i = 1; i < pattSize; ++i) {
        if (i < r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < pattSize && pattern[z[i]] == pattern[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i;
            r = i + z[i] - 1;
    }
}

void CalculateSP(const vector<size_t> &z, vector<int> &spWeak) {

    int size = z.size();
    vector<int> spStrict(size);
    int i;

    for (int j = size - 1; j > 0; j--) {
        i = j + z[j] - 1;
        spStrict[i] = z[j];
    }

    spWeak[size - 1] = spStrict[size - 1];
    for (i = size - 2; i > 0; i--) {
        spWeak[i] = max(spWeak[i + 1] - 1, spStrict[i]);
    }
}

void FailureFunc(vector<int> &sp, vector<int> &fail) {

    int size = fail.size();
    for (size_t i = 1; i < size; i++) {
        fail[i] = sp[i - 1];
    }

//    cout << "FailFunc: " << endl;
//    for (int i = 0; i <= size; i++) {
//        cout << i << ": " << fail[i] << endl;
//    }
}

vector<string> ReadPattern() {

    string word;
    char ch;
    vector<string> pattern;

    do {
        ch = getchar();
        if (ch == ' ' || ch == '\n') {
            if (!word.empty()) {
                pattern.push_back(word);
            }
            word.clear();
        } else {
            word += tolower(ch);
        }
    } while (ch != '\n');


    return pattern;
}
