#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

bool pure_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

color ray_pure_sphere_color(const ray &r)
{
    if (pure_sphere(point3(0, 0, -1), 0.5, r))
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

double normal_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}

color ray_normal_sphere_color(const ray& r) {
    auto t = normal_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

color ray_color(const ray &r)
{
    // middium part is "lighter" than two ends because y here is normalized with x
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char **argv)
{
    // handle argvs
    int lesson_id = 0;
    if (argc >= 2)
    {
        std::cerr << "got lesson arguments:" << atoi(argv[1]) << std::endl;
        lesson_id = atoi(argv[1]);
        if (lesson_id == 0)
        {
            std::cerr << "parse lesson number: \n \
1 : Image 1: First PPM image \n \
2 : Image 2: A blue-to-white gradient depending on ray Y coordinate \n \
3 : Image 3: Image 3: A simple red sphere \n \
4 : Image 4: A sphere colored according to its normal vectors \n \
.ppm will be generate in ./img directory."
                      << std::endl;
        }
    }

    // print image of lesson by param provided by commandline
    switch (lesson_id)
    {
    case 0:
        break;
    case 1:
    {
        // Image
        const int image_width = 256;
        const int image_height = 256;

        // Render
        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";
        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
                write_color(std::cout, pixel_color);
            }
        }
        break;
    }
    case 2:
    {
        // Image
        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);

        // Camera

        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        auto origin = point3(0, 0, 0);
        auto horizontal = vec3(viewport_width, 0, 0);
        auto vertical = vec3(0, viewport_height, 0);
        auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

        // Render

        std::cout << "P3\n"
                  << image_width << " " << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                auto u = double(i) / (image_width - 1);
                auto v = double(j) / (image_height - 1);
                ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
                color pixel_color = ray_color(r);
                write_color(std::cout, pixel_color);
            }
        }
        break;
    }
    case 3:
    {
        // Image
        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);

        // Camera

        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        auto origin = point3(0, 0, 0);
        auto horizontal = vec3(viewport_width, 0, 0);
        auto vertical = vec3(0, viewport_height, 0);
        auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

        // Render

        std::cout << "P3\n"
                  << image_width << " " << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                auto u = double(i) / (image_width - 1);
                auto v = double(j) / (image_height - 1);
                ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
                color pixel_color = ray_pure_sphere_color(r);
                write_color(std::cout, pixel_color);
            }
        }
        break;
    }
    case 4:
    {
        // Image
        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);

        // Camera

        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        auto origin = point3(0, 0, 0);
        auto horizontal = vec3(viewport_width, 0, 0);
        auto vertical = vec3(0, viewport_height, 0);
        auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

        // Render

        std::cout << "P3\n"
                  << image_width << " " << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                auto u = double(i) / (image_width - 1);
                auto v = double(j) / (image_height - 1);
                ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
                color pixel_color = ray_normal_sphere_color(r);
                write_color(std::cout, pixel_color);
            }
        }
        break;
    }
    }

    std::cerr << "ppm of lesson " << lesson_id << " Done.\n";
}