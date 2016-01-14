#include "info_pannel.h"
#include "ui_info_pannel.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>

//TAGLIB
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>


info_pannel::info_pannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_pannel)
{

    ui->setupUi(this);


    thread = new QThread();
    worker = new TWorker();
    worker->moveToThread(thread);
      //connect(worker, SIGNAL(valueChanged(QString)), ui->label, SLOT(setText(QString)));
      connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
      connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
      connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(QString(":/new/def/res/qsmp_logo.png"));
}

info_pannel::~info_pannel()
{
    worker->abort();
    thread->wait();
    delete thread;
    delete worker;

    delete ui;
}

void info_pannel::DisplayCoverArt(QString path)
{
    if(path != PreviousCoverArt){ // if music file directory is same, that previous: do not proceed change cover art

    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.

    worker->imageLabel = ui->imageLabel;///!!!!

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpe" << "*.JPEG";

    QDirIterator iterator (path, filters, QDir::Files , QDirIterator::Subdirectories);

    while(iterator.hasNext()){
        iterator.next();
        qDebug() << "Cover art changing: " << PreviousCoverArt <<  iterator.fileInfo().absoluteFilePath();
        //ipn->DisplayCoverArt(iterator.fileInfo().absoluteFilePath());
        QPixmap * image = new QPixmap(iterator.fileInfo().absoluteFilePath());
        worker->CoverArtList.push_back(image);
    }


    worker->requestWork();


    ///ui->imageLabel->setPixmap(*image);
    PreviousCoverArt = path;

    }

}
void info_pannel::DisplayMediaInfo(QString path)
{
#ifdef _WIN32
    TagLib::FileRef f(path.toStdWString().c_str());
#else
    TagLib::FileRef f(path.toStdString().c_str());
#endif

QString Album_var,Track_var;
if(!f.isNull() && f.tag()) {
    TagLib::Tag *tag = f.tag();
    ui->MediaInfoWidget->item(0)->setText(QString::fromStdWString(tag->title().toWString()));
    ui->MediaInfoWidget->item(1)->setText(QString::fromStdWString(tag->artist().toWString()));
    ui->MediaInfoWidget->item(2)->setText(QString::fromStdWString(tag->album().toWString()));
    ui->MediaInfoWidget->item(3)->setText(QString::number(tag->year()));
    ui->MediaInfoWidget->item(4)->setText(QString::fromStdWString(tag->comment().toWString()));
    ui->MediaInfoWidget->item(5)->setText(QString::number(tag->track()));
    ui->MediaInfoWidget->item(6)->setText(QString::fromStdWString(tag->genre().toWString()));
}

if(!f.isNull() && f.audioProperties()) {
    TagLib::AudioProperties *properties = f.audioProperties();

    ui->MediaInfoWidget->item(8)->setText(QString::number(properties->bitrate()) + " kbps");
    ui->MediaInfoWidget->item(9)->setText(QString::number(properties->sampleRate()) + " kHz");
    ui->MediaInfoWidget->item(10)->setText("Channels: " + QString::number(properties->channels()));

    int seconds = properties->length() % 60;
    int minutes = (properties->length() - seconds) / 60;
    ui->MediaInfoWidget->item(11)->setText("Length: " + QString::number(minutes) + ":" + QString::number(seconds));
}
    QFileInfo pfile(path);
    ui->MediaInfoWidget->item(13)->setText(QString::number(pfile.size()/1024) + " KiB");
    ui->MediaInfoWidget->item(14)->setText(pfile.dir().absolutePath());
    ui->MediaInfoWidget->item(15)->setText(pfile.fileName());
}
