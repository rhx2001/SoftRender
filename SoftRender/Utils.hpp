#pragma once
#include"My_Math.hpp"
#include<cmath>
#include<iostream>

class Trans {
public:
	template<typename T>
	static Matrix<T, 4, 4> Translate(const Vector<T, 3>& Pos) {
		Matrix<T, 4, 4> trans(4, 4, T(1));
		trans(0, 3) = Pos[0];
		trans(1, 3) = Pos[1];
		trans(2, 3) = Pos[2];
		return trans;
	}

	template<typename T>
	static Matrix<T, 4, 4> Rotate(const Vector<T,3>& axis, float angle) {
		float x = axis[0], y = axis[1], z = axis[2];
		float a = angle / 180 * MY_PI;
		Matrix4f I(4, 4, 1.0f), N({ { 0.0f,-z,y,0.0f }, { z,0.0f,-x,0.0f }, { -y,x,0.0f,0.0f }, { 0.0f,0.0f,0.0f,1.0f } }), rotation;
		Vector4f n({x,y,z,0});
		rotation = (cos(a) * I +   n.dot(n) * (1.0f - cos(a)) + sin(a));
		std::cout << rotation.dot(N) << "\n"<< n.dot(n) <<"\n";
		rotation = rotation.dot(N);
		rotation(3, 3) = 1.0f;

		return rotation;
	}
};