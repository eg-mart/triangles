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

    std::list<geometry::triangle_t> triangle_arr = {t1, t2, t3};  

    auto octo = geometry::octo_t(triangle_arr);                             
    
    std::cout << octo.a << octo.b << octo.c << "\n";

    std::cout << "!!" << std::endl;

    auto octo_root = geometry::octo_tree_t(triangle_arr);

    // auto octo_arr = octo.divide_octo();

    // for(auto octo_it: octo_arr) {
    //     std::cout << octo_it.a << octo_it.b << octo_it.c << std::endl;
    // }

    return 0;
}
