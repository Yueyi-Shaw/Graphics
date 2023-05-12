#ifndef __PRINT_PPM_H__
#define __PRINT_PPM_H__
#include <iostream>
#include <fstream>
#include <string>

void output_image_by_stream(unsigned char *ptr, int DIM)
{
    std::cout << "P3\n"
              << DIM << ' ' << DIM << "\n255\n";

    for (int y = 0; y < DIM; y++)
    {
        for (int x = 0; x < DIM; x++)
        {
            int offset = x + y * DIM;

            auto r = ptr[offset * 4 + 0];
            auto g = ptr[offset * 4 + 1];
            auto b = ptr[offset * 4 + 2];

            // Write the translated [0,255] value of each color component.
            std::cout << static_cast<int>(r) << ' '
                      << static_cast<int>(g) << ' '
                      << static_cast<int>(b) << '\n';
        }
    }
}

void write_image_to_file(unsigned char *ptr, int DIM, std::string path)
{
    std::ofstream fp;
    fp.open(path, std::ios_base::out | std::ios_base::trunc);
    if (!fp)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    fp << "P3\n"
       << DIM << ' ' << DIM << "\n255\n";
    for (int y = 0; y < DIM; y++)
    {
        for (int x = 0; x < DIM; x++)
        {
            int offset = x + y * DIM;

            auto r = ptr[offset * 4 + 0];
            auto g = ptr[offset * 4 + 1];
            auto b = ptr[offset * 4 + 2];

            // Write the translated [0,255] value of each color component.
            fp << static_cast<int>(r) << ' '
               << static_cast<int>(g) << ' '
               << static_cast<int>(b) << '\n';
        }
    }

    fp.close(); // Close the file
    std::cout << "Success. File is written to " + path << std::endl;
}

#endif __PRINT_PPM_H__