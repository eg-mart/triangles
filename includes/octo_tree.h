#pragma once

#include <vector>
#include <list>
#include <unordered_map>
#include "triangle.h"

namespace geometry {

using triangle_in_node_t = std::unordered_map<int, triangle_t *>;

class octo_t
{
public:
    octo_t(triangle_in_node_t& triangle_arr);

    std::vector<octo_t> divide_octo();
    bool is_triangle_in_octo(const triangle_t& triangle);
    
private:
    vector3_t a, b, c;

    octo_t(const vector3_t& a, const vector3_t& b, const vector3_t& c);
};

class node_t 
{
public:
    node_t(triangle_in_node_t& triangle_arr);
    ~node_t();

    triangle_in_node_t triangles_arr;
    triangle_in_node_t child_triangles_arr;
    node_t* smaller_nodes[8] = {};

    std::list<int> intersect_in_node(std::list<int>& number_array);

private:
    octo_t octo;
};

class octo_tree_t
{
public:
    node_t *root = nullptr;

    octo_tree_t(triangle_in_node_t& triangle_arr);
    ~octo_tree_t();

    void intersect_octo_tree(std::list<int>& intersect_numbers);
    size_t size();

private:
    size_t size_(node_t *node);
};

}
