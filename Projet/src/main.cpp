#include <QApplication>
#include "window.hpp"

int boucle(noeud &parcours, std::list<std::pair<int,int>> &queue, std::map<std::pair<int,int>,bool> &visite,graphe g,std::pair<int,int> arrivee){
    for (auto coord_voisin: parcours.liste_voisin)
    {
        //Si les coordonées du voisin correspondent à l'arrivée on sort de la boucle
        if (arrivee== coord_voisin)
        {
            std::cout<<"ARRIVEE TROUVEE"<<std::endl;
            return 0;
        }

        //Si on tombe sur un mur, on n'ajoute pas ses coordonnées dans queue mais on dit qu'on l'a vérifié
        if (g.liste_case[coord_voisin].acces== false ) //mur
        {
            visite[coord_voisin]=true;
            return 1;
        }

        //Sinon on dit qu'on a vérifié le voisin et on l'ajoute à la queue pour refaire l'algo
        else if (!visite[coord_voisin])
        {
            visite[coord_voisin]=true;
            queue.push_back(coord_voisin);
            return 1;
        }
    }
}




void parcourslargeur(graphe g, int x_dep,int y_dep, int x_ar, int y_ar)
{
    //Creation coorndonées de départ et d'arrivée.
    std::pair<int,int> debut(x_dep,y_dep);
    std::pair<int,int> arrivee(x_ar,y_ar);
    int stop = 1;
    //Creation du noeud de depart en fonction des coordonnées de depart
    noeud n_depart = g.liste_case[debut];

    // On crée une grille bool et on initialise
    // à 0 pour dire qu'on a visité aucune case
    std::map<std::pair<int,int>,bool> visite;
    for (int i=0; i<g.dim_x;i++)
    {
        for (int j=0; i<g.dim_y;i++)
        {
        std::pair<int,int> coord(i,j);
        visite[coord]=false;
        }
    }

    //On crée une queue de coordonnées à vérifier
    std::list<std::pair<int,int>> queue;

    //Notre point de départ est vérifié on le met dans la queue
    visite[debut]=true;
    queue.push_back(debut);

    //On parcourt la queue tant qu'elle n'est pas vide.
    while(stop!=0)
    {
        //On affiche l'élement qu'on va vérifier de la queue
        debut=queue.front();
        std::cout<<"s"<<std::endl;
        queue.pop_front();
        noeud parcours = g.liste_case[debut];
        stop = boucle(parcours,queue,visite,g,arrivee);

    }
}



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
    parcourslargeur(mon_graphe,5,5,8,9);
    // mon_graphe.afficher();


    //#### Gestion graphique ####//
    QApplication app(argc,argv);
    window win(mon_graphe);
    win.show();
    return app.exec();


    return 0;
}


