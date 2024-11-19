#pragma once
#include "mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Model {
public:
    Model() = default;

    bool loadOBJ(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << path << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "v") {
                float x, y, z;
                iss >> x >> y >> z;
                mesh.addVertex(x, y, z);
            }
            else if (token == "vt") {
                float u, v;
                iss >> u >> v;
                mesh.addTextureCoord(u, v);
            }
            else if (token == "vn") {
                float x, y, z;
                iss >> x >> y >> z;
                mesh.addNormal(x, y, z);
            }
            else if (token == "f") {
                Mesh::Face face;
                std::string vertex;

                // 处理面的每个顶点
                while (iss >> vertex) {
                    std::istringstream vertexStream(vertex);
                    std::string indexStr;
                    std::vector<int> indices;

                    // 分割顶点/纹理/法线索引
                    while (std::getline(vertexStream, indexStr, '/')) {
                        if (indexStr.empty()) {
                            indices.push_back(0);
                        }
                        else {
                            indices.push_back(std::stoi(indexStr));
                        }
                    }

                    // OBJ文件索引从1开始，需要减1
                    face.vertexIndices.push_back(indices[0] - 1);
                    if (indices.size() > 1) {
                        face.textureIndices.push_back(indices[1] - 1);
                    }
                    if (indices.size() > 2) {
                        face.normalIndices.push_back(indices[2] - 1);
                    }
                }
                mesh.addFace(face);
            }
            // 忽略其他类型的行（如注释等）
        }

        file.close();
        return true;
    }

    const Mesh& getMesh() const {
        return mesh;
    }

private:
    Mesh mesh;
};