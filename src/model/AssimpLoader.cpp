#include "AssimpLoader.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ElementModel.h"
#include "ModelRegistry.h"

int indicesCount = 0;

struct Vertex {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

void AssimpLoader::load(const std::string &modelName, const std::string& fileName) {
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_OptimizeMeshes // sloučení malých plošek
                                 | aiProcess_JoinIdenticalVertices // NUTNÉ jinak hodně duplikuje
                                 | aiProcess_Triangulate // prevod vsech ploch na trojuhelniky
                                 | aiProcess_CalcTangentSpace;
    // vypocet tangenty, nutny pro spravne pouziti normalove mapy

    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

    const aiScene* scene = importer.ReadFile(fileName, importOptions);

    if (scene) {
        //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        for (unsigned int i = 0; i < scene->mNumMaterials; i++) //Materials
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);

            aiColor4D d;

            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }

        if(scene->mNumMeshes > 1) {
            throw std::runtime_error("Only single mesh is supported");
        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) //Objects
        {
            aiMesh* mesh = scene->mMeshes[i];

            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

            std::vector<glm::vec3> vertices;
            vertices.resize(mesh->mNumVertices);

            std::vector<glm::vec3> normals;
            normals.resize(mesh->mNumVertices);

            std::vector<glm::vec2> textures;
            textures.resize(mesh->mNumVertices);

            std::vector<glm::vec3> tangents;
            tangents.resize(mesh->mNumVertices);

            for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
                if (mesh->HasPositions()) {
                    vertices[i] = {
                        mesh->mVertices[i].x,
                        mesh->mVertices[i].y,
                        mesh->mVertices[i].z
                    };
                    pVertices[i].Position[0] = mesh->mVertices[i].x;
                    pVertices[i].Position[1] = mesh->mVertices[i].y;
                    pVertices[i].Position[2] = mesh->mVertices[i].z;
                }
                if (mesh->HasNormals()) {
                    normals[i] = {
                        mesh->mNormals[i].x,
                        mesh->mNormals[i].y,
                        mesh->mNormals[i].z
                    };
                    pVertices[i].Normal[0] = mesh->mNormals[i].x;
                    pVertices[i].Normal[1] = mesh->mNormals[i].y;
                    pVertices[i].Normal[2] = mesh->mNormals[i].z;
                }
                if (mesh->HasTextureCoords(0)) {
                    textures[i] = {
                        mesh->mTextureCoords[0][i].x,
                        mesh->mTextureCoords[0][i].y
                    };
                    pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }
                if (mesh->HasTangentsAndBitangents()) {
                    tangents[i] = {
                        mesh->mTangents[i].x,
                        mesh->mTangents[i].y,
                        mesh->mTangents[i].z
                    };
                    pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                    pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                    pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                }
            }

            std::vector<GLushort> elements;
            elements.resize(mesh->mNumFaces * 3);

            unsigned int* pIndices = nullptr;
            if (mesh->HasFaces()) {
                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];

                    elements[i * 3] = mesh->mFaces[i].mIndices[0];
                    elements[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    elements[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            ModelRegistry::get()->registerElementModel(
                modelName,
                elements,
                {
                    ModelAttribute::from(vertices),
                    ModelAttribute::from(normals),
                    ModelAttribute::from(textures),
                    ModelAttribute::from(tangents)
                }
            );

            // glGenVertexArrays(1, &VAO);
            // glGenBuffers(1, &VBO);
            // glGenBuffers(1, &IBO);
            //
            // glBindVertexArray(VAO);
            // glBindBuffer(GL_ARRAY_BUFFER, VBO);
            //
            // glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
            //
            // glEnableVertexAttribArray(0);
            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (0));
            // glEnableVertexAttribArray(1);
            // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (3 * sizeof(GLfloat)));
            // glEnableVertexAttribArray(2);
            // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (6 * sizeof(GLfloat)));
            // //tangenta pro normalovou mapu
            // glEnableVertexAttribArray(3);
            // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (8 * sizeof(GLfloat)));
            //
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
            //
            // glBindBuffer(GL_ARRAY_BUFFER, 0);
            // glBindVertexArray(VAO);

            check_gl_error();
            indicesCount = mesh->mNumFaces * 3;

            delete[] pVertices;
            delete[] pIndices;
        }
    } else {
        printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
    }
    glBindVertexArray(0);
}
