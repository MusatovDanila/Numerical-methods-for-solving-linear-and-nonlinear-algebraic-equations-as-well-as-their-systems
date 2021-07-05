#include<iostream>
#include<Eigen/Dense>

int main(){
	int n = 3;
	double eps = 0.001;
	//std::cin >> n;
	Eigen::MatrixXf a (n,n);
	Eigen::MatrixXf a_1 (n, n);
	Eigen::VectorXf d (n);
	Eigen::VectorXf d_1 (n);
	Eigen::VectorXf x(n);
	Eigen::VectorXf x_1(n);
	Eigen::VectorXf x_2(n);
	Eigen::VectorXf x_3(n);
	/*
	a(0, 0) = -2; a(0, 1) =  -7; a(0, 2) =  -8; a(0, 3) =  -2; d(0) = -51;
	a(1, 0) =  2; a(1, 1) = -17; a(1, 2) =  -6; a(1, 3) =  -2; d(1) =  85;
	a(2, 0) = -7; a(2, 1) =  -6; a(2, 2) = -23; a(2, 3) =  -3; d(2) =  71;
	a(3, 0) =  3; a(3, 1) =  -2; a(3, 2) =  -7; a(3, 3) = -13; d(3) =  91;
	*/
	a(0, 0) = 15; a(0, 1) =  -1; a(0, 2) =  2; d(0) =  1;
	a(1, 0) =  1; a(1, 1) = -23; a(1, 2) =  1; d(1) = -1;
	a(2, 0) =  1; a(2, 1) =   3; a(2, 2) = 30; d(2) =  2;


	//Eigen::VectorXf x_t(n);
	//x_t(0) = 97.8485; x_t(1) = 17.1478; x_t(2) = -41.9776; x_t(3) = 35.5456;
	
	for(int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j) {
			//std::cin >> a(i, j);
			a_1(i, j)= a(i, j); 
		}
	}
	
	for (int i = 0; i < n; ++i) {
		//std::cin >> d(i);
		d_1(i)= d(i);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			a(i, j) = (i != j) ? 0: a(i, i);
		}
	}
	d = a.inverse()*d;
	a = a.inverse()*(a - a_1);

	x(0) = 0; x(1) = 0; x(2) = 0;// x(3) = 0;
	x_1 = x;
	x_2 = x;
	float max_difference = 1;
	float now;
	float max_difference_1 = 0;
	float now_1=0;
	int h = 0;
	for (; max_difference>eps;) {
		std::cout << x << std::endl << std::endl << max_difference_1 << std::endl << std::endl << std::endl;
		++h;
	//	std::cout << x_1 << std::endl << std::endl;
		x_1 = x;
		x = a*x_1+d;
		max_difference = 0;
		max_difference_1 = 0;
		for (int i = 0; i < n; ++i) {
			now = fabs(x(i) - x_1(i));
			max_difference = (now > max_difference) ? now : max_difference;
			now_1 = fabs(d_1(i) - a_1(i,0)*x(0)- a_1(i, 1)*x(1) - a_1(i, 2)*x(2) /*- a_1(i, 3)*x(3)*/);
			max_difference_1 = (now_1 > max_difference_1) ? now_1 : max_difference_1;
		}

	}

	float check = 0;
	int checker = 0;
	for (int i = 0; i < n; ++i, check = 0) {
		for (int j = 0; j < n; ++j) {
			check += a_1(i, j) * x(j);
		}
		if (fabs(check - d_1(i)) < 0.1)++checker;
	}
	if (checker == n) { std::cout << "all good" << std::endl; }
	std::cout << h<< std::endl;

	max_difference = 1;
	now;
	max_difference_1 = 0;
	now_1 = 0;
	h = 0;
	for (; max_difference > eps;) {
		std::cout << x_2 << std::endl << std::endl << max_difference_1 << std::endl << std::endl << std::endl;
		//	std::cout << x_1 << std::endl << std::endl;
		++h;
		max_difference = 0;
		x_3 = x_2;
		max_difference_1 = 0;
		for(int i = 0; i < n; ++i) {
			x_2(i)= (a.row(i)* x_2 + d(i));
		}
		for (int i = 0; i < n; ++i) {
			now = fabs(x_3(i) - x_2(i));
			max_difference = (now > max_difference) ? now : max_difference;
			now_1 = fabs(d_1(i) - a_1(i, 0)*x(0) - a_1(i, 1)*x(1) - a_1(i, 2)*x(2) /*- a_1(i, 3)*x(3)*/);
			max_difference_1 = (now_1 > max_difference_1) ? now_1 : max_difference_1;
		}
	}
	check = 0;
	checker=0;
	for (int i = 0; i < n; ++i, check = 0) {
		for (int j = 0; j < n; ++j) {
			check += a_1(i, j) * x_2(j);
		}
		if (fabs(check-d_1(i))<0.1)++checker;
	}
	if (checker == n) { std::cout << "all good" << std::endl; }

	std::cout << h << std::endl;
	system("pause");
	return 0;
}