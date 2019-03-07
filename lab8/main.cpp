#include <bits/stdc++.h>
using namespace std;

double sqr(double a, double b, double c) {
	double q = (a + b + c) / 2;
	return sqrt(q * (q - a) * (q - b) * (q - c));
}

int main() {
	int n;
	cin >> n;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a.rbegin(), a.rend());
	double _max = 0;
	int pos = 0;
	for(int i = 0; i <= n - 3; ++i) {
		if(a[i+1] + a[i+2] > a[i]) {
			double current = sqr(a[i], a[i+1], a[i+2]);
			if(current > _max) {
				pos = i;
				_max = current;
			}
		}
	}
	if(_max == 0) {
		cout << 0 << endl;
	} else {
        cout << fixed << setprecision(3) << _max << endl;
		for(int i = 2; i >= 0; --i) {
			cout << a[pos+i] << " ";
		}
		cout << endl;
	}
	return 0;
}
