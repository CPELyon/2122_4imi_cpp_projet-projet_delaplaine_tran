#include <QApplication>
#include "window.hpp"

#include <stdlib.h>

int main(int argc,char *argv[])
{
    std::map<std::pair<int,int> , noeud> liste_case;
    int dim_x = 30;
    int dim_y = 20;
    for (int i = 0; i < dim_x; i++)
    {
        for (int j = 0; j < dim_y; j++)
        {
            noeud ma_case = noeud(true,0);
            int chance = rand() % 10 + 1;
            if (chance < 4)
            {
                ma_case.acces = false;
            }

            ma_case.set_voisin(i,j,dim_x,dim_y);
            //std::cout<<"case : ("<<i<<","<<j<<") :";
            //ma_case.afficher_voisin();
            std::pair <int,int> coord (i,j);
            liste_case[coord] = ma_case;
        }
    }

    graphe mon_graphe = graphe(dim_x,dim_y,liste_case);

    mon_graphe.liste_case[std::make_pair(1,1)].acces = false;

    // mon_graphe.afficher();



    //#### Gestion graphique ####//
    QApplication app(argc,argv);
    window win(mon_graphe);
    win.show();
    return app.exec();


    return 0;
}
