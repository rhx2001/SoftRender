#include"MathV.hpp"
#include"MathM.hpp"
#include"Utils.hpp"
int main() {
	Vector<int, 2> a({ 1,2 });
	Vector<int, 2> b({ 3,4 });
	Vector<int, 3> c = {1,2,3};
	Matrix<int, 2, 2> m = { {1,2},{3,4} };
	Matrix<int, 2, 2> t = { {1,2},{4,5} };
	Matrix<float, 3, 2> q = { {1,2},{3,4},{5,6} };
	std::cout << Utils::Translate(Vector<float, 3>({ 1,2,3 }))<<" "<<Utils::Rotate(Vector<float, 3>({0,0,0}), 45.0f);
}