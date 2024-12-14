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
	static void triangle(Vector2i t0, Vector2i t1, Vector2i t2, TGAImage& image, TGAColor color) {
		if (t0.y == t1.y && t0.y == t2.y) return;
		//根据y的大小对坐标进行排序
		if (t0.y > t1.y) std::swap(t0, t1);
		if (t0.y > t2.y) std::swap(t0, t2);
		if (t1.y > t2.y) std::swap(t1, t2);
		int max_height = (t2.y - t0.y);
		int second_half = t2.y - t1.y;
		for (int i = t0.y; i < t2.y; i++) {
			int alpha = float(i)/max_height;
			int beta = i < t1.y ? float(i) / t1.y : float((i - t1.y)) / float(t2.y-t1.y);
			Vector2i A = t0 + (t2 - t0) * alpha;
			Vector2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
		}
	}

};
