#include "window.hpp"

#include "ui_mainwindow.h"

#include <iostream>


window::window(graphe mon_graphe,QWidget *parent)
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
