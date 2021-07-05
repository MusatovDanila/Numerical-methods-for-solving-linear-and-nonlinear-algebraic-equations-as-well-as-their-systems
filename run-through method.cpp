#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

int main() {
	int n = 5;
	//,m;
	/*
	cout << "Please, enter dimension of the Matrix" << endl << endl;
	cin >> n;
	if (n < 2) {
		cout << "wrong dimension of Matrix";
		return 0;
	};
	cout << "Please, enter quantity diagonals in Matrix" << endl << endl;
	cin >> m;
	*/
	/*
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	vector<vector<int>> matrix_1(n, vector<int>(n, 0));
	
	
	for (int i = 0; i < m-2; i++){
		cin >> matrix[0][i];
	}
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> matrix[i][i - 1];
			cin >> matrix[i][i];
			cin >> matrix[i][i + 1];
		}
	}
	for (int i = m-2; i > -1; i--){
		cin >> matrix[n - 1][n - i - 1];
	}
	*/
	vector<double> a(n, 0);
	vector<double> b(n, 0);
	vector<double> c(n, 0);
	vector<double> d(n, 0);
	vector<double> a1(n, 0);
	vector<double> b1(n, 0);
	vector<double> c1(n, 0);
	vector<double> d1(n, 0);
	vector<double> P(n, 0);
	vector<double> Q(n, 0);
	vector<double> x(n, 0);
			  b[0] =  -6; c[0] =  3; d[0] =  -33;
	a[1] = 6; b[1] = -23; c[1] = -9; d[1] = -107;
	a[2] = 2; b[2] =  -7; c[2] = -1; d[2] =   18;
	a[3] = 5; b[3] =  15; c[3] =  9; d[3] =  -69;
	a[4] = 5; b[4] = -11;		     d[4] =  -31;

			   b1[0] =  -6; c1[0] =  3; d1[0] =  -33;
	a1[1] = 6; b1[1] = -23; c1[1] = -9; d1[1] = -107;
	a1[2] = 2; b1[2] =  -7; c1[2] = -1; d1[2] =   18;
	a1[3] = 5; b1[3] =  15; c1[3] =  9; d1[3] =  -69;
	a1[4] = 5; b1[4] = -11;				d1[4] =  -31;
	/*
	cout << "Please, enter value of a diagonal in Matrix" << endl << endl;
	for (int i = 1; i < n; ++i) {
		cin >> a[i];
		a1[i] = a[i];
	}
	cout << "Please, enter value of b diagonal in Matrix" << endl << endl;
	for (int i = 0; i < n; ++i) {
		cin >> b[i];
		b1[i] = b[i];
	}
	cout << "Please, enter value of c diagonal in Matrix" << endl << endl;
	for (int i = 0; i < n - 1; ++i) {
		cin >> c[i];
		c1[i] = c[i];
	}
	cout << "Please, enter value of d column in Matrix" << endl << endl;
	for (int i = 0; i < n; ++i) {
		cin >> d[i];
		d1[i] = d[i];
	}
	*/
	P[0] = -c[0] / b[0];
	cout << "P[" << 0 << "] = " << P[0] << endl;
	Q[0] = d[0] / b[0];
	cout << "Q[" << 0 << "] = " << Q[0] << endl << endl;
	for (int i = 1; i < n; ++i) {
		P[i] = -c[i] / (b[i] + a[i] * P[i - 1]);
		cout << "P[" << i << "] = " << P[i] << endl;
		Q[i] = (d[i] - a[i] * Q[i - 1]) / (b[i] + a[i] * P[i - 1]);
		cout << "Q[" << i << "] = " << Q[i] << endl << endl;
	}
	x[n - 1] = Q[n-1];
	cout << endl << "x[" << n - 1 << "] = " << x[n - 1] << endl;

	for (int i = n-2; i > -1; --i) {
		x[i] = P[i] * x[i + 1] + Q[i];
		cout << endl << "x[" << i << "] = " << x[i] << endl ;
	}
	int proofer = 0;
	proofer = (fabs((b1[0] * x[0] + c1[0] * x[1]) - d1[0])<0.00001) ? ++proofer : proofer;
	cout << (b1[0] * x[0] + c1[0] * x[1]) << endl;
	for (int i = 1; i < n-1; ++i) {
		proofer = (fabs((a1[i] * x[i - 1] + b1[i] * x[i] + c1[i] * x[i + 1]) - d1[i])<0.00001) ? ++proofer: proofer;
		cout << (a1[i] * x[i - 1] + b1[i] * x[i] + c1[i] * x[i + 1]) << endl;
	}
	proofer = (fabs((a1[n - 1] * x[n - 2] + b1[n - 1] * x[n - 1]) - d1[n - 1]) < 0.00001) ? ++proofer : proofer;
	cout <<	a1[n - 1] * x[n - 2] + b1[n - 1] * x[n - 1] << endl;
	if (proofer == n) cout << endl << "all good" << endl << endl;
	else cout << endl << "all bad" << endl << endl;
	system("pause");
	return 0;
}