#include "detectclick.h"

DetectClick::DetectClick() : QGraphicsView()
{

}


void DetectClick::mousePressEvent(QMouseEvent* event)
{
    emit mouseClicked(event->x(), event->y());
}
