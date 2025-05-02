#include"networkview.h"

NetworkView::NetworkView(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
}
