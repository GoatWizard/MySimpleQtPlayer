#include "info_pannel.h"
#include "ui_info_pannel.h"

#include <QDir>
#include <QDebug>

info_pannel::info_pannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_pannel)
{
    ui->setupUi(this);
    imageLabel = new QLabel();
    imageLabel->setMinimumSize(QSize(256,256));
    imageLabel->setMaximumSize(QSize(256,256));
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QString(":/new/def/res/qsmp_logo.png"));
    qDebug() << QDir::currentPath();
    ui->verticalLayout->addWidget(imageLabel);
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
    imageLabel->setPixmap(image);

    //mainLayout.addWidget(imageLabel);
}

