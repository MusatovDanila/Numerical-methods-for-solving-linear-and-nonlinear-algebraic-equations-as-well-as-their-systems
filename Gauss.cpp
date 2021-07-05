#include<iostream>
#include<cmath>
using namespace std;

int main() {
	int n = 4;
	/*
	cin >> n;
	*/
	double** matrix = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; ++i) {
		matrix[i] = (double*)malloc(n * sizeof(double));
	}
	double** matrix1 = (double**)malloc(n * sizeof(double*));
	for (int i = 0; i < n; ++i) {
		matrix1[i] = (double*)malloc(n * sizeof(double));
	}
	/*
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> matrix[i][j];
		}
	}
	*/
	matrix[0][0] = -2; matrix[0][1] = -1; matrix[0][2] = -9; matrix[0][3] = -5;
	matrix[1][0] = -4; matrix[1][1] = 4; matrix[1][2] = -2; matrix[1][3] = 6;
	matrix[2][0] = 5; matrix[2][1] = 0; matrix[2][2] = 7; matrix[2][3] = -4;
	matrix[3][0] = 9; matrix[3][1] = 0; matrix[3][2] = 7; matrix[3][3] = 7;

	matrix1[0][0] = -2; matrix1[0][1] = -1; matrix1[0][2] = -9; matrix1[0][3] = -5;
	matrix1[1][0] = -4; matrix1[1][1] = 4; matrix1[1][2] = -2; matrix1[1][3] = 6;
	matrix1[2][0] = 5; matrix1[2][1] = 0; matrix1[2][2] = 7; matrix1[2][3] = -4;
	matrix1[3][0] = 9; matrix1[3][1] = 0; matrix1[3][2] = 7; matrix1[3][3] = 7;
	double* c, h;
	double* b = (double*)malloc(n * sizeof(double));
	double* b1 = (double*)malloc(n * sizeof(double));
	b[0] = 93; b[1] = 16; b[2] = -80; b[3] = -119;
	b1[0] = 93; b1[1] = 16; b1[2] = -80; b1[3] = -119;
	bool flag = 0;
	for (int i = 0, e = 0; i < n; ++i) {
		if (matrix[i][i] == 0) {
			e = i + 1;
			while (e < n && matrix[i][i] == 0) {
				if (matrix[e][i] != 0) {
					h = b[i];
					c = matrix[i];
					b[i] = b[e];
					matrix[i] = matrix[e];
					b[e] = b[i];
					matrix[e] = c;
				}
				e++;
			}
			if (matrix[i][i] == 0 && e == n) {
				flag = 1;
				break;
			}
		}
		for (int q = n - 1; q > i; q--) {
			b[q] -= matrix[q][i] * b[i] / matrix[i][i];
			for (int j = n - 1; j > i - 1; --j) {
				matrix[q][j] -= (matrix[i][j] / matrix[i][i])*matrix[q][i];
			}
		}
		for (int o = 0; o < n; ++o) {
			for (int s = 0; s < n; ++s) {
				cout << matrix[o][s] << "  ";
			}
			cout << "=  " << b[o] << endl;
		}
		cout << matrix[i][i] << endl << endl;
	}
	if (flag == 1) { cout << "net vozmojnosti diagoalizovat"; return 0; }
	for (int i = n - 1; i > -1; --i) {
		if (matrix[i][i] != 0) {
			for (int q = i - 1; q > -1; q--) {
				b[q] -= b[i] * matrix[q][i] / matrix[i][i];
				matrix[q][i] = 0;
			}
			b[i] = b[i] / matrix[i][i];
			matrix[i][i] = 1;
		}
		for (int o = 0; o < n; ++o) {
			for (int s = 0; s < n; ++s) {
				cout << matrix[o][s] << "  ";
			}
			cout << "=  " << b[o] << endl;
		}
		cout << "x[" << i << "] = " << b[i] << endl << endl;
	}
	int t = 0;
	for (int i = 0; i < n; ++i) {
		if (fabs((b[0] * matrix1[i][0] + b[1] * matrix1[i][1] + b[2] * matrix1[i][2] + b[3] * matrix1[i][3]) - b1[i])<0.0001)t++;
	}
	if (t == n)cout << "all good" << endl << endl;
	else cout << "all bad"<< endl << endl;
	
	system("pause");
}