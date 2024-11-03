#include"MathV.hpp"
#include"MathM.hpp"
int main() {
	Vector<int, 2> a({ 1,2 });
	Vector<int, 2> b({ 3,4 });
	Vector<int, 3> c = {1,2,3};
	Matrix<int, 2, 2> m = { {1,2},{3,4} };
	Matrix<int, 2, 2> t = { {1,2},{4,5} };
	std::cout << a<<"\n"<<a-b<<"\n"<<a+b<<"\n"<<a*b*100<<"\n"<<a.dot(b)<<"\n"<<c<<"\n"<<m.dot(t)<<"\n"<<m.dot(a)<<"\n"<<a.dot(m).dot(t);
}