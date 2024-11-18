#pragma once
#include"tgaimage.h"
class draw
{
public:
	static void line(float x0, float y0, float x1, float y1, TGAImage &tgaiamge, TGAColor tgacol) {
		bool steep = false; //标记当前斜率的绝对值是否大于1
		if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
			//斜率绝对值>1了，此时将线段端点各自的x,y坐标对调。
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1) {  //x0>x1时，对线段端点坐标进行对调
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		for (float x = x0; x <= x1; x++) {
			float q = (float)(x1 - x0);
			float t = (x - x0) / q;
			int y = y0 * (1. - t) + y1 * t;
			if (steep) {
				//如果线段是斜率大于1的，那么线段上的点原本坐标应该是(y,x)
				tgaiamge.set(y, x, tgacol);
			}
			else {
				tgaiamge.set(x, y, tgacol);
			}
		}
	}

};
