//This code is the intellectual property of Danila Musatov .
//Contacts danilarumus2000@gmail.com
//This program contains a number of numerical methods for finding the root on the interval.
// Copyright reserved 2021 

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
using v_i = vector<int>;
using v_d = vector<double>;
using EVX = Eigen::VectorXf;
using EMX = Eigen::MatrixXf; 
using V_EMX = vector<Eigen::MatrixXf>;


template <typename T>
double max_delt(const T& x, const T& x_1) {
	double max = -1;
	for (unsigned int i = 0; i < x.size(); ++i) {
		max = (fabs(x[i] - x_1[i]) > max) ? fabs(x[i] - x_1[i]) : max;
	}
	return max;
}

EVX conv_v_e(const v_d& x) {
	EVX e_v_X(x.size());
	for (unsigned int i = 0; i < x.size(); ++i) {
		e_v_X(i) = x[i];
	}
	return e_v_X;
}

v_d conv_e_v(const EVX& x) {
	v_d x_v(x.size());
	for (int i = 0; i < x.size(); ++i) {
		x_v[i]=x[i];
	}
	return x_v;
}

template<typename T>
EMX W_completion(const m_func_x< double(*)(EVX x)>& d_fi, const T& e_v_x) {
	EMX W(e_v_x.size(), e_v_x.size());
	for (int i = 0; i < e_v_x.size(); ++i) {
		for (int j = 0; j < e_v_x.size(); ++j) {
			W(i, j) = d_fi[i][j](e_v_x);
		}
	}
	return W;
}


EVX Fx(const EVX& evx, const v_func_v_x<EVX>& f) {
	EVX FX(f.size());
	for (unsigned int i = 0; i < f.size(); ++i) {
		FX[i] = f[i](evx);
	}
	return FX;
}

v_d converter_e_v(const EVX& x) {
	v_d b_x(x.size());
	for (int i = 0; i < x.size(); i++) b_x[i]=x[i];
	return b_x;
}

template < typename F, typename X>
double max_f_x(const F& f_x, const X& x) {
	double max = -1;
	for (unsigned int i = 0; i < x.size(); ++i) {
		max = (fabs(f_x[i](x)) > max) ? fabs(f_x[i](x)) : max;
	}
	return max;
}

template <typename F, typename X>
void print_disc(const F& f, const X& x) {
	cout << "\n\nx[0] = "<< x[0] << "      x[1] = " << x[1] <<"        f_0(x) = " <<f[0](x) << "        f_1(x) = " << f[1](x) <<"        discrepancy = " << max_f_x<F, X>(f, x) << "\n\n";
	return;
}

v_d simple_iter_s(const v_func_v_x<v_d>& fi, 
				const v_func_v_x<v_d>& f, 
				const v_d& x, 
				const double& eps) {
	v_d x_1, x_2;
	x_1 = x;
	for (unsigned int i = 0; i < fi.size(); i++) x_2.push_back(fi[i](x));
	print_disc<v_func_v_x<v_d>, v_d>(f, x_1);
	while (max_delt<v_d>(x_1, x_2) > eps) {
		x_1 = x_2;
		for (unsigned int i = 0; i < fi.size(); i++)
			x_2[i] = fi[i](x_1);
		print_disc<v_func_v_x<v_d>, v_d>(f, x_2);
	}
	return x_2;
}
// take first interpolation of x as free coef
v_d zeydel_s(const v_func_v_x<v_d>& fi, const v_d& x, const double eps) {
	v_d x_1, x_2;
	x_1 = x;
	for (unsigned int i = 0; i < fi.size(); i++) x_2.push_back(fi[i](x));
	while (max_delt<v_d>(x_1, x_2) > eps) {
		x_1 = x_2;
		for (unsigned int i = 0; i < fi.size(); i++)
			x_2[i] = fi[i](x_2);
	}
	return x_2;
}

v_d Newtonw_s(const m_func_x< double(*)(EVX x)>& d_fi, 
			  const v_func_v_x<EVX>& f, 
			  const v_d& x, const double& eps) {

	EVX e_v_X(x.size());
	EVX e_v_X_1(x.size());
	e_v_X = conv_v_e(x);
	EMX W(x.size(), x.size());
	W = W_completion(d_fi, e_v_X);
	e_v_X_1 = e_v_X - W.inverse() * Fx(e_v_X, f);
	print_disc<v_func_v_x<EVX>, EVX>(f, e_v_X);
	print_disc<v_func_v_x<EVX>, EVX>(f, e_v_X_1);

	while (max_delt<EVX>(e_v_X, e_v_X_1) > eps) {
		e_v_X = e_v_X_1;
		for (unsigned int i = 0; i < f.size(); i++) {
			W = W_completion(d_fi, e_v_X);
			e_v_X_1 = e_v_X - W.inverse() * Fx(e_v_X, f);
			print_disc<v_func_v_x<EVX>, EVX>(f, e_v_X_1);
		}

	}

	return converter_e_v(e_v_X_1);
}

// functions for rotation method Yakobi 


v_i max_v_index(EMX A) {
	v_i v(2);
	double max_v{-1.0};
	int n = A.rows();
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (max_v < fabs(A(i, j))) {
				max_v = fabs(A(i, j));
				v[0] = i;
				v[1] = j;
			}
		}
	}
	return v;
}

EMX zero_EMX(const unsigned int & rows, const unsigned int& columns) {
	EMX M(rows, columns);
	for (unsigned int i = 0; i < rows; ++i)
		for (unsigned int j = 0; j < columns; ++j)
			M(i, j) = 0;
	return M;
}
EMX E_EMX(const unsigned int & size) {
	EMX M(size, size);
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = 0; j < size; ++j)
			M(i, j) = 0;
	for (unsigned int i = 0; i < size; ++i)
		M(i, i) = 1;
	return M;
}

EMX init_U_M(const double & theta, const int & size, v_i cords) {
	EMX U(size, size);
	U = E_EMX(size);
	for (int i = 0; i < cords.size();++i) {
		for (int j = 0; j < cords.size(); ++j) {
			if (i == j){
				U(cords[i],cords[j]) =  cos(theta);
			}
			else {
				U(cords[i], cords[j]) = -sin(theta);
				U(cords[j], cords[i]) =  sin(theta);
			}
		}
	}
	return U;
}

double fi_k(EMX A, v_i cords) {
	return(0.5 * atan(2 * A(cords[0], cords[1]) / ( A(cords[0], cords[0]) - A(cords[1], cords[1]) ) ) );

}

double criteria(EMX& A) {
	double res = 0;
	int n = A.rows();
	for (int i = 1; i < n; ++i) {
		for(int j = 0; j < i; ++j) {
			res += A(i, j) * A(i, j);
		}
	}
	return sqrt(res);
}

V_EMX Jacobi_M(const EMX & Source, const double & eps) {
	EMX A = Source;
	v_i max;
	EMX U;
	int size = Source.rows();
	EMX L=E_EMX(size);
	int counter{ 0 };
	while ( criteria(A) > eps ) {
		max = max_v_index(A);
		U = init_U_M(fi_k(A, max), size, max);
		L = L*U;
		A = U.transpose()*A*U;
		//cout <<"\nL[" << counter++ << "]:\n " << L << "\n";
	}
	V_EMX V{A, L};
	return V;
}
