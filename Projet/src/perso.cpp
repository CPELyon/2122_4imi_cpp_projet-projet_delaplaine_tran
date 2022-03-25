#include "perso.hpp"

perso::perso()
    :vie(100),miam(100),pos(0,0)
{}

perso::perso(std::pair<int,int> spawn)
    :vie(100),miam(100),pos(spawn)
{}

void perso::mangerp()
{
    if (miam+20 > 100)
    {
        miam=100;
    }else
    {
        miam+=20;
    }
}

void perso::mangerm()
{
    if (miam-1 < 0)
    {
        miam=0;
    }else
    {
        miam-=1;
    }

}

void perso::viep()
{
    if (vie+10 > 100)
    {
        vie=100;
    }else
    {
        vie+=10;
    }
}

void perso::viem()
{
    if (vie-30 < 0)
    {
        vie=0;
    }else
    {
        vie-=30;
    }

}

 std::pair<int,int>& perso::deplacer(std::pair<int,int> arrivee)
 {
   return pos = arrivee;
 }

 std::pair<int,int> perso::deplacer(std::pair<int,int> arrivee) const
 {
   return pos;
 }
