#include "tworker.h"

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

    if(!CoverArtList.isEmpty()){
        if(imagecounter<CoverArtList.size()){
        imageLabel->setPixmap(*CoverArtList[imagecounter]);
        imagecounter++;
        }
        else{
            imagecounter=1;
            imageLabel->setPixmap(*CoverArtList[0]);
        }
    }


    QEventLoop loop;
    QTimer::singleShot(4096, &loop, SLOT(quit()));
    loop.exec();


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

        for(quint16 c = 0;c < CoverArtList.size();c++){
            delete CoverArtList[c];
        }

        CoverArtList.clear();
        imagecounter=0;

        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
}
