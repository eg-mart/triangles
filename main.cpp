#include <iostream>
#include <assert.h>
#include "vector3.h"
#include "octo_tree.h"

int main()
{
    size_t triangle_number = 0;

    std::cin >> triangle_number;

    geometry::triangle_in_node_t triangles_arr = {};

    for (size_t it = 0; it < triangle_number; ++it) {
        double ax = 0, ay = 0, az = 0,
               bx = 0, by = 0, bz = 0,
               cx = 0, cy = 0, cz = 0;

        std::cin >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;

        auto t = new geometry::triangle_t(geometry::vector3_t(ax, ay, az), 
                                          geometry::vector3_t(bx, by, bz),
                                          geometry::vector3_t(cx, cy, cz));
            
        triangles_arr.emplace(it, t);
    }
    
    auto octo_root = geometry::octo_tree_t(triangles_arr);

    std::list<int> intersect_numbers;
    octo_root.intersect_octo_tree(intersect_numbers);

    for (auto it : intersect_numbers) {
        std::cout << it << " ";
    }

    for (auto it : triangles_arr) {
        delete it.second;
    }

    std::cout << std::endl;
}
