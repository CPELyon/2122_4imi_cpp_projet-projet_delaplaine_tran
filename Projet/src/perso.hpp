#ifndef PERSO_HPP
#define PERSO_HPP
#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <vector>

struct perso
{
    // Points de vie de notre personnage entre 0 et 100
    int vie;
    // Nourriture de notre personnage entre 0 et 100
    int miam;
    // position de notre personnage sur la map
    std::pair<int,int> pos;

    // Score
    int score;
    // Variable de fin
    bool fin = false;

    perso();
    perso(std::pair<int,int> spawn);

    void mangerp();
    void mangerm();
    void viep();
    void viem();
    std::pair<int,int>& deplacer(std::pair<int,int> arrivee);
    std::pair<int,int> deplacer(std::pair<int,int> arrivee) const;

};

#endif // PERSO_HPP
