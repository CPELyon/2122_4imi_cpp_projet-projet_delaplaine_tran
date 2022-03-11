#include "noeud.hpp"

noeud::noeud()
    :acces(true),item(0),liste_voisin()
{}

noeud::noeud(bool p_acces,int p_item)
   :acces(p_acces),item(p_item)
{}

std::ostream& operator<<(std::ostream& s, noeud const & n)
{
    s<<n.item;
    return s;
}





