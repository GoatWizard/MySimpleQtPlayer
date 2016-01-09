#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets>
//#include <QMediaMetaData>
#include <QList>

#include "globals.h"
#include "myplayertreewidgetitem.h"

//TAGLIB
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    open_sqlite_db();
    _globals = new globals; // Create an object that stores global variables and functions

    _globals->playlistTree = ui->PlaylistTreeWidget;//new QTreeWidget;
    _globals->playlistTree->setHeaderHidden(true);

    plf = new playlist_form;
    ipn = new info_pannel;
    ui->PlaylistformLayout->addWidget(plf);
    ui->InfoPannelLayout->addWidget(ipn);

//Slider
    connect(ui->PlaybackProgressSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
//Context menu for add items button
    QMenu * AddItemsMenu = new QMenu(ui->AddItemsButton);
    QAction * act0 = new QAction("Files",ui->AddItemsButton);
    QAction * act1 = new QAction("Folder",ui->AddItemsButton);
    AddItemsMenu->addAction(act0);
    AddItemsMenu->addAction(act1);
    connect(act0,SIGNAL(triggered()),this,SLOT(AddItemsMenuFilesSlot()));
    connect(act1,SIGNAL(triggered()),this,SLOT(AddItemsMenuFolderSlot()));

    ui->AddItemsButton->setMenu(AddItemsMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playFile(QString fname)
{
    mediaPlayer.setMedia(QUrl::fromLocalFile(fname));
    mediaPlayer.play();
    QFileInfo pfile(fname);
    //qDebug() << pfile.dir().absolutePath();
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpe";

    QDirIterator iterator (pfile.dir().absolutePath(), filters, QDir::Files , QDirIterator::Subdirectories);

    while(iterator.hasNext()){
        iterator.next();
        qDebug() << iterator.fileInfo().absoluteFilePath();
        ipn->DisplayCoverArt(iterator.fileInfo().absoluteFilePath());

    }
    //qDebug() << mediaPlayer.metaData("QMediaMetaData::Title").toString() << "adsd";
    //read_tags(1,fname.toStdString().c_str());
    bIsPaused = false;
}


void MainWindow::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(), tr("MP3 files (*.mp3);;All files (*.*)"));
    if (!filePath.isEmpty()){
        playFile(filePath);
    }
}

void MainWindow::open_sqlite_db()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/myplayer.db");
    qDebug() << QDir::homePath();
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::ListDirRecursive(QString directory)
{
    QStringList filters;
    filters << "*.mp3" << "*.ogg" << "*.flac"; ///CHECK

    QDirIterator iterator (directory, filters, QDir::Files , QDirIterator::Subdirectories);//| QDir::NoSymLinks

    QSqlQuery query;
    query.exec("PRAGMA page_size = 4096");
    query.exec("PRAGMA cache_size = 262 144");
    query.exec("PRAGMA temp_store = MEMORY");
    query.exec("PRAGMA journal_mode = OFF");
    query.exec("PRAGMA locking_mode = EXCLUSIVE");
    query.exec("PRAGMA synchronous = OFF");

    while(iterator.hasNext()){
        iterator.next();
        #ifdef _WIN32
            TagLib::FileRef f(iterator.fileInfo().absoluteFilePath().toStdWString().c_str());
        #else
            TagLib::FileRef f(iterator.fileInfo().absoluteFilePath().toStdString().c_str());
        #endif
        QString Album_var,Track_var;
        if(!f.isNull() && f.tag()) {
            TagLib::Tag *tag = f.tag();
            Album_var = QString::fromStdWString(tag->album().toWString());
            Track_var = QString::fromStdWString(tag->title().toWString());
        }
        else {
            Album_var = "Unknown";
        }
        QString querystring = "insert into " + QString("TBL") +_globals->current_selected_pls.toLocal8Bit().toHex() + " (Path, Album, Track) values (:valPath, :valAlbum, :valTrack);";
        query.prepare(querystring);
        query.bindValue(":valPath", iterator.fileInfo().absoluteFilePath());//.toLocal8Bit().toHex());
        query.bindValue(":valAlbum", Album_var);
        query.bindValue(":valTrack", Track_var);
        query.exec();
        //query.finish();
        ///query.exec("insert into "+ _globals->current_selected_pls + " (Path, Album, Track) values (':valPath', ':valAlbum', ':valTrack');");


        //query.exec("insert into "+ _globals->current_selected_pls +" (Path, Album, Track) values('" + ":valA" + "'', " + "'" + Album_var + "'," + "'" + Track_var + "')");

        //qDebug() <<  query.lastError();
    }
}


void MainWindow::on_PlayButton_clicked()
{

    MyPlayerTreeWidgetItem * selecteditem = (MyPlayerTreeWidgetItem *)_globals->playlistTree->selectedItems().back();
    qDebug() << selecteditem->IdNum;

    QSqlQuery query;
    QString qvalue = "SELECT Path FROM "+QString("TBL") +_globals->current_selected_pls.toLocal8Bit().toHex()+" WHERE Id = " + QString::number(selecteditem->IdNum) +";";
    query.prepare(qvalue);
    //query.bindValue(":valCsp", QString("TBL") +_globals->current_selected_pls.toLocal8Bit().toHex());
    query.exec();
    while (query.next()) {
        QString filepath = query.value(0).toString();
        playFile(filepath);
    }
}

void MainWindow::on_Pause_clicked()
{
    if(bIsPaused){
        mediaPlayer.play();
        bIsPaused = false;
    }
    else{
        mediaPlayer.pause();
        bIsPaused = true;
    }
}

void MainWindow::on_Stop_clicked()
{
    mediaPlayer.stop();
}

void MainWindow::AddItemsMenuFilesSlot(){
    qDebug() << "test";
}


void MainWindow::AddItemsMenuFolderSlot(){
    //const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString dirPath = QFileDialog::getExistingDirectory();
    if(!dirPath.isEmpty()){
    ListDirRecursive(dirPath);
    _globals->fillPlaylist(); //For refreshing playlist
    }
}

void MainWindow::on_VolumeSlider_valueChanged(int value)
{
    mediaPlayer.setVolume(value);
}


//Progress playback slider
void MainWindow::durationChanged(qint64 duration)
{
    //this->duration = duration/1000;
    ui->PlaybackProgressSlider->setMaximum(duration / 1000);
}

void MainWindow::positionChanged(qint64 progress)
{
    if (!ui->PlaybackProgressSlider->isSliderDown()) {
        ui->PlaybackProgressSlider->setValue(progress / 1000);
    }
    //updateDurationInfo(progress / 1000);
}
void MainWindow::seek(int seconds)
{
    mediaPlayer.setPosition(seconds * 1000);
}

//
