#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets>
#include <QMediaMetaData>

#include "globals.h"

//TAGLIB
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

//The code below is from taglib examples
int read_tags(int argc,const char *argv)
{
  for(int i = 0; i < argc; i++) {

    std::cout << "******************** \"" << argv << "\" ********************" << endl;

    TagLib::FileRef f(argv);

    if(!f.isNull() && f.tag()) {

      TagLib::Tag *tag = f.tag();

      std::cout << "-- TAG (basic) --" << endl;
      std::cout << "title   - \"" << tag->title()   << "\"" << std::endl;
      std::cout << "artist  - \"" << tag->artist()  << "\"" << std::endl;
      std::cout << "album   - \"" << tag->album()   << "\"" << std::endl;
      std::cout << "year    - \"" << tag->year()    << "\"" << std::endl;
      std::cout << "comment - \"" << tag->comment() << "\"" << std::endl;
      std::cout << "track   - \"" << tag->track()   << "\"" << std::endl;
      std::cout << "genre   - \"" << tag->genre()   << "\"" << std::endl;

      TagLib::PropertyMap tags = f.file()->properties();

      unsigned int longest = 0;
      for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
        if (i->first.size() > longest) {
          longest = i->first.size();
        }
      }

      std::cout << "-- TAG (properties) --" << std::endl;
      for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
        for(TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
          std::cout << left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << std::endl;
        }
      }

    }

    if(!f.isNull() && f.audioProperties()) {

      TagLib::AudioProperties *properties = f.audioProperties();

      int seconds = properties->length() % 60;
      int minutes = (properties->length() - seconds) / 60;

      std::cout << "-- AUDIO --" << std::endl;
      std::cout << "bitrate     - " << properties->bitrate() << std::endl;
      std::cout << "sample rate - " << properties->sampleRate() << std::endl;
      std::cout << "channels    - " << properties->channels() << std::endl;
      //std::cout << "length      - " << minutes << ":" << setfill('0') << setw(2) << seconds << std::endl;
    }
  }
  return 0;
}
//end

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    open_sqlite_db();
    _globals = new globals; // Create an object that stores global variables and functions

    ui->PlaylistView->setModel(_globals->model);

    plf = new playlist_form;
    ipn = new info_pannel;
    ui->PlaylistformLayout->addWidget(plf);
    ui->InfoPannelLayout->addWidget(ipn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playFile(QString fname){

    mediaPlayer.setMedia(QUrl::fromLocalFile(fname));
    mediaPlayer.play();
    //qDebug() << mediaPlayer.metaData("QMediaMetaData::Title").toString() << "adsd";
    //read_tags(1,fname.toStdString().c_str());
    isPaused = false;
}


void MainWindow::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(), tr("MP3 files (*.mp3);;All files (*.*)"));
    if (!filePath.isEmpty()){
        playFile(filePath);
    }
}

void MainWindow::on_playFile_clicked()
{
    openFile();
}

void MainWindow::open_sqlite_db() {
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
 filters << "*.mp3" << "*.ogg" << "*.flac";
 //dir.setNameFilters(filters);

 QDirIterator iterator (directory, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

 QSqlQuery query;
         query.exec("PRAGMA page_size = 4096");
         query.exec("PRAGMA cache_size = 262 144");
         query.exec("PRAGMA temp_store = MEMORY");
         query.exec("PRAGMA journal_mode = OFF");
         query.exec("PRAGMA locking_mode = EXCLUSIVE");
         query.exec("PRAGMA synchronous = OFF");
 while(iterator.hasNext())
 {
 iterator.next();
    TagLib::FileRef f(iterator.fileInfo().absoluteFilePath().toStdWString().c_str());
    QString Album_var;
    if(!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        Album_var = QString::fromStdWString(tag->album().toWString());
    }
    else {
        Album_var = "Unknown";
    }
    query.exec("insert into "+ _globals->current_selected_pls +" (Path, Album, Track) values('" + iterator.fileInfo().absoluteFilePath() + "', " + "'" + Album_var + "'," + "'" + "TRACK_VAR" "')");
 }
}

void MainWindow::on_pushButton_4_clicked()
{

    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString dirPath = QFileDialog::getExistingDirectory();
    ListDirRecursive(dirPath);
    _globals->initializeModel();//For refreshing playlist
}

void MainWindow::on_PlayButton_clicked()
{
    QModelIndexList selection = ui->PlaylistView->selectionModel()->selectedIndexes();
    //CHECK!!!
    //for(int i=0; i< selection.count(); i++){
        QModelIndex index = selection.at(0);
        qint32 selindex = index.row()+1;
        QSqlQuery query;
        query.exec("SELECT Path FROM "+ _globals->current_selected_pls +" WHERE Id = "+ QString("%1").arg(selindex) +";");
        while (query.next()) {
                 QString filepath = query.value(0).toString();
                 playFile(filepath);
        }

    //}

}

void MainWindow::on_Pause_clicked()
{
    if(isPaused){
        mediaPlayer.play();
        isPaused = false;
    }
    else{
        mediaPlayer.pause();
        isPaused = true;
    }
}

void MainWindow::on_Stop_clicked()
{
    mediaPlayer.stop();
}
