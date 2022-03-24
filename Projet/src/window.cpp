#include "window.hpp"

#include "ui_mainwindow.h"

#include <iostream>


window::window(graphe& mon_graphe,QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow),render(new render_area(mon_graphe)),mon_graphe(mon_graphe)
{
    std::cout<<"Generate the Window"<<std::endl;

    //setup the graphical interface to the current widget
    ui->setupUi(this);

    //Attach the render_area window to the widget
    ui->layout_scene->addWidget(render);

    //connect signals
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(action_quit()));
    connect(ui->draw,SIGNAL(clicked()),this,SLOT(action_draw()));
    connect(ui->parcours,SIGNAL(clicked()),this,SLOT(action_parcours()));
    connect(ui->wall,SIGNAL(clicked()),this,SLOT(action_wall()));
    connect(ui->init,SIGNAL(clicked()),this,SLOT(action_init()));
}


window::~window()
{
    std::cout<<"Destructor of Window is called"<<std::endl;
}

void window::action_quit()
{
    close();
}

void window::action_draw()
{
    render->change_grid_state();
}

void window::action_parcours()
{
    render->change_parcours_state();
}

void window::action_wall()
{
    render->generate_wall();
}

void window::action_init()
{
    render->define_debut_fin();
}
