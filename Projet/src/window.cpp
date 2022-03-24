#include "window.hpp"
#include "ui_mainwindow.h"

#include <iostream>


window::window(graphe& mon_graphe,QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow),render(new render_area(mon_graphe,ui)),mon_graphe(mon_graphe)
{
    std::cout<<"Generate the Window"<<std::endl;

    //setup the graphical interface to the current widget
    ui->setupUi(this);

    //Attach the render_area window to the widget
    ui->layout_scene->addWidget(render);

    //connect signals
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(action_quit()));
    connect(ui->Lancer,SIGNAL(clicked()),this,SLOT(action_lancer()));

    //configure default option for ui
    ui->miam->setVisible(0);
    ui->vie->setVisible(0);
    ui->label->setVisible(0);
    ui->label_2->setVisible(0);
}


window::~window()
{
    std::cout<<"Destructor of Window is called"<<std::endl;
}

void window::action_quit()
{
    close();
}

void window::action_lancer()
{
    render->game_start(0,0,false);
}
