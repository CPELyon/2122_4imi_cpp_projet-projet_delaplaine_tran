#include <QApplication>
#include "window.hpp"


int main(int argc,char *argv[])
{
    std::map<std::pair<int,int> , noeud> liste_case;
    int dim_x = 20;
    int dim_y = 10;
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

    // mon_graphe.afficher();


    //#### Gestion graphique ####//
    QApplication app(argc,argv);
    window win(mon_graphe);
    win.show();
    return app.exec();


    return 0;
}
