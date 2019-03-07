#include <bits/stdc++.h>
using namespace std;
struct TGraph{
    vector<vector< pair<int,int> > > top;
    int count_top;
    int count_Side;
};

long long int Deikstra(TGraph &graph, int start, int finish) {
    vector<long long int> count(graph.count_top);
    priority_queue<pair<long long int, int> , vector<pair<long long int, int> >, greater<pair<long long int, int> > > que;

    for(int i = 0; i < graph.count_top; ++i) {
        count[i] = LLONG_MAX;
    }
    count[start] = 0;
    que.push(make_pair(0, start));

    while(!que.empty()) {
        int current = que.top().second;
        que.pop();
        vector<pair<int, int> >::iterator i;
        for (i = graph.top[current].begin(); i != graph.top[current].end(); ++i) {
            int tmp = i->first;
            int weight = i->second;

            if (count[tmp] > count[current] + weight) {
                count[tmp] = count[current] + weight;
                que.push(make_pair(count[tmp], tmp));
            }
        }
    }
    if(count[finish] == LLONG_MAX) {
        return -1;
    }
    return count[finish];
}

void Create_Graph(TGraph &graph, int &start, int &finish) {
    int top1;
    int top2;
    int weight;
    cin >> graph.count_top >> graph.count_Side >> start >> finish;
    graph.top.resize(graph.count_top);
    while(cin >> top1 >> top2 >> weight) {
        graph.top[top1 - 1].push_back(make_pair(top2 - 1, weight));
        graph.top[top2 - 1].push_back(make_pair(top1 - 1, weight));
    }
}

int main() {
    int start;
    int finish;
    long long int result;
    TGraph graph;
    Create_Graph(graph, start, finish);
    result = graph.count_top > 0 ? Deikstra(graph, start - 1, finish - 1) : -1;
    if(result < 0) {
        cout << "No solution" << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}



