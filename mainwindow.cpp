#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageinsequence.h"
#include "imageseqmodel.h"
#include "imagereceptordelegate.h"
#include "QDropEvent"
#include "iostream"

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

    QList<ImageInSequence> *listSeq2 = new QList<ImageInSequence>();

    ImageSeqModel *seqModel2 = new ImageSeqModel(this,listSeq2);

    ImageReceptorDelegate *delegate2 = new ImageReceptorDelegate();

    //Set data and item delegate to the listView
    ui->listView_2->setModel(seqModel2);
    ui->listView_2->setItemDelegate(delegate2);

    //Set drag an drop to the second listview
    ui->listView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listView_2->setDragEnabled(true);
    ui->listView_2->setAcceptDrops(true);
    ui->listView_2->setDropIndicatorShown(true);

}


MainWindow::~MainWindow()
{
    delete ui;
}
