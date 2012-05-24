#include "mybaselistview.h"
#include <QDropEvent>
#include <QApplication>
#include "imageinsequence.h"

MyBaseListView::MyBaseListView(QWidget *parent) :
    QListView(parent)
{
}

void MyBaseListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QListView::mousePressEvent(event);
}

void MyBaseListView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListView::mouseMoveEvent(event);
}

void MyBaseListView::dropEvent(QDropEvent *event)
{
        QModelIndex indModel = indexAt(event->pos());

        this->model()->dropMimeData(event->mimeData(),Qt::MoveAction,indModel.row(),indModel.column(), this->currentIndex());
        event->setDropAction(Qt::MoveAction);
        event->accept();
}

void MyBaseListView::dragEnterEvent(QDragEnterEvent *event)
{
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

void MyBaseListView::performDrag()
{
    QModelIndex indModel = indexAt(startPos);

    QModelIndexList listIndex;
    listIndex.push_front(indModel);

    QMimeData *mimeData = this->model()->mimeData(listIndex);

    /*
    QMimeData *mimeData =  new QMimeData;
    QVariant variant = this->model()->data(indModel,Qt::DisplayRole);

    ImageInSequence is;
    is.fromVariant(variant.toMap());

    mimeData->setData("application/x-myowncustomdata",this->model()->data(indModel,Qt::DisplayRole).toByteArray());
    mimeData->setText(is.image_file);
    */

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction) == Qt::MoveAction;

}

