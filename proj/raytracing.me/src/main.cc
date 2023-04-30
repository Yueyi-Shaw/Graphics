#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
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

double normal_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

color ray_normal_sphere_color(const ray &r)
{
    auto t = normal_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color(const ray &r)
{
    // middium part is "lighter" than two ends because y here is normalized with x
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_5(const ray &r, const hittable &world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_7(const ray &r, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    if (world.hit(r, 0, infinity, rec))
    {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color_7(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_9(const ray &r, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    if (world.hit(r, 0, infinity, rec))
    {
        point3 target = rec.p + rec.normal + random_unit_vector();
        return 0.5 * ray_color_9(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_10(const ray &r, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    if (world.hit(r, 0, infinity, rec))
    {
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color_10(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color ray_color_11(const ray &r, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color_11(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

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
5 : Image 5: Resulting render of normals-colored sphere with ground \n \
6 : Image 6: Before and after antialiasing \n \
7 : Image 7: First render of a diffuse sphere \n \
8 : Image 8: Diffuse sphere, with gamma correction \n \
9 : Image 9: Correct rendering of Lambertian spheres \n \
10 : Image 10: Rendering of diffuse spheres with hemispherical scattering \n \
11 : Image 11: Shiny metal \n \
12 : Image 12: Fuzzed metal \n \
13 : Image 13: Glass first \n \
14 : Image 14: Glass sphere that always refracts \n \
15 : Image 15: Glass sphere that sometimes refracts \n \
16 : Image 16: A hollow glass sphere \n \
17 : Image 17: A wide-angle view \n \
18 : Image 18: A distant view \n \
19 : Image 19: Zooming in \n \
20 : Image 20: Spheres with depth-of-field \n \
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
    case 5:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);

        // World
        hittable_list world;
        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                auto u = double(i) / (image_width - 1);
                auto v = double(j) / (image_height - 1);
                ray r(origin, lower_left_corner + u * horizontal + v * vertical);
                color pixel_color = ray_color_5(r, world);
                write_color(std::cout, pixel_color);
            }
        }
        break;
    }
    case 6:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;

        // World
        hittable_list world;
        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_5(r, world);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 7:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_7(r, world, max_depth);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 8:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_7(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 9:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_9(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 10:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_10(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 11:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
        auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 12:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
        auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 13:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<glassfirst>();
        auto material_left = make_shared<glassfirst>();
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 14:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<dielectric_14>(1.5);
        auto material_left = make_shared<dielectric_14>(1.5);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 15:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = make_shared<dielectric_15>(1.5);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 16:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World
        hittable_list world;
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = make_shared<dielectric>(1.5);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera
        camera cam;

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 17:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World

        auto R = cos(pi / 4);
        hittable_list world;

        auto material_left = make_shared<lambertian>(color(0, 0, 1));
        auto material_right = make_shared<lambertian>(color(1, 0, 0));

        world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
        world.add(make_shared<sphere>(point3(R, 0, -1), R, material_right));

        // Camera

        camera cam(90.0, aspect_ratio);

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 18:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World

        hittable_list world;

        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = make_shared<dielectric>(1.5);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        camera_18 cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 19:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World

        hittable_list world;

        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = make_shared<dielectric>(1.5);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        camera_18 cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 20, aspect_ratio);

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    case 20:
    {
        // Image

        const auto aspect_ratio = 16.0 / 9.0;
        const int image_width = 400;
        const int image_height = static_cast<int>(image_width / aspect_ratio);
        const int samples_per_pixel = 100;
        const int max_depth = 50;

        // World

        hittable_list world;

        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = make_shared<dielectric>(1.5);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
        world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // camera
        point3 lookfrom(3, 3, 2);
        point3 lookat(0, 0, -1);
        vec3 vup(0, 1, 0);
        auto dist_to_focus = (lookfrom - lookat).length();
        auto aperture = 2.0;

        dofcamera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

        // Render

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color_11(r, world, max_depth);
                }
                write_color_8(std::cout, pixel_color, samples_per_pixel);
            }
        }
        break;
    }
    }

    std::cerr << "ppm of lesson " << lesson_id << " Done.\n";
}