#include"Utils.hpp"
int main() {
	Vector<int, 2> a({ 1,2 });
	Vector<int, 2> b({ 3,4 });
	Vector<int, 3> c = {1,2,3};
	Matrix<int, 2, 2> m = { {1,2},{3,4} };
	Matrix<int, 2, 2> t = { {1,2},{4,5} };
	Matrix3f q = { {1,2,3},{3,4,3},{5,6,4} };
	std::cout << Trans::Translate(Vector<float, 3>({ 1,2,3 }))<<" "<<Trans::Rotate(Vector<float, 3>({1,0,1}), 45.0f);
	Matrix<int, 2, 2> z = m.dot(t);
	//z(1, 1) = 3;
	//std::cout << z;
}