#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets>
#include <QMediaMetaData>

#include "globals.h"


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
    qDebug() << mediaPlayer.metaData("QMediaMetaData::Title").toString() << "adsd";
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
    qDebug("DEBUG 1\n");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\pidor2");
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
 //qDebug() << iterator.fileInfo().absoluteFilePath();
 //mediaPlayer.setMedia(QUrl::fromLocalFile(iterator.fileInfo().absoluteFilePath()));
 //qDebug() << "Test: " << mediaPlayer.metaData(QMediaMetaData::Title).toString();
 query.exec("insert into "+ _globals->current_selected_pls +" (Path, Album, Track) values('" + iterator.fileInfo().absoluteFilePath() + "', " + "'" + "ALBUM_VAR" + "'," + "'" + "TRACK_VAR" "')");
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
