#include"Transformer.h"
#include "tgaimage.h"
#include "draw.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
int main() {
	Vector<int, 2> a({ 1,2 });
	Vector<int, 2> b({ 3,4 });
	Vector<int, 3> c = {1,2,3};
	Matrix<int, 2, 2> m = { {1,2},{3,4} };
	Matrix<int, 2, 2> t = { {1,2},{4,5} };
	Matrix3f q = { {1,2,3},{3,4,3},{5,6,4} };
	std::cout << Trans::Translate(Vector<float, 3>({ 1,2,3 }))<<" "<<Trans::Rotate(Vector<float, 3>({1,0,1}), 45.0f)<<"\n"<<q.inverse();
	Matrix<int, 2, 2> z = m.dot(t);
	TGAImage image(100, 100, TGAImage::RGB);
	draw::line(0.f, 20.f, 0.f, 40.f, image, white);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	//z(1, 1) = 3;
	//std::cout << z;

}