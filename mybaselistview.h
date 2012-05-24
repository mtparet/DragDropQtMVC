#ifndef MYBASELISTVIEW_H
#define MYBASELISTVIEW_H

#include <QListView>

class MyBaseListView : public QListView
{
    Q_OBJECT
public:
    explicit MyBaseListView(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void dropEvent(QDropEvent *event);

private:
    void performDrag();

    QPoint startPos;
    
signals:
    
public slots:
    
};

#endif // MYBASELISTVIEW_H
