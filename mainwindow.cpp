#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets>
//#include <QMediaMetaData>
#include <QList>

#include "globals.h"
//#include <QTreeWidgetItem>

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

    ///Setup stylesheet
    QFile styleSheet(":/styles/res/stylesheets/default.qss");

    if (!styleSheet.open(QIODevice::ReadOnly)) {
        qWarning("Unable to open :/styles/res/stylesheets/default.qss");
        return;
    }
    else {
        qApp->setStyleSheet(styleSheet.readAll());
    }

    open_sqlite_db();
    _globals = new globals; // Create an object that stores global variables and functions

    _globals->playlistTree = ui->PlaylistTreeWidget;
    //_globals->playlistTree->setHeaderHidden(true);

    plf = new playlist_form;
    ipn = new info_pannel; mediaPlayer.setVideoOutput(ipn->videoWidget);
    ui->PlaylistformLayout->addWidget(plf);
    ui->InfoPannelLayout->addWidget(ipn);

//Slider
    connect(ui->PlaybackProgressSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
//Other mediaplayer signals
    connect(&mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
//Context menu for add items button
    QMenu * AddItemsMenu = new QMenu(ui->AddItemsButton);
    //ui->AddItemsButton->setStyleSheet("");
    QAction * act0 = new QAction("Files",ui->AddItemsButton);
    QAction * act1 = new QAction("Folder",ui->AddItemsButton);
    //QIcon * icn = new QIcon(":/res/actions/add.png");
    //act0->setIcon(QIcon(":/res/actions/add.png"));
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
    //mediaPlayer.
    mediaPlayer.setMedia(QUrl::fromLocalFile(fname));
    mediaPlayer.play();
    currentTrackUrl = fname;
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
            qApp->tr("Unable to establish a database connection.\n"), QMessageBox::Cancel);
    }
}


void MainWindow::ListDirRecursive(QString directory)
{
    QStringList filters;
    filters << "*.mp3" << "*.ogg" << "*.flac" << "*.mp4"; ///CHECK

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
        InsertFileIntoPlaylist(iterator.fileInfo().absoluteFilePath(),query);
    }
}

void MainWindow::InsertFileIntoPlaylist(QString filename, QSqlQuery &query){

    #ifdef _WIN32
        TagLib::FileRef f(filename.toStdWString().c_str());
    #else
        TagLib::FileRef f(filename.toStdString().c_str());
    #endif

    QString Album_var,Track_var;
    if(!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        Album_var = QString::fromStdWString(tag->album().toWString());
        Track_var = QString::fromStdWString(tag->title().toWString());
    }

    if(Album_var.isEmpty()){
        Album_var = QFileInfo(filename).dir().dirName();
    }
    if(Track_var.isEmpty()){
        //QFileInfo pfile(filename);
        //pfile.fileName();
        Track_var = QFileInfo(filename).fileName();
    }
    QString querystring = "insert into " + QString("TBL") +_globals->current_selected_pls.toLocal8Bit().toHex() + " (Path, Album, Track) values (:valPath, :valAlbum, :valTrack);";
    query.prepare(querystring);
    query.bindValue(":valPath", filename);//.toLocal8Bit().toHex());
    query.bindValue(":valAlbum", Album_var);
    query.bindValue(":valTrack", Track_var);
    query.exec();
}


void MainWindow::PlayTrack()
{
    QSqlQuery query;
    QString qvalue = "SELECT Path FROM "+QString("TBL") +_globals->current_active_pls.toLocal8Bit().toHex()+" WHERE Id = " + QString::number(_globals->current_played_track_id) +";";
    query.prepare(qvalue);
    //query.bindValue(":valCsp", QString("TBL") +_globals->current_selected_pls.toLocal8Bit().toHex());
    query.exec();
    while (query.next()) {
        QString filepath = query.value(0).toString();
        playFile(filepath);
    }
}

void MainWindow::on_PlayButton_clicked()
{

    MyPlayerTreeWidgetItem * selecteditem = (MyPlayerTreeWidgetItem *)_globals->playlistTree->selectedItems().back();
    _globals->current_played_track_id = selecteditem->IdNum;
    _globals->current_played_track = selecteditem->Index;
    _globals->current_active_pls = _globals->current_selected_pls;
    _globals->TreeItemsToIDList();
    PlayTrack();
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

void MainWindow::AddItemsMenuFilesSlot()
{
    QStringList filePath = QFileDialog::getOpenFileNames();

    if(!filePath.isEmpty()){

        QSqlQuery query;
        query.exec("PRAGMA page_size = 4096");
        query.exec("PRAGMA cache_size = 262 144");
        query.exec("PRAGMA temp_store = MEMORY");
        query.exec("PRAGMA journal_mode = OFF");
        query.exec("PRAGMA locking_mode = EXCLUSIVE");
        query.exec("PRAGMA synchronous = OFF");

        for(QStringList::iterator it = filePath.begin();it != filePath.end();++it){
            QString current = *it;
            InsertFileIntoPlaylist(current,query);
            //qDebug() << "File : " << current;
        }

        _globals->fillPlaylist(); //For refreshing playlist

    }
}

void MainWindow::AddItemsMenuFolderSlot()
{
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

void  MainWindow::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::LoadedMedia){
         qDebug() << "Media is loaded";

    }

    if(status == QMediaPlayer::EndOfMedia){
    seekTrack(1);
    }
    else if(status == QMediaPlayer::BufferedMedia){ //Dispay cover art and tags info only after media file completely loaded to avoid errors on Windows
        if(mediaPlayer.isVideoAvailable()){
            qDebug() << "This is video!!!";
            //ipn->ui->MediaInfoWidget->setHidden(true);
            ipn->setIsVideo(true);
            ipn->DisplayMediaInfo(currentTrackUrl);
        }
        else{
            qDebug() << "This file is audio";
            ipn->setIsVideo(false);
            QFileInfo pfile(currentTrackUrl);
            ipn->DisplayCoverArt(pfile.dir().absolutePath());
            ipn->DisplayMediaInfo(currentTrackUrl);
        }
    }
}

void MainWindow::seekTrack(qint16 offset)
{
    _globals->current_played_track+=offset;
    qDebug() << "played track Id1: " << _globals->current_played_track_id;
    qDebug() << "played track num1: " << _globals->current_played_track;

    if(_globals->current_played_track+1>_globals->IDList.size()){
        if(_globals->current_active_pls == _globals->current_selected_pls){
            _globals->playlistTree->selectedItems().back()->setSelected(false);
            _globals->TreeItems[0]->setSelected(true);
        }
        _globals->current_played_track_id=_globals->IDList[0];
        _globals->current_played_track=0;
        qDebug() << "played track Id2: " << _globals->current_played_track_id;
        qDebug() << "played track num2: " << _globals->current_played_track;
    }
    else
    {
        if(_globals->current_active_pls == _globals->current_selected_pls){
            _globals->playlistTree->selectedItems().back()->setSelected(false);
            _globals->TreeItems[_globals->current_played_track]->setSelected(true);
        }
        _globals->current_played_track_id=_globals->IDList[_globals->current_played_track];
        qDebug() << "played track Id3: " << _globals->current_played_track_id;
        qDebug() << "played track num3: " << _globals->current_played_track;
    }

    PlayTrack();
}

void MainWindow::seek(int seconds)
{
    mediaPlayer.setPosition(seconds * 1000);
}

void MainWindow::on_MuteButton_clicked()
{
    mediaPlayer.setMuted(ui->MuteButton->isChecked());
}

void MainWindow::on_NextTrackButton_clicked()
{
    seekTrack(1);
}

void MainWindow::on_PrevTrackButton_clicked()
{
     seekTrack(-1);
}

void MainWindow::on_PlaylistTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    _globals->current_played_track_id = ((MyPlayerTreeWidgetItem *)item)->IdNum;
    _globals->current_played_track = ((MyPlayerTreeWidgetItem *)item)->Index;
    _globals->current_active_pls = _globals->current_selected_pls;
    _globals->TreeItemsToIDList();
    PlayTrack();
}
