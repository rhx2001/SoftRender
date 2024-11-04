#pragma once
#include"MathV.hpp"
#include"MathM.hpp"
#include<cmath>
class Utils {
public:
	template<typename T>
	static Matrix<T, 4, 4> Transform(const Vector<T, 3>& Pos) {
		Matrix<T, 4, 4> trans(4, 4, 1);
		trans(0, 3) = Pos[0];
		trans(1, 3) = Pos[1];
		trans(2, 3) = Pos[2];
		return trans;
	}

	template<typename T>
	static Matrix<T, 4, 4>Rotate(const Vector<T, 3> degree) {

	}
};