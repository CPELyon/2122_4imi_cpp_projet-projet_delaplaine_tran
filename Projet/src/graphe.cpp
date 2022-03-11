#include "graphe.hpp"

graphe::graphe()
    :dim_x(10),dim_y(10),liste_case()
{}

graphe::graphe(int p_dim_x,int p_dim_y,std::map<std::pair<int,int>,noeud> p_map)
    :dim_x(p_dim_x),dim_y(p_dim_y),liste_case(p_map)
{}

void graphe::afficher()
{
    for (auto& val : liste_case)
    {
        auto coord = val.first;
        int dim_x = std::get<0>(coord);
        int dim_y = std::get<1>(coord);
        std::cout << "Position (" << dim_x << "," << dim_y << ") | Item : " << val.second << '\n';
    }
}

