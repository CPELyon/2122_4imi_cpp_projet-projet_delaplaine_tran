#include <QApplication>
#include "window.hpp"

void afficher_algo(graphe g){
    for (int i=0; i<g.dim_x;i++)
    {std::cout<<std::endl;
        for (int j=0; j<g.dim_y;j++)
        {
            std::pair<int,int> coord (i,j);
            int a= g.liste_case[coord].item;
            std::cout<<a<<" ";
        }
    }
    std::cout<<std::endl;

}

int boucle(noeud &parcours, std::list<std::pair<int,int>> &queue, std::map<std::pair<int,int>,bool> &visite,graphe &g,std::pair<int,int> &arrivee){
    for (auto coord_voisin: parcours.liste_voisin)
    {


        //Si les coordonées du voisin correspondent à l'arrivée on sort de la boucle
        if (arrivee== coord_voisin)
        {
            return 0;

        }

        //Si on tombe sur un mur, on n'ajoute pas ses coordonnées dans queue mais on dit qu'on l'a vérifié
        if (g.liste_case[coord_voisin].acces== false ) //mur
        {
            g.liste_case[coord_voisin].item=2;
            visite[coord_voisin]=true;
        }

        //Sinon on dit qu'on a vérifié le voisin et on l'ajoute à la queue pour refaire l'algo
        if (visite[coord_voisin]==false)
        {

            afficher_algo(g);
            g.liste_case[coord_voisin].item=4;
            visite[coord_voisin]=true;
            queue.push_back(coord_voisin);
        }
    }
}





void parcourslargeur(graphe g, int x_dep,int y_dep, int x_ar, int y_ar)
{
    std::pair<int,int> coord1(0,1);
    g.liste_case[coord1].acces=false;
    std::pair<int,int> coord2(1,2);
    g.liste_case[coord2].acces=false;
    std::pair<int,int> coord3(1,3);
    g.liste_case[coord3].acces=false;
    std::pair<int,int> coord4(1,4);
    g.liste_case[coord4].acces=false;
    //Creation coorndonées de départ et d'arrivée.
    std::pair<int,int> debut(x_dep,y_dep);
    std::pair<int,int> arrivee(x_ar,y_ar);
    int stop = 1;
    //Creation du noeud de depart en fonction des coordonnées de depart
    noeud n_depart = g.liste_case[debut];
    g.liste_case[debut].item=4;
    // On crée une grille bool et on initialise
    // à 0 pour dire qu'on a visité aucune case
    std::map<std::pair<int,int>,bool> visite;
    for (int i=0; i<g.dim_x;i++)
    {
        for (int j=0; j<g.dim_y;j++)
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
    int w=0;
    //On parcourt la queue tant qu'elle n'est pas vide.
    while(stop!=0)
    {
        //On affiche l'élement qu'on va vérifier de la queue
        debut=queue.front();
        std::cout<<debut.first<<debut.second<<std::endl;
        queue.pop_front();
        noeud parcours = g.liste_case[debut];
        stop = boucle(parcours,queue,visite,g,arrivee);

    }
    std::cout<<"ARRIVEE TROUVEE"<<std::endl;
}



int main(int argc,char *argv[])
{
    std::map<std::pair<int,int> , noeud> liste_case;
    int dim_x = 6;
    int dim_y = 6;
    for (int i = 0; i < dim_x; i++)
    {
        for (int j = 0; j < dim_y; j++)
        {
            noeud ma_case = noeud();
            ma_case.set_voisin(i,j,dim_x,dim_y);
            std::pair <int,int> coord (i,j);
            liste_case[coord] = ma_case;
        }
    }


    graphe mon_graphe = graphe(dim_x,dim_y,liste_case);
    parcourslargeur(mon_graphe,1,1,3,3);
    // mon_graphe.afficher();


    //#### Gestion graphique ####//
    QApplication app(argc,argv);
    window win(mon_graphe);
    win.show();
    return app.exec();


    return 0;
}


