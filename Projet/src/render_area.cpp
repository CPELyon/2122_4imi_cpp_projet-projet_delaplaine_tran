
#include "render_area.hpp"

#include <iostream>

#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

//#### Fonction libre ####//


//#### Fonction concernant render area ####//

render_area::render_area(graphe mon_graphe,QWidget *parent)
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
    brush.setColor(Qt::gray); //color of the interior of the shape
    brush.setStyle(Qt::NoBrush); //fill the interior
    painter.setBrush(brush);

    //if grid_state is true, then we draw the grid
    if(grid_state)
    {
        int dim_x = mon_graphe.dim_x;
        int dim_y = mon_graphe.dim_y;
        for (int i = 0; i < dim_x; i++)
        {
            for (int j = 0; j < dim_y; j++)
            {
                int coin_sup_x = i*((this->width())/dim_x);
                int coin_sup_y = j*((this->height())/dim_y);
                int coin_inf_x = coin_sup_x + (this->width())/dim_x;
                int coin_inf_y = coin_sup_y + (this->height())/dim_y;
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

void render_area::mousePressEvent(QMouseEvent *event)
{
    //when a click occurs, we store the current mouse position
    x_old=event->x();
    y_old=event->y();
    QWidget* val = this->childAt(x_old,y_old);
    std::cout << "widget : " << val << std::endl;
}

void render_area::mouseMoveEvent(QMouseEvent *event)
{
    //get the current mouse position
    int x=event->x();
    int y=event->y();

    //std::cout << this->childAt(x,y);
    //store the previous mouse position
    x_old=x;
    y_old=y;

    repaint();
}
