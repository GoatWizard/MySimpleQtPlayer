#include "info_pannel.h"
#include "ui_info_pannel.h"

#include <QDir>
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

    //imageLabel = new QLabel();
    //imageLabel->setMinimumSize(QSize(256,256));
    //imageLabel->setMaximumSize(QSize(256,256));
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(QString(":/new/def/res/qsmp_logo.png"));
    qDebug() << QDir::currentPath();
    //ui->verticalLayout->addWidget(imageLabel);

    //ui->CoverArtFrame(imageLabel);
}

info_pannel::~info_pannel()
{
    delete ui;
}

void info_pannel::DisplayCoverArt(QString path)
{
    QPixmap image(path);

    //QLabel * imageLabel = new QLabel();
    ui->imageLabel->setPixmap(image);

    //mainLayout.addWidget(imageLabel);
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

    ui->MediaInfoWidget->item(0)->setText("Artist: " + QString::fromStdWString(tag->artist().toWString()));
}
else{
    Album_var = "Unknown";
    }
}
