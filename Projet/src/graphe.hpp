#pragma once


#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "noeud.hpp"

struct graphe
{
    int dim_x;
    int dim_y;
    std::map<std::pair<int,int> , noeud> liste_case;

    graphe();

    graphe(int p_dim_x,int p_dim_y,std::map<std::pair<int,int>,noeud> p_map);

    void afficher();

    int get_nb_mur();

    void generate_wall();

    void reset_parcours();
    void reset_debut();
    void reset_fin();

};

#endif // GRAPHE_HPP
