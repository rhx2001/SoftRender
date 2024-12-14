#include"Transformer.h"
#include "tgaimage.h"
#include "draw.h"
#include "model.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 600;
int main() {
	Vector<int, 2> a({ 1,2 });
	Vector<int, 2> b({ 3,4 });
	Vector<int, 3> c = {1,2,3};
	Matrix<int, 2, 2> m = { {1,2},{3,4} };
	Matrix<int, 2, 2> t = { {1,2},{4,5} };
	Matrix3f q = { {1,2,3},{3,4,3},{5,6,4} };
	//Vector<int, 2> zzz = 3 + b ;
	std::cout << Trans::Translate(Vector<float, 3>({ 1,2,3 }))<<" "<<Trans::Rotate(Vector<float, 3>({1,0,1}), 45.0f)<<"\n"<<q.inverse()<<"\n";

	Matrix<int, 2, 2> z = m.dot(t);
	TGAImage image(width, height, TGAImage::RGB);
	draw::line(0.f, 20.f, 0.f, 40.f, image, white);
	//image.flip_vertically();
	//image.write_tga_file("output.tga");
	Model model;
	model.loadOBJ("african_head.obj");
	Mesh meshs = model.getMesh();
	for (int i = 0; i < meshs.faces.size(); i++) {
		Mesh::Face face = meshs.faces[i];
		for (int j = 0; j < 3; j++) {
			for (int j = 0; j < 3; j++) {
				Vector3f v0 = meshs.Vertex[face.vertexIndices[j]];
				Vector3f v1 = meshs.Vertex[face.vertexIndices[(j + 1) % 3]];
				//std::cout <<v0<<" " << v0.x << " " << v0.x + 1. << "\n";
				int x0 = (v0.x + 1.) * width / 2.;
				int y0 = (v0.y + 1.) * height / 2.;
				int x1 = (v1.x + 1.) * width / 2.;
				int y1 = (v1.y + 1.) * height / 2.;
				draw::line(x0, y0, x1, y1, image, white);
			}
		}
	}
	image.flip_vertically();
	image.write_tga_file("output.tga");
	std::cout << a << "\n";
	a.x = 10;
	std::cout << a << "\n";
	//z(1, 1) = 3;
	//std::cout << z;

}