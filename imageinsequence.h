#ifndef IMAGEINSEQUENCE_H
#define IMAGEINSEQUENCE_H
#include <QString>
#include <QVariantMap>

class ImageInSequence
{
  public:
    ImageInSequence();
    ImageInSequence(ImageInSequence *imIn);
    QString image_file;

    QVariantMap toVariantMap();

    bool fromVariant(QVariantMap variantMap);

    bool operator == (const ImageInSequence & is);

};


#endif // IMAGEINSEQUENCE_H
