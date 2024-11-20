#include <iostream>
#include <assert.h>
#include "vector3.h"
#include "octo_tree.h"

int main()
{
    size_t triangle_number = 0;

    std::cin >> triangle_number;
    assert(std::cin.good());

    geometry::triangle_in_node_t triangles_arr = {};

    for (size_t it = 0; it < triangle_number; ++it) {
        double ax = 0, ay = 0, az = 0,
               bx = 0, by = 0, bz = 0,
               cx = 0, cy = 0, cz = 0;

        std::cin >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;
        assert(std::cin.good());

        auto t = geometry::triangle_t(geometry::vector3_t(ax, ay, az), 
                                      geometry::vector3_t(bx, by, bz),
                                      geometry::vector3_t(cx, cy, cz));
            
        triangles_arr.emplace(it, t);
    }

    // std::list<int> answer = {};

    // for(auto x = triangles_arr.begin(); x != triangles_arr.end(); ++x){
    //     auto y = x;
    //     y++;
    //     for(; y != triangles_arr.end(); ++y){
    //         if(x->second.is_intersecting(y->second)){
    //             answer.push_back(x->first);
    //         }
    //     }
    // }

    // // answer.unique();
    // answer.sort();

    // for (int it : answer) {
    //     std::cout << it << " ";
    // }
    
    auto octo_root = geometry::octo_tree_t(triangles_arr);

    octo_root.intersect_octo_tree();

    for (auto it : octo_root.intersect_numbers) {
        std::cout << it << " ";
    }

    std::cout << std::endl;
    return 0;
}
