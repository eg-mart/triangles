#pragma once

#include <vector>
#include <list>
#include "triangle.h"

namespace geometry {
    class octo_t
    {
    public:
        // std::vector<triangle_t> triangles_inside = {};
    
        octo_t(std::list<triangle_t>& triangle_arr);
        octo_t(const vector3_t& a, const vector3_t& b, const vector3_t& c);

        std::vector<octo_t> divide_octo();
        bool  is_triangle_in_octo(const triangle_t& triangle);

        vector3_t a, b, c;
    };

    class node_t 
    {
    public:
        octo_t octo;
        std::list<triangle_t> triangles_arr;
        node_t* smaller_nodes[8] = {};


        node_t(std::list<triangle_t>& triangle_arr);
        ~node_t();
    };

    class octo_tree_t
    {
    public:
        node_t *root = nullptr;

        octo_tree_t(std::list<triangle_t>& triangle_arr);
        ~octo_tree_t();
    };
    
    
}