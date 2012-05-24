#include "imageinsequence.h"

ImageInSequence::ImageInSequence(){
}

ImageInSequence::ImageInSequence(ImageInSequence *imIn){
    this->image_file = imIn->image_file;
}


QVariantMap ImageInSequence::toVariantMap(){
    QVariantMap imgsequence;
    imgsequence.insert("image_file",image_file);
    return imgsequence;
}

bool ImageInSequence::fromVariant(QVariantMap variantMap){
    ImageInSequence();
    image_file = variantMap["image_file"].toString();
    return true;
}

bool ImageInSequence::operator == (const ImageInSequence & is){
    if(is.image_file == this->image_file){
        return true;
    }else{
        return false;
    }
}

