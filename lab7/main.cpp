#include <bits/stdc++.h>
using namespace std;

int16_t size_n, size_m;

int32_t Max_Square_in_Line(vector<int16_t> &column)
{
    stack<int16_t> stack;
    int32_t max_count = 0;

    int16_t i = 0;
    while(i < size_m || !stack.empty())
    {
        if(stack.empty() || (column[stack.top()] <= column[i] && i < size_m))
        {
            stack.push(i);
            i++;
        }
        else
        {
            int16_t last_elem = stack.top();
            stack.pop();
            int32_t current_count = column[last_elem] * (stack.empty() ? i : i - stack.top() - 1);

            if (current_count > max_count)
            {
                max_count = current_count;
            }
        }
    }
    return  max_count;
}
void Read_Rectangle(vector<vector<int8_t> > &rectan) {
    rectan.resize(size_n);
    for (int i = 0; i < size_n; ++i) {
        rectan[i].resize(size_m);
        for (int j = 0; j < size_m; ++j) {
            cin >> rectan[i][j];
        }
    }
}
int main()
{
    cin >> size_n >> size_m;
    vector<vector<int8_t> > rectangle;
    Read_Rectangle(rectangle);

    vector<int16_t> column_count(size_m);
    int32_t max_sqr = 0;

    for (int i = 0; i < size_n; ++i)
    {
        for (int j = 0; j < size_m; ++j)
        {
            if (rectangle[i][j] == '0')
            {
                column_count[j]++;
            }
            else
            {
                column_count[j] = 0;
            }
        }
        int32_t current_sqr = Max_Square_in_Line(column_count);
        if (current_sqr > max_sqr)
        {
            max_sqr = current_sqr;
        }
    }

    cout <<  max_sqr << endl;

    return 0;
}
