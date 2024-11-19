#pragma once
#include "My_Math.h"

class Mesh
{
public:

    std::vector<Vector3f> Vertex;
    std::vector<Vector2f> Texcootd;
    std::vector<Vector3f> Normal;

    struct Face {
        std::vector<int> vertexIndices;
        std::vector<int> textureIndices;
        std::vector<int> normalIndices;
    };

    std::vector<Face> faces;

    void addVertex(float x, float y, float z) {
        Vertex.push_back(Vector3f({ x, y, z }));
    }

    void addTextureCoord(float u, float v) {
        Texcootd.push_back(Vector2f({ u, v }));
    }

    void addNormal(float x, float y, float z) {
        Normal.push_back(Vector3f({ x, y, z }));
    }

    void addFace(const Face& face) {
        faces.push_back(face);
    }

private:

};

