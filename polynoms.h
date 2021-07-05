//This code is the intellectual property of Danila Musatov .
//Contacts danilarumus2000@gmail.com
//This program contains a number of numerical methods for finding the root on the interval.
// Copyright reserved 2021 

#pragma once
#include<iostream>
#include<vector>	
#include<cmath>
#include<Eigen/Dense>
#include<Eigen/LU> 


using std::cout;
using std::vector;
template <typename T>
using v_func_v_x = vector < double(*)(T)>;
template <typename T>
using m_func_x = vector < vector <T>>;
using v_d = vector<double>;
using EVX = Eigen::VectorXf;
using EMX = Eigen::MatrixXf;
//using v_func_v_e_x = vector < double(*)(EVX x)>;

template <typename X>
double my_polynom_1(X x) {
	return (x[0] - cos(x[1]) - 3);
	//return (x[0] * x[0] - 2 * log10(x[1]) - 1);
}


template <typename X>
double my_polynom_2(X x) {
	return (x[1] - sin(x[0]) - 3);
	//return (x[0] * x[0] - 3 * x[0] * x[1] + 3);
}

template <typename X>
double my_f_1_d_1(X x) {
	return 1.0;
	//return 2.0 * x[0];
}

template <typename X>
double my_f_1_d_2(X x) {
	return sin(x[1]);
	//return (x[0] == 0) ? NULL : (2.0 / (x[1] * log(10)));
}

template <typename X>
double my_f_2_d_1(X x) {
	return (-cos(x[0]));
	//return 2.0 * x[0];
}

template <typename X>
double my_f_2_d_2(X x) {
	return 1.0;
	//return  (3.0 * x[0]);
}

template <typename X>
double my_fi_1(X x) {
	return (cos(x[1]) + 3);
	//	return (x[0] == 0)? NULL: (sqrt(2 * log10(x[1]) + 1));
}

template <typename X>
double my_fi_2(X x) {
	return (sin(x[0]) + 3);
	//return (x[0] == 0) ? NULL : ((x[0] / 3) + (3 / x[0]));
}
