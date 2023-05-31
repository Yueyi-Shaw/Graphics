#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include "Tools/DebugConsole.h"
#include <iostream>

int main(int argc, char **argv)
{
    DebugConsole console;

    // Create an instance of the Importer class
    Assimp::Importer importer;

    const char *pFile = "../../../models\\DragonAttenuation\\glTF-Binary\\DragonAttenuation.glb";

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene *scene = importer.ReadFile(pFile,
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
        return -1;
    }

    // log
    std::cout << "Model has " << scene->mNumMeshes << " meshes." << std::endl;

    aiNode *rootNode = scene->mRootNode;
    std::cout << "Model root node name: " << rootNode->mName.C_Str() << std::endl;
    std::cout << "Model root node has " << rootNode->mNumChildren << " children." << std::endl;

    // log
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[i];

        std::cout << "Mesh " << (i + 1) << " has " << mesh->mNumVertices << " vertices." << std::endl;

        for (unsigned int j = 0; j < mesh->mNumVertices; j++)
        {
            aiVector3D position = mesh->mVertices[j];
            std::cout << "Vertex " << (j + 1) << " position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
        }
    }

    // release
    importer.FreeScene();

    std::cout << "PRESS ENTER TO EXIT" << std::endl;
    std::string userInput;
    while (true)
    {
        std::getline(std::cin, userInput);

        if (!userInput.empty())
        {
            break;
        }
    }

    return 0;
}