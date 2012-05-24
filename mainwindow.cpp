#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageinsequence.h"
#include "imageseqmodel.h"
#include "imagereceptordelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initiate some data
    ImageInSequence oneS1 = new ImageInSequence();
    oneS1.image_file = "image1.jpg";

    ImageInSequence oneS2 = new ImageInSequence();
    oneS2.image_file = "image2.jpg";

    ImageInSequence oneS3 = new ImageInSequence();
    oneS3.image_file = "image3.jpg";

    QList<ImageInSequence> *listSeq = new QList<ImageInSequence>();
    listSeq->push_front(oneS1);
    listSeq->push_front(oneS2);
    listSeq->push_front(oneS3);


    ImageSeqModel *seqModel = new ImageSeqModel(this,listSeq);

    ImageReceptorDelegate *delegate = new ImageReceptorDelegate();

    //Set data and item delegate to the listView
    ui->listView->setModel(seqModel);
    ui->listView->setItemDelegate(delegate);

    //Set accept drag and drop
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listView->setDragEnabled(true);
    ui->listView->setAcceptDrops(true);
    ui->listView->setDropIndicatorShown(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->viewport()->setAcceptDrops(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
