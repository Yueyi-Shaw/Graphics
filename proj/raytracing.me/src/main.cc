#include <iostream>
#include "vec3.h"
#include "color.h"

int main(int argc, char** argv)
 {
    // output argvs
    std::cerr << "got " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cerr << argv[i] << std::endl;
    }
    color vector(0,1,0);
    std::cerr << "vector " << vector[0] << vector[1] << vector[2] << std::endl;
    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}