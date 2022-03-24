#include "graphe.hpp"

graphe::graphe()
    :dim_x(10),dim_y(10),liste_case(),Yugo(perso())
{}

graphe::graphe(int p_dim_x,int p_dim_y,std::map<std::pair<int,int>,noeud> p_map)
    :dim_x(p_dim_x),dim_y(p_dim_y),liste_case(p_map),Yugo(perso())
{}

void graphe::afficher()
{
    for (auto& val : liste_case)
    {
        auto coord = val.first;
        int dim_x = std::get<0>(coord);
        int dim_y = std::get<1>(coord);
        std::cout << "Position (" << dim_x << "," << dim_y << ") | " << val.second << '\n';
    }
}

int graphe::get_nb_mur()
{
    int ret = 0;
    for (auto val : liste_case)
    {
        if (!std::get<1>(val).acces)
        {
            ret += 1;
        }
    }
    return ret;
}

void graphe::generate_wall()
{
    for (int i = 0; i < dim_x; i++)
    {
        for (int j = 0; j < dim_y; j++)
        {
            int chance = rand() % 10 + 1;
            if (chance < 3)
            {
                liste_case[std::make_pair(i,j)].acces = false;
            }
        }
    }

    void graphe::checknoeud()
    {

    }

//    std::map<std::pair<int,int> , noeud> liste_use = liste_case;
//    while(!liste_use.empty())
//    {
//        auto val = liste_use.begin();
//        auto coord = val->first;

//        int nb_voisin = 0;
//        for (auto val : liste_use[coord].liste_voisin)
//        {
//            if (liste_use.find(val) == liste_use.end() && liste_use[val].acces) nb_voisin++;
//        }

//        while (nb_voisin != 0)
//        {
//            for (auto val : liste_use[coord].liste_voisin)
//            {

//            }
//        }
//    }
}

