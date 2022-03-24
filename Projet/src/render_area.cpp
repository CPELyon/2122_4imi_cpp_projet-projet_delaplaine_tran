
#include "render_area.hpp"

#include <iostream>
#include <windows.h>
#include <cstdlib>

#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

//#### Fonction libre ####//
int boucle(noeud &parcours, std::list<std::pair<int,int>> &queue, std::map<std::pair<int,int>,bool> &visite,graphe &g,std::pair<int,int> &arrivee,int & ret,bool check,bool refill){
    for (auto coord_voisin: parcours.liste_voisin)
    {
        //Si les coordonées du voisin correspondent à l'arrivée on sort de la boucle
        if (check && arrivee == coord_voisin)
        {
            return 0;
        }

        //Si on tombe sur un mur, on n'ajoute pas ses coordonnées dans queue mais on dit qu'on l'a vérifié
        if (g.liste_case[coord_voisin].acces== false ) //mur
        {
            visite[coord_voisin]=true;
        }

        //Sinon on dit qu'on a vérifié le voisin et on l'ajoute à la queue pour refaire l'algo
        if (visite[coord_voisin]==false)
        {
            g.liste_case[coord_voisin].item = 3;
            visite[coord_voisin]=true;
            queue.push_back(coord_voisin);
            ret++;
            if (refill)
            {

                g.liste_case[coord_voisin].acces = false;
            }
        }


    }
}

//#### Fonction concernant render area ####//

int render_area::parcourslargeur(graphe & g, int x_dep,int y_dep, int x_ar, int y_ar,bool check = true,bool refill = false)
{
    g.reset_parcours();
    int ret = 0;
    //Creation coorndonées de départ et d'arrivée.
    std::pair<int,int> debut(x_dep,y_dep);
    std::pair<int,int> arrivee(x_ar,y_ar);
    int stop = 1;
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
    //On parcourt la queue tant qu'elle n'est pas vide.
    while(stop!=0 && !queue.empty())
    {
        //On affiche l'élement qu'on va vérifier de la queue
        debut=queue.front();
        //std::cout<<debut.first<<debut.second<<std::endl;
        queue.pop_front();
        noeud parcours = g.liste_case[debut];
        stop = boucle(parcours,queue,visite,g,arrivee,ret,check,refill);
        //repaint();
    }
    if (check) std::cout<<"ARRIVEE TROUVEE"<<std::endl;
    return ret;
}

std::pair<std::pair<int,int>,noeud> find_min (graphe g,graphe P)
{
    int dist = 1000;
    std::pair<std::pair<int,int>,noeud> ret;
    for (auto val : g.liste_case)
    {
        if (P.liste_case.find(val.first) == P.liste_case.end())
        {
            if (std::get<1>(val).distance < dist)
            {
                dist = val.second.distance;
                ret = val;
            }
        }
    }
    return ret;
}

void render_area::dijkstra(graphe & g, int x_dep,int y_dep, int x_ar, int y_ar)
{
    g.reset_parcours();

    std::map<std::pair<int,int>,noeud> P_liste;
    graphe P = graphe(g.dim_x,g.dim_y,P_liste);
    std::pair<int,int> coord_debut (x_dep,y_dep);
    std::pair<int,int> coord_fin (x_ar,y_ar);

    // On assigne les distances a tout les noeuds de g
    // La case de debut possede une distance nulle
    for (auto val : g.liste_case)
    {
        std::pair<int,int> coord = val.first;
        g.liste_case[coord].distance = 1000;
        if (coord.first == coord_debut.first && coord.second == coord_debut.second){g.liste_case[coord].distance = 0;}
    }

    // variable pour eviter de boucler infiniment
    // signifie que le chemin n'existe pas
    int compteur = 0;
    // On applique l'algorithme de recherche
    while(P.liste_case.size() < g.liste_case.size()-g.get_nb_mur() && compteur <= g.liste_case.size()-g.get_nb_mur())
    {
        compteur++;
        std::pair<std::pair<int,int>,noeud> a = find_min(g,P);
        P.liste_case[a.first] = std::get<1>(a);
        auto liste = g.liste_case[a.first].liste_voisin;
        for (auto b : liste)
        {
            if (P.liste_case.find(b) == P.liste_case.end())
            {
                if (g.liste_case[b].acces)
                {
                    if (g.liste_case[b].distance > std::get<1>(a).distance + 1)
                    {
                        g.liste_case[b].distance = std::get<1>(a).distance + 1;
                        g.liste_case[b].predecesseur = a.first;
                    }
                }
            }
        }
    }
    std::cout<<"nb case : "<<g.liste_case.size()-g.get_nb_mur()<<std::endl;
    std::cout<<"compteur : "<<compteur<<" | p size : "<<P.liste_case.size()<<std::endl;

    // Si on a trouver un chemin alors on le trace
    if (compteur <= g.liste_case.size()-g.get_nb_mur())
    {
        // On en deduit le chemin le plus court entre debut et fin
        std::vector<std::pair<int,int>> A;
        std::pair<int,int> coord_s = coord_fin;
        while (coord_s.first != coord_debut.first || coord_s.second != coord_debut.second)
        {
            A.push_back(std::make_pair(std::get<0>(coord_s),std::get<1>(coord_s)));
            coord_s = g.liste_case[coord_s].predecesseur;
        }
        A.push_back(std::make_pair(std::get<0>(coord_debut),std::get<1>(coord_debut)));

        std::cout<<0<<std::endl;

        // inverser A pour aller du debut a la fin
        std::reverse(A.begin(),A.end());

        // implementation graphique
        for (auto val : A)
        {
            if (g.liste_case[val].item != 1 && g.liste_case[val].item != 2)
            {
                if (g.liste_case[g.liste_case[val].predecesseur].item == 3)
                {
                    g.liste_case[g.liste_case[val].predecesseur].item = 0;
                }
                g.liste_case[val].item = 3;
            }
            Sleep(250);
            repaint();
        }
    }else
    {
        std::cout<<"Aucun chemin trouve"<<std::endl;
    }
}

void render_area::generate_wall()
{

    // #### initialisation de mur random

    for (int i = 0; i < mon_graphe.dim_x; i++)
    {
        for (int j = 0; j < mon_graphe.dim_y; j++)
        {
            int chance = rand() % 10 + 1;
            if (chance < 4)
            {
                mon_graphe.liste_case[std::make_pair(i,j)].acces = false;
            }
        }
    }

    // #### On rebouche les zones isolee

    std::map<std::pair<int,int>,int> zone;

    graphe g_copie = mon_graphe;
    while(!g_copie.liste_case.empty() && g_copie.liste_case.size() != g_copie.get_nb_mur())
    {
        //std::cout<<"modif acces"<<std::endl;
        // definir la premiere case non mur
        auto it = g_copie.liste_case.begin();
        auto coord_debut = it->first;
        bool check = false;
        while (!check)
        {
            if (!g_copie.liste_case[coord_debut].acces)
            {
                it++;
                coord_debut = it->first;
            }else
            {
                check = true;
            }
        }

        // algo de parcours à partir du noeud de depart
        int nb_case_zone = 1+parcourslargeur(g_copie,std::get<0>(coord_debut),std::get<1>(coord_debut),0,0,false);
        zone[coord_debut] = nb_case_zone;

        // on enleve toute les cases parcouru lors de l'algo de parcours
        auto liste_temp = g_copie.liste_case;
        for (auto val : liste_temp)
        {
            auto coord = val.first;
            if (g_copie.liste_case[coord].item == 3)
            {
                g_copie.liste_case.erase(coord);
            }
        }
        g_copie.liste_case.erase(coord_debut);

        // mise a jour des voisins dans la liste de case restante
        for (auto val : g_copie.liste_case)
        {
            auto coord = val.first;
            for (int i = 0; i < g_copie.liste_case[coord].liste_voisin.size(); i++ )
            {
                if (g_copie.liste_case.find(g_copie.liste_case[coord].liste_voisin.at(i)) == g_copie.liste_case.end())
                {
                    g_copie.liste_case[coord].liste_voisin.erase(g_copie.liste_case[coord].liste_voisin.begin()+i);
                }
            }
        }
    }

    // determination de la plus grande zone
    int max = 0;
    for (auto it=zone.begin(); it != zone.end(); ++it)
    {
        auto coord = it->first;
        if (zone[coord] > max )
        {
            max = zone[coord];
        }
    }

    // remplissage des zones isolee
    for (auto it=zone.begin(); it != zone.end(); ++it)
    {
        auto coord = it->first;
        if (zone[coord] != max)
        {
            // permet de passer a false tte les cases de la zones
            parcourslargeur(mon_graphe,std::get<0>(coord),std::get<1>(coord),0,0,false,true);
            mon_graphe.liste_case[coord].acces = false; // on le ft manuellement pour le premier element
        }
    }
    repaint();
}

render_area::render_area(graphe& mon_graphe,QWidget *parent)
    :QWidget(parent),pixmap(new QPixmap),grid_state(false),mon_graphe(mon_graphe),
      x_old(0),y_old(0)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

render_area::~render_area()
{
	if(pixmap!=nullptr)
	{
		delete pixmap;
		pixmap=nullptr;
	}
}

void render_area::paintEvent(QPaintEvent*)
{
    //A painter class able to draw in 2D
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //The drawing pen with its properties
    QPen pen;
    pen.setWidth(1.0);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    //The brush class is usefull to fill the interior of the shapes
    QBrush brush = painter.brush();
    // brush.setColor(Qt::white); //color of the interior of the shape
    brush.setStyle(Qt::SolidPattern); //fill the interior
    painter.setBrush(brush);

    //if grid_state is true, then we draw the grid
    if(grid_state)
    {

        int dim_x = mon_graphe.dim_x;
        int dim_y = mon_graphe.dim_y;

        // std::cout << ' ' << col_ind << ' ' << ligne_ind << std::endl;

        for (int i = 0; i < dim_x; i++)
        {
            for (int j = 0; j < dim_y; j++)
            {

                int coin_sup_x = i*((this->width())/dim_x);
                int coin_sup_y = j*((this->height())/dim_y);
                int coin_inf_x = coin_sup_x + (this->width())/dim_x;
                int coin_inf_y = coin_sup_y + (this->height())/dim_y;
                // std::cout<<mon_graphe.liste_case[std::make_pair(i,j)].acces<<std::endl;

                if (mon_graphe.liste_case[std::make_pair(i,j)].acces == false)
                {
                    brush.setColor(Qt::black);
                    painter.setBrush(brush);
                }else if (mon_graphe.liste_case[std::make_pair(i,j)].item == 1)
                {
                    QColor color(251, 35, 17);
                    brush.setColor(color);
                    painter.setBrush(brush);
                }else if (mon_graphe.liste_case[std::make_pair(i,j)].item == 2)
                {
                    QColor color(104, 171, 242);
                    brush.setColor(color);
                    painter.setBrush(brush);
                }else if (mon_graphe.liste_case[std::make_pair(i,j)].item == 3)
                {
                    QColor color(116, 126, 136);
                    brush.setColor(color);
                    painter.setBrush(brush);
                }else
                {
                    brush.setColor(Qt::white);
                    painter.setBrush(brush);
                }
                painter.drawRect(coin_sup_x,coin_sup_y,coin_inf_x,coin_inf_y);
            }
        }
    }

}


void render_area::change_grid_state()
{
    grid_state=!grid_state;
    repaint();
}


void render_area::define_debut_fin()
{
    std::pair<int,int> debut = define_debut(0,0,false);
    //std::pair<int,int> fin = define_fin(0,0,false);

    //std::cout<<"Debut : "<<mon_graphe.liste_case[debut].acces<<" | fin : "<<mon_graphe.liste_case[fin].acces<<std::endl;
    //std::cout<<"Debut : ("<<debut.first<<","<<debut.second<<") | fin : ("<<fin.first<<","<<fin.second<<")"<<std::endl;
}

std::pair<int,int> render_area::define_debut(int pos_x = 0,int pos_y = 0,bool accept_pos = false)
{
    // reset du debut dans le graphe
    mon_graphe.reset_debut();

    // init des coords du debut et de la fin dans la map
    int debut_x;
    int debut_y;
    if (!accept_pos)
    {
        debut_x = rand() % (mon_graphe.dim_x-1);
        debut_y = rand() % (mon_graphe.dim_y-1);

    }else
    {
        debut_x = pos_x;
        debut_y = pos_y;
    }

    std::pair<int,int> debut (debut_x,debut_y);

    // config de la case de debut dans la map
    bool check = false;
    while (!check)
    {
        if (mon_graphe.liste_case[debut].acces)
        {
            mon_graphe.liste_case[debut].item = 1;
            check = true;
        }else
        {
            if (std::get<0>(debut) < mon_graphe.dim_x-1){std::get<0>(debut) += 1;}
            else if (std::get<1>(debut) < mon_graphe.dim_y-1){std::get<1>(debut) += 1;}
            else
            {
                std::get<0>(debut) = 0;
                std::get<1>(debut) = 0;
            }
        }
    }

    repaint();
    return debut;
}

std::pair<int,int> render_area::define_fin(int pos_x = 0,int pos_y = 0,bool accept_pos = false)
{
    // reset de la fin dans le graphe
    mon_graphe.reset_fin();

    // init des coords du debut et de la fin dans la map
    int fin_x;
    int fin_y;
    if (accept_pos)
    {
        fin_x = rand() % (mon_graphe.dim_x-1);
        fin_y = rand() % (mon_graphe.dim_y-1);

    }else
    {
        fin_x = pos_x;
        fin_y = pos_y;
    }
    std::pair<int,int> fin (fin_x,fin_y);

    // config de la case de fin dans la map
    bool check = false;
    while (!check)
    {
        if (mon_graphe.liste_case[fin].acces && mon_graphe.liste_case[fin].item != 1)
        {
            mon_graphe.liste_case[fin].item = 2;
            check = true;
        }else
        {
            if (std::get<0>(fin) < mon_graphe.dim_x-1){std::get<0>(fin) += 1;}
            else if (std::get<1>(fin) < mon_graphe.dim_y-1){std::get<1>(fin) += 1;}
            else
            {
                std::get<0>(fin) = 0;
                std::get<1>(fin) = 0;
            }
        }
    }
    repaint();
    return fin;
}

void render_area::change_parcours_state()
{
    parcours_state=!parcours_state;
    std::pair<int,int> debut;
    std::pair<int,int> fin;
    for (auto val : mon_graphe.liste_case)
    {
        auto coord = std::get<0>(val);
        if (mon_graphe.liste_case[coord].item == 1)
        {
            debut = coord;
        }else if (mon_graphe.liste_case[coord].item == 2)
        {
            fin = coord;
        }
    }

    // Appel des algo de parcours

    //int cpt = parcourslargeur(mon_graphe,std::get<0>(debut),std::get<1>(debut),std::get<0>(fin),std::get<1>(fin));
    dijkstra(mon_graphe,debut.first,debut.second,fin.first,fin.second);
    //dijkstra(mon_graphe,0,0,mon_graphe.dim_x-1,mon_graphe.dim_y-1);
    //parcourslargeur(mon_graphe,0,0,mon_graphe.dim_x-1,mon_graphe.dim_y-1);
    repaint();

}

void render_area::mousePressEvent(QMouseEvent *event)
{
    //when a click occurs, we store the current mouse position
    x_old=event->x();
    y_old=event->y();

    int col_ind = x_old / (this->width()/mon_graphe.dim_x);
    int ligne_ind = y_old / (this->height()/mon_graphe.dim_y);

    std::pair<int,int> coord_fin (col_ind,ligne_ind);

    // recuperation des coord du debut et de fin
    std::pair<int,int> debut;
    for (auto val : mon_graphe.liste_case)
    {
        auto coord = std::get<0>(val);
        if (mon_graphe.liste_case[coord].item == 1)
        {
            debut = coord;
        }
    }

    dijkstra(mon_graphe,debut.first,debut.second,coord_fin.first,coord_fin.second);

    // on redefinit le debut
    define_debut(coord_fin.first,coord_fin.second,true);

    //repaint();
}

void render_area::mouseMoveEvent(QMouseEvent *event)
{
    //get the current mouse position
    int x=event->x();
    int y=event->y();

    //store the previous mouse position
    x_old=x;
    y_old=y;

    // repaint();
}
