#include "tworker.h"
#include <QDirIterator>

TWorker::TWorker(QObject *parent) : QObject(parent)
{
    _working = false;
    _abort = false;
}

TWorker::~TWorker()
{

}

void TWorker::doWork()
{

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpe" << "*.JPEG";

    QDirIterator iterator (dirpath, filters, QDir::Files , QDirIterator::Subdirectories);

    while(iterator.hasNext()){
        iterator.next();
        qDebug() << "Cover art changing: " <<  iterator.fileInfo().absoluteFilePath();
        //QMatrix tMat;
        //tMat.  // .scale(32,32);
        //ipn->DisplayCoverArt(iterator.fileInfo().absoluteFilePath());
       // QPixmap * image = new QPixmap(iterator.fileInfo().absoluteFilePath());

       // QPixmap * image2 = new QPixmap(image->scaled(QSize(256,256),Qt::KeepAspectRatio));

        QPixmap * image2 = new QPixmap(QPixmap(iterator.fileInfo().absoluteFilePath()).scaled(QSize(256,256),Qt::KeepAspectRatio));

        //image->seth
        //image->load(iterator.fileInfo().absoluteFilePath());
        CoverArtList.push_back(image2);
        //delete image;
        //image = NULL;
    }

while(!_abort){
    if(!CoverArtList.isEmpty()){
        if(imagecounter<CoverArtList.size()){
            imageLabel->setPixmap(*CoverArtList[imagecounter]);
            imagecounter++;
        }
        else{
            imagecounter=1;
            imageLabel->setPixmap(*CoverArtList[0]);
        }

        if(CoverArtList.size() == 1) {
            abort();
        }
    }
    else {
        abort();
    }

    //qDebug() << "FIX THIS!!! :" << CoverArtList.size();


    QEventLoop loop;
    QTimer::singleShot(4096, &loop, SLOT(quit()));
    loop.exec();
    }

    mutex.lock();
    _working = false;
    mutex.unlock();

    emit finished();
}

void TWorker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void TWorker::abort()
{
    if (_working) {
        _abort = true;
        //qDebug() << "ABORT!!!";
        for(quint16 c = 0;c < CoverArtList.size();c++){
            delete CoverArtList[c];
        }

        CoverArtList.clear();
        imagecounter=0;

        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
}
