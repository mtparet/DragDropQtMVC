#include "mybaselistview.h"
#include <QDropEvent>
#include <QApplication>
#include <iostream>
#include <QMimeData>
#include <QDrag>
#include "imageinsequence.h"

MyBaseListView::MyBaseListView(QWidget *parent) :
    QListView(parent)
{
}

void MyBaseListView::mousePressEvent(QMouseEvent *event)
{
    std::cout << "mouse press event" << std::endl;

    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QListView::mousePressEvent(event);
}

void MyBaseListView::mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "enter move event" << std::endl;

    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListView::mouseMoveEvent(event);
}

void MyBaseListView::dropEvent(QDropEvent *event)
{
    std::cout << " drop event" << std::endl;

        QModelIndex indModel = indexAt(event->pos());

        this->model()->dropMimeData(event->mimeData(),Qt::MoveAction,indModel.row(),indModel.column(), this->currentIndex());
        event->setDropAction(Qt::MoveAction);
        event->accept();
}

void MyBaseListView::dragEnterEvent(QDragEnterEvent *event)
{
    std::cout << "enter drag enter event" << std::endl;

    if (event->mimeData()->hasFormat("application/x-myowncustomdata")){
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void MyBaseListView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-myowncustomdata")){
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void MyBaseListView::mouseReleaseEvent(QMouseEvent *e){
    std::cout << "leave mouse release event" << std::endl;


}


void MyBaseListView::performDrag()
{
    QModelIndex indModel = indexAt(startPos);

    QModelIndexList listIndex;
    listIndex.push_front(indModel);

    QMimeData *mimeData = this->model()->mimeData(listIndex);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction) == Qt::MoveAction;

}

void MyBaseListView::dragLeaveEvent(QDragLeaveEvent *e){
    std::cout << "leave event" << std::endl;
    if(e->isAccepted()){
        std::cout << "leave accepted event" << std::endl;

        QModelIndex indModel = indexAt(startPos);
        bool test = this->model()->removeRow(indModel.row());
        std::cout << test << std::endl;

    }
}



