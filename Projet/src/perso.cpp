#include "perso.hpp"

perso::perso()
    :vie(100),miam(100),pos(0,0)
{}

perso::perso(std::pair<int,int> spawn)
    :vie(100),miam(100),pos(spawn)
{}

void perso::mangerp()
{
    miam+=10;
}

void perso::mangerm()
{
    miam-=10;
}

void perso::viep()
{
    vie-=10;
}

void perso::viem()
{
    vie-=10;
}

 void perso::deplacer(std::pair<int,int> &pos,std::pair<int,int> &arrivee)
 {
   pos = arrivee;
 }


