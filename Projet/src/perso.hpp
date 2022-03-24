#ifndef PERSO_HPP
#define PERSO_HPP
#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <vector>

struct perso
{
    int vie;
    // Points de vie de notre personnage entre 0 et 100
    int miam;
    // Nourriture de notre personnage entre 0 et 100
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
    void deplacer(std::pair<int,int> arrivee);

};

#endif // PERSO_HPP
