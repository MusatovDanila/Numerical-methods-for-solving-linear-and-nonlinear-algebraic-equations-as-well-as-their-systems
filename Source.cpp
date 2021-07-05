//This code is the intellectual property of Danila Musatov .
//Contacts danilarumus2000@gmail.com
//This program contains a number of numerical methods for finding the root on the interval.
// Copyright reserved 2021 

#include<iostream>
#include<vector>	
#include<cmath>
#include"functions.h"
#include"polynoms.h"

int main() {
	double eps = 0.001;
	/*
	v_func_v_x<v_d> my_sys_f{ &my_polynom_1<v_d> ,&my_polynom_2<v_d> };
	v_func_v_x<v_d> my_sys_fi{ & my_fi_1<v_d>, & my_fi_2<v_d>};
	m_func_x<double(*)(EVX)> d_f{ {my_f_1_d_1<EVX>, my_f_1_d_2<EVX>}, {my_f_2_d_1<EVX>, my_f_2_d_2<EVX> }};
	//std::cin >> eps;
	v_d x_0{ 3, 3 };
	v_d x,x_1;
	x = simple_iter_s(my_sys_fi, my_sys_f, x_0, eps);
	v_func_v_x<EVX> my_sys_e_f{ &my_polynom_1<EVX> ,&my_polynom_2<EVX> };
	std::cout << "\n\n Newton\n\n";
	x_1 = Newtonw_s(d_f, my_sys_e_f, x_0, eps);
	*/

	// Lab ¹6 rotation method Yakobi
	EMX A(3,3);
	/*
	A(0, 0) =  5; A(0, 1) = -4; A(0, 2) =  7;
	A(1, 0) = -4; A(1, 1) = -3; A(1, 2) =  4;
	A(2, 0) =  7; A(2, 1) =  4; A(2, 2) = -1;
	*/
	
	A(0, 0) = -8; A(0, 1) =  5; A(0, 2) = -7;
	A(1, 0) =  5; A(1, 1) =  1; A(1, 2) =  4;
	A(2, 0) = -7; A(2, 1) =  4; A(2, 2) =  4;
	
	V_EMX My = Jacobi_M(A,eps);
	cout << "\n\n Start Matrix:\n\n" << A << "\n\n Lambda Matrix\n\n" << My[0] << "\n\n"; 
	cout << A.eigenvalues(); 
	
	//
	cout << "\n\n First eigen vector \n\n" << My[1].row(0) 
		 <<	"\n\n Second eigen vector\n\n" << My[1].row(1) 
		 << "\n\n Third eigen vector\n\n" << My[1].row(2) << "\n\n";
	

	cout << "\n\nAv[0]:\n" << A * My[1].col(0) << "\n\nLv[0]:\n";
	cout << My[0](0, 0) * My[1].col(0)<< "\n\n";
	cout << "\n\nAv[1]:\n" << A * My[1].col(1) << "\n\nLv[1]:\n";
	cout << My[0](1, 1) * My[1].col(1) << "\n\n";
	cout << "\n\nAv[2]:\n" << A * My[1].col(2) << "\n\nLv[2]:\n";
	cout << My[0](2, 2) * My[1].col(2) << "\n\n";

	//cout << A * My[1] << "\n\n" << My[0] << "\n\n" ;
	
	
	system("pause");
	return 0;
}