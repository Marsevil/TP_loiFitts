#ifndef DETECTCLICK_H
#define DETECTCLICK_H

#include <QGraphicsView>
#include <QMouseEvent>

class DetectClick : public QGraphicsView
{
    Q_OBJECT

public:
    DetectClick();

signals:
    void mouseClicked(int, int);

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // DETECTCLICK_H
