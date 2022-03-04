#include <iostream>
#include <map>
#include <utility>

struct noeud
{
    bool acces;
    int item;

};

struct graphe
{
    int dim_x;
    int dim_y;
    std::map<std::pair<int,int> , noeud> liste_case;

    graphe()
        :dim_x(10),dim_y(10),liste_case()
    {}

    graphe(int p_dim_x,int p_dim_y,std::map<std::pair<int,int>,noeud> p_map)
        :dim_x(p_dim_x),dim_y(p_dim_y),liste_case(p_map)
    {}
};

int main()
{

    return 0;
}
