#include "imageseqmodel.h"
#include "imageinsequence.h"
#include "QMimeData"
#include "QStringList"
#include "iostream"

ImageSeqModel::ImageSeqModel(QObject *parent, QList<ImageInSequence> *li) :
    QAbstractListModel(parent)
{
    this->li = *li;
}

int ImageSeqModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return li.count();
}

QVariant ImageSeqModel::data(const QModelIndex &index, int role) const {
     int row = index.row();

     if (role != Qt::DisplayRole){
         return (QVariant::Invalid);
    }
    if ((index.column() == 0) && (row >= 0) && (row < rowCount()))
    {
      ImageInSequence is = li.at(index.row());
      return is.toVariantMap();
    }
    return (QVariant::Invalid);
}


Qt::DropActions ImageSeqModel::supportedDropActions() const
 {
     return Qt::CopyAction | Qt::MoveAction;
 }

Qt::DropActions ImageSeqModel::supportedDragActions() const
 {
     return Qt::CopyAction | Qt::MoveAction;
 }

 Qt::ItemFlags ImageSeqModel::flags(const QModelIndex &index) const{
     Qt::ItemFlags defaultFlags = 0;

     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
     else
         return Qt::ItemIsDropEnabled | defaultFlags;

 }

 bool ImageSeqModel::dropMimeData(const QMimeData *data,
     Qt::DropAction action, int row, int column, const QModelIndex &parent)
 {
     if (action == Qt::IgnoreAction)
         return true;

     if (column > 0)
         return false;

     int beginRow;

      if (row != -1)
          beginRow = row;
      else if (parent.isValid())
               beginRow = parent.row();
      else
          beginRow = rowCount(QModelIndex());

      QByteArray encodedData = data->data("application/x-myowncustomdata");
      QDataStream stream(&encodedData, QIODevice::ReadOnly);

      QVariant  isVariant;
        stream >> isVariant;


      QModelIndex idx = index(beginRow, 0, QModelIndex());
      setData(idx, isVariant);
      return true;

 }

QStringList ImageSeqModel::mimeTypes() const{
    QStringList types;
    types << "application/x-myowncustomdata";
    return types;
}

QMimeData * ImageSeqModel::mimeData ( const QModelIndexList & indexes ) const{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);


    stream << data(indexes.first(), Qt::DisplayRole);


    mimeData->setData("application/x-myowncustomdata", encodedData);
    return mimeData;
}


bool ImageSeqModel::setData ( const QModelIndex & index, const QVariant & value, int role  ){
    if (!index.isValid() )
    {
        return false;
    }
    int row = index.row();

    if(row < 0){
            return false;
    }
    ImageInSequence is;
    is.fromVariant(value.toMap());

    //Si l'objet n'est pas contenu on l'insert sinon on le déplace
    if(li.contains(is)){
        li.removeOne(is);
        li.insert(row,is);
    }else{
       li.insert(row,is);
    }

    emit dataChanged(index,index);
    return true;
}

bool ImageSeqModel::removeRows(int row, int count, const QModelIndex &parent){
    if(row > li.count() || row < 0){
        return false;
    }

    li.removeAt(row);

    QModelIndex startIndex = index(0,0);
   QModelIndex endIndex =  index(li.count(),0);

    emit dataChanged(startIndex,endIndex);

    return true;
}


