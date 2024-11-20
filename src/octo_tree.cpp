#include <utility>
#include <iostream>
#include <limits>
#include <list>
#include "octo_tree.h"
#include "common.h"


namespace geometry {
    octo_t::octo_t (triangle_in_node_t& triangle_arr) {
        double inf = std::numeric_limits<double>::infinity();
        
        std::pair<double, double> extr[3] = {{-inf, inf}, {-inf, inf}, {-inf, inf}}; 

        for (auto triangle: triangle_arr) {
            for (size_t it_axes = 0; it_axes < 3; ++it_axes) {
                for (size_t it_points = 0; it_points < 3; ++it_points) {
                    if (gt_double(triangle.second.p[it_points].x[it_axes], extr[it_axes].first)) {
                        extr[it_axes].first = triangle.second.p[it_points].x[it_axes]; 
                    }
                    if (lt_double(triangle.second.p[it_points].x[it_axes], extr[it_axes].second)) {
                        extr[it_axes].second = triangle.second.p[it_points].x[it_axes]; 
                    }
                }
            }
        }
        
        // for each coordinate (0, 1, 2): first is biggest, second is smallest between all points 

        a = vector3_t(extr[0].first, extr[1].first, extr[2].first);
        b = vector3_t(extr[0].first, extr[1].second, extr[2].first);
        c = vector3_t(extr[0].second, extr[1].first, extr[2].second);
    }

    octo_t::octo_t (const vector3_t& a, const vector3_t& b, const vector3_t& c) : a(a), b(b), c(c)
    {}

    std::vector<octo_t> octo_t::divide_octo () {
        vector3_t mid_ab = 0.5 * (a + b), 
                  mid_ac = 0.5 * (a + c),
                  mid_bc = 0.5 * (b + c);

        vector3_t mid_right_plane  = vector3_t(a.x[0]     , mid_ab.x[1], mid_ac.x[2]),
                  mid_left_plane   = vector3_t(c.x[0]     , mid_ab.x[1], mid_ac.x[2]),
                  mid_bottom_plane = vector3_t(mid_ac.x[0], mid_ab.x[1], c.x[2]     ),
                  mid_top_plane    = vector3_t(mid_ac.x[0], mid_ab.x[1], a.x[2]     ),
                  center           = vector3_t(mid_ac.x[0], mid_ab.x[1], mid_bc.x[2]),
                  mid_back_plane   = vector3_t(mid_ac.x[0], b.x[1]     , mid_ac.x[2]);

        vector3_t mid_a_bottom = vector3_t(a.x[0]     , a.x[1]     , mid_ac.x[2]),
                  mid_a_left   = vector3_t(mid_ac.x[0], mid_ac.x[1], a.x[2]     ),
                  mid_b_bottom = vector3_t(b.x[0]     , b.x[1]     , mid_bc.x[2]),
                  mid_b_left   = vector3_t(mid_ac.x[0], b.x[1]     , b.x[2]     ),
                  mid_c_right  = vector3_t(mid_ac.x[0], mid_ac.x[1], c.x[2]     ),
                  mid_c_top    = vector3_t(c.x[0]     , c.x[1]     , mid_ac.x[2]),
                  mid_c_back   = vector3_t(c.x[0]     , mid_bc.x[1], c.x[2]     );

        octo_t small_octo_1 = {a              , mid_ab         , mid_ac          },
               small_octo_2 = {mid_ab         , b              , center          },
               small_octo_3 = {mid_a_bottom   , mid_right_plane, mid_c_right     },
               small_octo_4 = {mid_right_plane, mid_b_bottom   , mid_bottom_plane},
               small_octo_5 = {mid_a_left     , mid_top_plane  , mid_c_top       },
               small_octo_6 = {mid_top_plane  , mid_b_left     , mid_left_plane  },
               small_octo_7 = {mid_ac         , center         , c               },
               small_octo_8 = {center         , mid_back_plane , mid_c_back      };

        std::vector<octo_t> octo_arr = {small_octo_1, 
                                        small_octo_2, 
                                        small_octo_3, 
                                        small_octo_4, 
                                        small_octo_5, 
                                        small_octo_6, 
                                        small_octo_7, 
                                        small_octo_8};

        return octo_arr;
    }  

    bool octo_t::is_triangle_in_octo(const triangle_t& triangle) {
        for (size_t it_points = 0; it_points < 3; ++it_points) {
            if (gt_double(triangle.p[it_points].x[0], a.x[0]) || 
                gt_double(triangle.p[it_points].x[1], a.x[1]) || 
                gt_double(triangle.p[it_points].x[2], a.x[2]) || 
                lt_double(triangle.p[it_points].x[0], c.x[0]) || 
                lt_double(triangle.p[it_points].x[1], b.x[1]) || 
                lt_double(triangle.p[it_points].x[2], c.x[2])) 
            {
                return false;
            }
        }
        return true;
    }

    node_t::node_t(triangle_in_node_t& triangle_arr) 
    : triangles_arr(triangle_arr), octo(triangle_arr)
    {
        auto smaller_octo = this->octo.divide_octo();

        triangle_in_node_t smaller_triangle_arr[8] = {};


        for (auto it_tr = triangle_arr.begin(); it_tr != triangle_arr.end(); ++it_tr) {
            for (int it = 0; it < 8; ++it) {
                if (smaller_octo[it].is_triangle_in_octo(it_tr->second)){
                    this->child_triangles_arr.emplace(*it_tr);
                    // smaller_triangle_arr[it].emplace(smaller_triangle_arr[it].end(), triangle_arr, it_tr);
                    smaller_triangle_arr[it].insert(triangle_arr.extract(it_tr));
                    break;
                }
            }
        }

        for (int it = 0; it < 8; ++it) {
            if (smaller_triangle_arr[it].size() > 2) {
                smaller_nodes[it] = new node_t(smaller_triangle_arr[it]);
            } else {
                smaller_nodes[it] = nullptr;
            }
        }
    }

    std::list<int> node_t::intersect_in_node(std::list<int>& number_array) {
        auto triangles_in_node = this->triangles_arr;

        std::list<int> results = {};

        int i = 0;
        for (auto triangle_1 : triangles_in_node)
        {
            ++i;
            int j = 0;
            for (auto triangle_2 : triangles_in_node)
            {
                ++j;
                if (i != j && triangle_1.second.is_intersecting(triangle_2.second))
                {
                    // std::cout << i << " is intersecting with " << j << "\n";
                    number_array.push_back(triangle_1.first);
                    number_array.push_back(triangle_2.first);
                    // results.emplace_back(i);
                }
            }
            for (auto triangle_3 : this->child_triangles_arr)
            {
                ++j;
                if (i != j && triangle_1.second.is_intersecting(triangle_3.second))
                {
                    // std::cout << i << " is intersecting with " << j << "\n";
                    number_array.push_back(triangle_1.first);
                    number_array.push_back(triangle_3.first);
                    // results.emplace_back(i);
                }
            }
        }

        for (int i = 0; i < 8; ++i) {
            if (this->smaller_nodes[i] != nullptr) {
                this->smaller_nodes[i]->intersect_in_node(number_array);
            }
        }
        
        return results;
    }

    node_t::~node_t() {
        for (int it = 0; it < 8; ++it) {
            delete smaller_nodes[it];
        }
    }

    octo_tree_t::octo_tree_t(triangle_in_node_t& triangle_arr) {
        root = new node_t(triangle_arr);
    }

    octo_tree_t::~octo_tree_t() {
        delete root;
    }

    void octo_tree_t::intersect_octo_tree() {

        this->root->intersect_in_node(this->intersect_numbers);

        for (int i = 0; i < 8; ++i) {
            if (this->root->smaller_nodes[i] != nullptr) {
                this->root->smaller_nodes[i]->intersect_in_node(this->intersect_numbers);
            }
        }

        this->intersect_numbers.sort();
        this->intersect_numbers.unique();
    }
}