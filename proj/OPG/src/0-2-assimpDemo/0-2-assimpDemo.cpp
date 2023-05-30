#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <iostream>

int main(int argc, char **argv)
{
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

    // If the import failed, report it
    if (nullptr == scene)
    {
        std::cout << importer.GetErrorString() << std::endl;
        return false;
    }

    // Now we can access the file's contents.
}