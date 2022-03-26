#ifndef PERSO_HPP
#define PERSO_HPP
#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <vector>

struct perso
{
    // Variable de fin
    bool fin = false;

    perso();
    perso(std::pair<int,int> spawn);
    ~perso();


    virtual void mangerp();
    virtual void mangerm();
    virtual void viep();
    virtual void viem();
    std::pair<int,int>& deplacer(std::pair<int,int> arrivee);
    std::pair<int,int> deplacer(std::pair<int,int> arrivee) const;

    int getsetmiam() const;
    int& getsetmiam();
    int getsetvie() const;
    int& getsetvie();
    int getsetscore() const;
    int& getsetscore();
    std::pair<int,int> getsetpos() const;
    std::pair<int,int>& getsetpos();

protected:
    // Points de vie de notre personnage entre 0 et 100
    int vie;
    // Nourriture de notre personnage entre 0 et 100
    int miam;
    // position de notre personnage sur la map
    std::pair<int,int> pos;

private:
    // Score
    int score;

};

struct aventurier : public perso
{
    void mangerp();
    void mangerm();
    void viep();
    void viem();
};

struct guerrier : public perso
{
    void mangerp();
    void mangerm();
    void viep();
    void viem();
};

struct sorcier : public perso
{
    void mangerp();
    void mangerm();
    void viep();
    void viem();
};

#endif // PERSO_HPP
