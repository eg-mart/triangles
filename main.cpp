#include <iostream>
#include "vector3.h"
#include "octo_tree.h"

int main()
{
    auto t1 = geometry::triangle_t(geometry::vector3_t(0, 0, 0), 
                                   geometry::vector3_t(1, 0, 0),
                                   geometry::vector3_t(0, 1, 0));

    auto t2 = geometry::triangle_t(geometry::vector3_t(0, 0, 1), 
                                   geometry::vector3_t(1, 1, 1),
                                   geometry::vector3_t(1, 1, -2));

    auto t3 = geometry::triangle_t(geometry::vector3_t(0, 0, 1), 
                                   geometry::vector3_t(1, 1, 1),
                                   geometry::vector3_t(1, 1, 0));

    geometry::triangle_in_node_t triangle_arr = {{1, t1}, {2, t2}, {3, t3}};  

    auto octo = geometry::octo_t(triangle_arr);                             
    
    std::cout << octo.a << octo.b << octo.c << "\n";

    std::cout << "!!";
    std::cout << std::endl;

    auto octo_root = geometry::octo_tree_t(triangle_arr);

    octo_root.intersect_octo_tree();

    for (auto it : octo_root.intersect_numbers) {
        std::cout << it;
    }

    std::cout << std::endl;
    return 0;
}
