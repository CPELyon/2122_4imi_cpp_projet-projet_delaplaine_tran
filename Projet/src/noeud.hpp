#pragma once

#ifndef NOEUD_HPP
#define NOEUD_HPP

#include <iostream>
#include <map>
#include <utility>
#include <vector>

struct noeud
{
    // Attribut pour savoir si c'est un obstacle ou non
    //  true : case libre
    //  false : case avec obstacle
    bool acces;
    // Item contenu sur la case
    //  0 : aucun item présent
    //  1 : nourriture
    int item;
    std::vector<std::pair<int,int>> liste_voisin;

    noeud();

    noeud(bool p_acces,int p_item);

};

std::ostream& operator<<(std::ostream& s, noeud const & n);

#endif // NOEUD_HPP
