#include <iostream>
#include <assert.h>
#include <chrono>
#include "vector3.h"
#include "octo_tree.h"

int main()
{
    size_t triangle_number = 0;

    auto start_init = std::chrono::high_resolution_clock::now();

    std::cin >> triangle_number;
    assert(std::cin.good());

    geometry::triangle_in_node_t triangles_arr = {};

    for (size_t it = 0; it < triangle_number; ++it) {
        double ax = 0, ay = 0, az = 0,
               bx = 0, by = 0, bz = 0,
               cx = 0, cy = 0, cz = 0;

        std::cin >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;
        assert(std::cin.good());

        auto t = new geometry::triangle_t(geometry::vector3_t(ax, ay, az), 
                                          geometry::vector3_t(bx, by, bz),
                                          geometry::vector3_t(cx, cy, cz));
            
        triangles_arr.emplace(it, t);
    }

    auto stop_init = std::chrono::high_resolution_clock::now();

    auto start_dumb = std::chrono::high_resolution_clock::now();

    std::list<int> answer = {};

    for (auto x = triangles_arr.begin(), 
              t_end = triangles_arr.end(); x != t_end; ++x) {
        auto y = x;
        y++;
        for (; y != t_end; ++y) {
            if (x->second->is_intersecting(*y->second)) {
                answer.push_back(x->first);
                answer.push_back(y->first);
            }
        }
    }

    answer.sort();

    for (int it : answer) {
        std::cout << it << " ";
    }

    std::cout << "\n";

    auto stop_dumb = std::chrono::high_resolution_clock::now();

    auto start_octo = std::chrono::high_resolution_clock::now();
    
    auto octo_root = geometry::octo_tree_t(triangles_arr);

    std::list<int> intersect_numbers;
    octo_root.intersect_octo_tree(intersect_numbers);

    auto stop_octo = std::chrono::high_resolution_clock::now();

    auto duration_init = std::chrono::duration_cast<std::chrono::milliseconds>(stop_init - start_init);
    auto duration_dumb = std::chrono::duration_cast<std::chrono::milliseconds>(stop_dumb - start_dumb);
    auto duration_octo = std::chrono::duration_cast<std::chrono::milliseconds>(stop_octo - start_octo);

    std::cout << "Time taken by init: " << duration_init.count() << " miliseconds; \n" << std::endl;
    std::cout << "Time taken by dumb: " << duration_dumb.count() << " miliseconds; \n" << std::endl;
    std::cout << "Time taken by octo: " << duration_octo.count() << " miliseconds; \n" << std::endl;

    for (auto it : intersect_numbers) {
        std::cout << it << " ";
    }

    for (auto it : triangles_arr) {
        delete it.second;
    }

    std::cout << std::endl;
    return 0;
}
