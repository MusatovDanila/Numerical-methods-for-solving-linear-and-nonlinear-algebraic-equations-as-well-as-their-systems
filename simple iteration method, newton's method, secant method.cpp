#include<iostream>
#include<cmath>
#include<vector>

//This code is the intellectual property of Danila Musatov .
//Contacts danilarumus2000@gmail.com
//This program contains a number of numerical methods for finding the root on the interval.
// Copyright reserved 2021 

typedef double(*function)(double);
typedef double(*function_1)(double, function, function);

double my_polynom(double x) {
	return (3*sqrt(x+1) - exp(x) - 0.5);
}
/*
double my_polynom(double x) {
	return (pow(x, 6) - 5 * x - 2);
}
*/
double s_polynom(double x) {
	return (exp(x)  - 2 * x - 2);
}

double fi_my_polynom(double x) {
	return (log(3*sqrt(x+1)-0.5));
}

/*
double fi_my_polynom(double x) {
	return ((pow(x, 6) - 2) / 5);
}
*/

double fi_2_my_polynom(double x) {
	return pow((5*x+2), 1/6.0) ;
}

double dev_fi_2_my_polynom(double x) {
	return (5/( 6*pow((5*x+2), (5/6.0))) );
}

double dev_fi_my_polynom(double x) {
	return (3/ (sqrt(x + 1)*(6*sqrt(x + 1) - 1)));
}

/*
double dev_fi_my_polynom(double x) {
	return ((6*pow(x, 5)) / 5);
}
*/
double fi_n_polynom(double x , function f, function df) {
	return(x - (f(x)/df(x)));
}

double derivative_my_polynom(double x) {
	return (6*pow(x, 5) - 5);
}

double s_derivative_my_polynom(double x) {
	return (30 * pow(x, 4));
}

double fi_secant(double x_0, double x_1, function f) {
	return (x_1-f(x_1)*(x_1-x_0)/ (f(x_1) - f(x_0)));
	//return ((f(x_1)*x_0-x_1*(f(x_0)))/(f(x_1)-f(x_0)));
}

bool check_exist_root(double f_a, double f_b) {
	if (f_a*f_b > 0) 
		return 0;
	return 1;
}

double m_half_division(const double& a, const double& b, const double& eps, function f , const double & proffer, double c_iter = 0) {
	double value_f_l = f(a);
	double value_f_r = f(b);
	double c_k = 0;
	if (check_exist_root(value_f_l, value_f_r)) {
		c_k = (((b + a) / 2));
		std::cout << "iter = " << c_iter << "     l = " << a << "       r = " << b <<  "        x = " << c_k << "      f(x)=" << f(c_k) << "      |x-x*| = " << fabs(c_k - proffer) << std::endl << std::endl;
		if (fabs(value_f_l - value_f_r) < eps){
			return ((b + a) / 2);
		}
		
		if (check_exist_root(value_f_l,f(c_k)))
			return m_half_division(a, c_k, eps, f , proffer ,++c_iter);

		if (check_exist_root(f(c_k), value_f_r))
			return m_half_division(c_k, b, eps, f, proffer, ++c_iter);

	}
	return NULL;

}

double m_simple_iteration(const double& x_0, const double& eps, function f, const double & proffer, function f_1) {
	double x = x_0;
	int q_iter = 0;
	do{
		x = f(x);
		std::cout << "iter = " << q_iter++ << "      x = " << x << "      f(x)=" << f_1(x) <<"      |x-x*| = " << fabs(x - proffer) << std::endl << std::endl;
	}while (fabs(x - f(x)) > eps);
	return x;
}

double m_newton(const double& x_0, const double& eps, function_1 fi, function f, function df, const double & proffer) {
	double x = x_0;
	int q_iter = 0;
	while (fabs(x - fi(x,f,df)) > eps) {
		x = fi(x, f, df);
		std::cout << "iter = " << q_iter++ << "      x = " << x << "      f(x)=" << f(x) << "      |x-x*| = " << fabs(x - proffer) << std::endl << std::endl;
	}
	x = fi(x, f, df);
	std::cout << "iter = " << q_iter++ << "      x = " << x << "      f(x)=" << f(x) <<"      |x-x*| = " << fabs(x - proffer) << std::endl << std::endl;
	return x;
}

double m_secant(const double& a, const double& b, const double& eps, function f, const double & proffer) {
	double x_0 = a;
	double x_1 = b;
	int q_iter = 0;
	double helper;
	do{
		helper = fi_secant(x_0, x_1, f);
		x_0 = x_1;
		x_1 = helper;
		std::cout << "iter = " << q_iter++ << "      x = " << x_1 << "      f(x)=" << f(x_1) << "      |x-x*| = " << fabs(x_1 - proffer) << std::endl << std::endl;
	} while (fabs(fi_secant(x_0, x_1, f)) > eps);
	//while (fabs(x_0 - x_1) > eps);
	return x_1;
}

int main() {
	double a= -1, b=0, c=1, d = 2;
	//std::cout << "enter end of interval (a,b)";
	//std::cin >> a >> b;
	//std::cout << "enter end of interval (c,d)";
	//std::cin >> c >> d;
	/*
	double x_0=(-1.0/rand()),x_1=(rand()%int(d) +c);
	std::cout << "half division" << std::endl << std::endl;
	m_half_division(a, b, 0.01, my_polynom, -0.39919);
	std::cout << std::endl << std::endl;
	double n = m_half_division(c, d, 0.01, my_polynom, 1.44868);
	std::cout<< my_polynom(n);
	std::cout << std::endl << std::endl;
	*/
	double x_0 = 1.2;
	std::cout << "simple iteration" << std::endl << std::endl;
	std::cout << dev_fi_my_polynom(x_0) << std::endl << std::endl;
	if (dev_fi_my_polynom(x_0) < 1) {
		std::cout << "fi`(x) < 1, all good let`s start" << std::endl << std::endl;
		m_simple_iteration(x_0, 0.0001, fi_my_polynom, 1.42933,my_polynom);
	}
	std::cout << std::endl << std::endl;
	/*
	//m_simple_iteration(1.5, 0.01, fi_my_polynom, -0.39919);
	std::cout << dev_fi_2_my_polynom(x_1) << std::endl << std::endl;
	if (dev_fi_2_my_polynom(x_1) < 1) {
		std::cout << "fi`(x) < 1, all good let`s start" << std::endl << std::endl;
		m_simple_iteration(x_1, 0.0001, fi_2_my_polynom, 1.44868,my_polynom);
	}
	std::cout << std::endl << std::endl;
	std::cout << "newton" << std::endl << std::endl;
	m_newton(x_0, 0.01, fi_n_polynom, my_polynom ,derivative_my_polynom, -0.39919);
	std::cout << std::endl << std::endl;
	m_newton(x_1, 0.01, fi_n_polynom, my_polynom, derivative_my_polynom, 1.44868);
	std::cout << std::endl << std::endl;
	std::cout << "secant" << std::endl << std::endl;
	m_secant(-0.5, 0, 0.01, my_polynom, -0.39919);
	std::cout << std::endl << std::endl;
	m_secant(1.2, 1.7, 0.01, my_polynom, 1.44868); 
	std::cout << std::endl << std::endl;
	//m_secant(-100, 0, 0.01, s_polynom, -0.39919);
	*/
	system("pause");
	return 0;
}