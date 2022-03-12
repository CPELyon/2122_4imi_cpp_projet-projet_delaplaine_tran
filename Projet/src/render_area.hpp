#pragma once

#ifndef RENDER_AREA_HPP
#define RENDER_AREA_HPP

#include <QWidget>

#include "graphe.hpp"

//Forward declaration of QPixmap
class QPixmap;

/** Declaration of render_area class */
class render_area : public QWidget
{
    Q_OBJECT
    graphe& mon_graphe;
public:
    render_area(graphe& mon_graphe,QWidget *parent = nullptr);
    ~render_area();

    /** Inverse the state of the draw_grid variable
        Draw or not the grid */
    void change_grid_state();

protected:
	/** The actual painting function */
     void paintEvent(QPaintEvent *event);
     /** Function called when the mouse is pressed */
     void mousePressEvent(QMouseEvent *event);
     /** Function called when the mouse is moved */
     void mouseMoveEvent(QMouseEvent *event);

private:

	/** A QPixmap is an image */
    QPixmap *pixmap;
    /** A boolean indicating the grid should be drawn or not */
    bool grid_state;
    /** Storage for the previous position of the mouse */
    int x_old,y_old;


};

#endif
