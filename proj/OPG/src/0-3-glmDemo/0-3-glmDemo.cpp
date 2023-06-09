#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Tools/DebugConsole.h"

int main()
{
    DebugConsole console;

    glm::mat4 model_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 1, 0));
    glm::mat4 view_matrix = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 projection_matrix = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;

    std::cout << "MVP Matrix: " << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << mvp_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    glm::vec3 v1(1.0f, 0.0f, 0.0f);
    glm::vec3 v2(0.0f, 1.0f, 0.0f);
    glm::vec3 cross_product = glm::cross(v1, v2);
    glm::vec3 normalized = glm::normalize(glm::vec3(2, 0, 0));

    std::cout << "Cross product of v1 and v2: (" << cross_product.x << ", " << cross_product.y << ", " << cross_product.z << ")" << std::endl;
    std::cout << "Normalized vector: (" << normalized.x << ", " << normalized.y << ", " << normalized.z << ")" << std::endl;

    glm::vec3 p1(0.0f, 0.0f, 0.0f);
    glm::vec3 p2(2.0f, 0.0f, 0.0f);
    glm::vec3 p3(0.0f, 2.0f, 0.0f);
    glm::vec3 normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
    float distance = glm::dot(-p1, normal);

    std::cout << "Plane equation: " << normal.x << "x + " << normal.y << "y + " << normal.z << "z + " << distance << " = 0" << std::endl;

    std::cout << "PRESS ENTER TO EXIT" << std::endl;
    std::string userInput;
    while (true)
    {
        //std::getline(std::cin, userInput);

        if (!userInput.empty())
        {
            break;
        }
    }

    return 0;
}