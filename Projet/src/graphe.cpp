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

int graphe::checknoeud()
{
    Yugo.score += 10;
    Yugo.mangerm();
    int rep = 0;
    if (liste_case[Yugo.pos].item==4){
       Yugo.mangerp();
       //std::cout<<"manger plus"<<std::endl;
    }
    if (liste_case[Yugo.pos].item==5){
       Yugo.viem();
       Yugo.score += 50;
       //std::cout<<"vie moins"<<std::endl;
    }
    if (liste_case[Yugo.pos].item==6){
       Yugo.viep();
       //std::cout<<"vie plus"<<std::endl;
    }
    if (liste_case[Yugo.pos].item==7){
       //changement map
       reset_map();
       rep = 1;
       Yugo.score += 20;
    }
    return rep;
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
}

void graphe::reset_parcours()
{
    for (auto val : liste_case)
    {
        auto coord = std::get<0>(val);
        if (liste_case[coord].item == 3)
        {
            liste_case[coord].item = 0;
        }
    }
}

void graphe::reset_debut()
{
    for (auto val : liste_case)
    {
        auto coord = std::get<0>(val);
        if (liste_case[coord].item == 1)
        {
            liste_case[coord].item = 0;
        }
    }
}

void graphe::reset_fin()
{
    for (auto val : liste_case)
    {
        auto coord = std::get<0>(val);
        if (liste_case[coord].item == 2)
        {
            liste_case[coord].item = 0;
        }
    }
}

void graphe::reset_map()
{
    for (auto val : liste_case)
    {
        auto coord = std::get<0>(val);
        liste_case[coord].acces = true;
        liste_case[coord].item = 0;
    }
}

