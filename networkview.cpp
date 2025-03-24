#include "networkview.h"

NetworkView::NetworkView(QWidget *parent) : QLabel(parent)
{
    initialize();
}

void NetworkView::initialize()
{
    setText("");
    setMinimumSize(QSize(2000, 2000));
    setStyleSheet("QLabel { background-color: white; }");
}

void NetworkView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
    {
        emit signalMouseLeftButtonReleased(event->pos());
    }
}

void NetworkView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
    {
        emit signalMouseLeftButtonPressed(event->pos());
    }
}

void NetworkView::mouseMoveEvent(QMouseEvent *event)
{
    emit signalMouseMoved(event->pos());
}

void NetworkView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
    {
        emit signalMouseDoubleClicked(event->pos());
    }
}

void NetworkView::refresh(QPixmap image)
{
    setPixmap(image);
}
