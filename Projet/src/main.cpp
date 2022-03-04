#include <QApplication>

#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "myWindow.hpp"


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

    noeud()
        :acces(true),item(0),liste_voisin()
    {}

    noeud(bool p_acces,int p_item)
       :acces(p_acces),item(p_item)
    {}
};

std::ostream& operator<<(std::ostream& s, noeud const & n)
{
    s<<n.item;
    return s;
}

struct graphe
{
    int dim_x;
    int dim_y;
    std::map<std::pair<int,int> , noeud> liste_case;

    graphe()
        :dim_x(10),dim_y(10),liste_case()
    {}

    graphe(int p_dim_x,int p_dim_y,std::map<std::pair<int,int>,noeud> p_map)
        :dim_x(p_dim_x),dim_y(p_dim_y),liste_case(p_map)
    {}

    void afficher()
    {
        for (auto& val: liste_case)
        {
            auto coord = val.first;
            int dim_x = std::get<0>(coord);
            int dim_y = std::get<1>(coord);
            std::cout << "Position (" << dim_x << "," << dim_y << ") | Item : " << val.second << '\n';
        }
    }

};

int main(int argc,char *argv[])
{
    std::map<std::pair<int,int> , noeud> liste_case;
    int dim_x = 2;
    int dim_y = 4;
    for (int i = 0; i < dim_x; i++)
    {
        for (int j = 0; j < dim_y; j++)
        {
            noeud ma_case = noeud();
            std::pair <int,int> coord (i,j);
            liste_case[coord] = ma_case;
        }
    }

    graphe mon_graphe = graphe(dim_x,dim_y,liste_case);

    mon_graphe.afficher();

    QApplication app(argc,argv);
    window win;
    win.show();
    return app.exec();


    return 0;
}
